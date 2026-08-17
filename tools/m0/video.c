/* Une fenêtre, et un clavier vivant.
 *
 * Jusqu'ici le banc écrivait des images sur disque et lisait un scénario écrit
 * d'avance. C'était le bon choix tant qu'il fallait trouver des défauts : une
 * exécution reproductible se compare, une partie jouée ne se compare pas. Mais
 * on ne juge pas une conduite sur des captures, et il arrive un moment où la
 * seule question qui reste est « est-ce que ça se joue ».
 *
 * Ce fichier est facultatif. Sans SDL2, tout le reste fonctionne exactement
 * comme avant, images sur disque et scénario -- c'est `build.py` qui décide,
 * en regardant si la bibliothèque est là.
 *
 * Ce qui est affiché est la zone d'écran que le GPU désigne, telle qu'elle est
 * dans la mémoire vidéo, convertie à la volée. Le rastériseur ne change pas :
 * il est vérifié, et le remplacer par du matériel est un autre chantier.
 */
#include "rt.h"

#ifndef AVEC_SDL

/* Le menu des reglages lit cette valeur meme sans fenetre : sans elle, la
   construction sans SDL ne se lie pas. Elle ne sert alors a rien, ce qui est
   la bonne facon pour une variable de cadence de ne pas exister. */
double mod_hz = 60.0;

int video_init(void) { return 0; }
void video_image(const u16 *v, int x, int y, int w, int h) { (void)v; (void)x; (void)y; (void)w; (void)h; }
u32 video_manette(void) { return 0xFFFF; }
int video_negcon(unsigned char *q) { (void)q; return 0; }
int video_fermee(void) { return 0; }
void video_fin(void) {}

#else

/* Sous Windows, SDL detourne main() par une macro et reclame sa propre
   bibliotheque de demarrage. On lui dit plutot que le main est deja ecrit et
   on le declare pret nous-memes : une dependance de moins, et le meme code
   des deux cotes. */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
int mods_ouvert(void);
void mods_basculer(void);
void mods_deplacer(int);
void mods_changer(int);
void mods_dessiner(u32 *, int, int, int);

static SDL_Window *fenetre;
static SDL_Renderer *rendu;
static SDL_Texture *texture;
static int tex_l, tex_h;
static int ferme;
static u32 boutons = 0xFFFF;
static SDL_GameController *manette;
static void manette_ouvrir(int);
static void manette_fermer(void);
static u32 manette_lire(void);

/* La cadence.
 *
 * Rien ne bride le jeu : le code traduit s'execute a la vitesse de la machine
 * hote, et il produit ses images aussi vite qu'on les lui laisse produire.
 * Sur la console, c'est le balayage video qui donne le tempo -- soixante fois
 * par seconde en NTSC, ce qu'est la version japonaise. Sans cette limite, la
 * voiture accelere quatre fois trop vite et le jeu devient injouable pour une
 * raison qui n'a rien a voir avec lui.
 *
 * On attend donc, apres avoir montre l'image, ce qui reste de son seizieme de
 * seconde. Attendre ici plutot qu'ailleurs a une raison : le jeu bloque sur
 * son propre echange de tampons, donc brider l'affichage bride tout le reste
 * sans qu'on ait a toucher a la base de temps.
 *
 * Le retard ne s'accumule pas. Si une image a coute plus que son temps, on
 * repart de maintenant plutot que de courir apres : rattraper un retard sur
 * un jeu de course revient a le rendre saccade pour rien.
 */
double mod_hz = 60.0;
#define hz mod_hz
static Uint64 prochaine, freq;

static void cadencer(void)
{
    Uint64 maintenant;
    if (hz <= 0.0) return;
    if (!freq) { freq = SDL_GetPerformanceFrequency(); prochaine = SDL_GetPerformanceCounter(); }
    prochaine += (Uint64)((double)freq / hz);
    maintenant = SDL_GetPerformanceCounter();
    if (maintenant > prochaine) { prochaine = maintenant; return; }
    {
        double reste = (double)(prochaine - maintenant) / (double)freq;
        if (reste > 0.002) SDL_Delay((Uint32)((reste - 0.001) * 1000.0));
        while (SDL_GetPerformanceCounter() < prochaine) { }
    }
}

int video_init(void)
{
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        fprintf(stderr, "SDL : %s\n", SDL_GetError());
        return 0;
    }
    fenetre = SDL_CreateWindow("Ridge Racer", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 640, 480,
                               SDL_WINDOW_RESIZABLE);
    if (!fenetre) {
        fprintf(stderr, "SDL : %s\n", SDL_GetError());
        return 0;
    }
    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!rendu) rendu = SDL_CreateRenderer(fenetre, -1, 0);
    if (!rendu) {
        fprintf(stderr, "SDL : %s\n", SDL_GetError());
        return 0;
    }
    /* Le filtrage lineaire adoucit un affichage 320 par 240 etire en 640 par
       480. C'est un gout, pas une fidelite : la console n'en avait pas. */
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    {   /* Une manette deja branchee ne provoque pas d'evenement : il faut la
           chercher une fois au demarrage. */
        int i;
        for (i = 0; i < SDL_NumJoysticks(); i++)
            if (SDL_IsGameController(i)) { manette_ouvrir(i); break; }
        if (!manette) printf("manette : aucune, le clavier fera l'affaire\n");
    }
    {   /* HZ=0 pour ne rien brider, HZ=30 pour la cadence que la course tient
           sur la console -- le jeu y dessine une image sur deux balayages. */
        const char *h = getenv("HZ");
        if (h) hz = atof(h);
        if (hz > 0.0) printf("fenetre : %g images par seconde au plus\n", hz);
        else printf("fenetre : cadence libre\n");
    }
    return 1;
}

/* --- la manette ----------------------------------------------------------
 *
 * SDL sait reconnaitre la plupart des manettes et leur donner une disposition
 * commune, ce qui evite d'ecrire une table par modele. On ouvre la premiere
 * venue, et on accepte qu'elle arrive ou reparte en cours de partie -- une
 * manette qu'on rebranche doit remarcher sans relancer le jeu.
 *
 * Le jeu connait deux manettes. La numerique, qui ne rend que seize boutons ;
 * et le neGcon de Namco, dont le corps se tord et dont les boutons I et II
 * mesurent l'appui. Ridge Racer a ete ecrit pour cette manette-la : la
 * fonction qui lit le port teste le type 0x23 et, dans ce cas, prend la
 * torsion comme angle de braquage et les deux boutons comme pedales. Le mode
 * numerique ne fait que fabriquer les memes valeurs a partir des directions.
 *
 * Le stick gauche peut donc devenir soit une croix directionnelle, soit une
 * torsion. Voir manette_negcon plus bas.
 */
static void manette_ouvrir(int index)
{
    if (manette) return;
    manette = SDL_GameControllerOpen(index);
    if (manette)
        printf("manette : %s\n", SDL_GameControllerName(manette));
}

static void manette_fermer(void)
{
    if (manette) { SDL_GameControllerClose(manette); manette = 0; }
}

static u32 manette_lire(void)
{
    u32 m = 0xFFFF;
    int x, y;
    const int MORT = 12000;      /* zone morte : un stick au repos n'est jamais
                                    exactement au centre */
    if (!manette) return m;
    /* Demander la mise a jour plutot que compter sur la boucle d'evenements :
       elle la fait deja, mais elle n'est pas seule a nous appeler, et un etat
       vieux d'une image est un defaut qu'on ne verrait pas. */
    SDL_GameControllerUpdate();
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_DPAD_UP))    m &= ~0x1000u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) m &= ~0x2000u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_DPAD_DOWN))  m &= ~0x4000u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_DPAD_LEFT))  m &= ~0x8000u;
    /* La disposition suit la position des boutons, pas leur nom : le bouton du
       bas accelere, celui de droite freine, comme la croix et le rond. */
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_A))     m &= ~0x0040u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_B))     m &= ~0x0020u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_X))     m &= ~0x0080u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_Y))     m &= ~0x0010u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_LEFTSHOULDER))  m &= ~0x0004u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) m &= ~0x0008u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_START)) m &= ~0x0800u;
    if (SDL_GameControllerGetButton(manette, SDL_CONTROLLER_BUTTON_BACK))  m &= ~0x0100u;
    if (SDL_GameControllerGetAxis(manette, SDL_CONTROLLER_AXIS_TRIGGERLEFT)  > 8000) m &= ~0x0001u;
    if (SDL_GameControllerGetAxis(manette, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 8000) m &= ~0x0002u;
    x = SDL_GameControllerGetAxis(manette, SDL_CONTROLLER_AXIS_LEFTX);
    y = SDL_GameControllerGetAxis(manette, SDL_CONTROLLER_AXIS_LEFTY);
    if (x < -MORT) m &= ~0x8000u;
    if (x >  MORT) m &= ~0x2000u;
    if (y < -MORT) m &= ~0x1000u;
    if (y >  MORT) m &= ~0x4000u;
    return m;
}

/* Le rapport du neGcon : quatre octets apres les boutons.
 *
 *   octet 4  torsion du boitier, 0x00 a gauche, 0x80 au repos, 0xFF a droite
 *   octet 5  bouton I,  0x00 relache a 0xFF enfonce
 *   octet 6  bouton II, idem
 *   octet 7  gachette L, idem
 *
 * Les seuils sont ceux du jeu, lus dans read_pad_input : il ecrete I, II et L
 * a 0x6A puis divise par 0x6A, si bien que la course utile s'arrete la ; et il
 * fabrique les directions numeriques a partir de la torsion, droite au-dela de
 * 0xA3, gauche en deca de 0x5E. On produit donc 0x6A pour un appui plein, et
 * non 0xFF : au-dela, on gaspillerait la moitie de la course des gachettes.
 *
 * La croix directionnelle et les boutons de face restent branches : ils
 * poussent la torsion et les pedales a fond. On ne perd rien en passant en
 * analogique, on ajoute seulement les valeurs intermediaires.
 */
static int manette_negcon(unsigned char *q)
{
    const int PLEIN = 0x6A;
    const int MORT = 3000;
    int x, t, i, ii, l;
    if (!manette) return 0;

    x = SDL_GameControllerGetAxis(manette, SDL_CONTROLLER_AXIS_LEFTX);
    if (x > -MORT && x < MORT) x = 0;
    else x -= (x > 0 ? MORT : -MORT);
    t = 0x80 + x * 127 / (32767 - MORT);
    if (t < 0) t = 0;
    if (t > 255) t = 255;

    i  = SDL_GameControllerGetAxis(manette, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) * PLEIN / 32767;
    ii = SDL_GameControllerGetAxis(manette, SDL_CONTROLLER_AXIS_TRIGGERLEFT)  * PLEIN / 32767;
    l  = 0;
    if (i < 0) i = 0;
    if (ii < 0) ii = 0;

    /* Ce que le clavier ou les boutons demandent l'emporte : tout ou rien. */
    if (!(boutons & 0x8000u)) t = 0x00;
    if (!(boutons & 0x2000u)) t = 0xFF;
    if (!(boutons & 0x0040u)) i = PLEIN;
    if (!(boutons & 0x0020u)) ii = PLEIN;
    if (!(boutons & 0x0004u)) l = PLEIN;

    q[0] = (unsigned char)t;
    q[1] = (unsigned char)i;
    q[2] = (unsigned char)ii;
    q[3] = (unsigned char)l;
    return 1;
}

int video_negcon(unsigned char *q) { return manette_negcon(q); }

static void touches(void)
{
    SDL_Event e;
    const Uint8 *k;
    u32 m = 0xFFFF;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) ferme = 1;
        /* Le branchement d'une manette se traite ici et nulle part ailleurs :
           cette boucle vide la file entiere, et le second passage qui cherchait
           ces evenements plus bas ne trouvait donc jamais rien. Une manette
           branchee en cours de partie n'etait vue que par hasard. */
        if (e.type == SDL_CONTROLLERDEVICEADDED) { manette_ouvrir(e.cdevice.which); continue; }
        if (e.type == SDL_CONTROLLERDEVICEREMOVED) { manette_fermer(); continue; }
        if (e.type != SDL_KEYDOWN) continue;
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE: ferme = 1; break;
        case SDLK_F1:     mods_basculer(); break;
        /* Tant que le menu est ouvert, les fleches lui appartiennent : on ne
           veut pas piloter et regler en meme temps. */
        case SDLK_UP:     if (mods_ouvert()) mods_deplacer(-1); break;
        case SDLK_DOWN:   if (mods_ouvert()) mods_deplacer(+1); break;
        case SDLK_LEFT:   if (mods_ouvert()) mods_changer(-1); break;
        case SDLK_RIGHT:  if (mods_ouvert()) mods_changer(+1); break;
        default: break;
        }
    }
    /* Le menu se pilote aussi a la manette : la croix directionnelle et le
       bouton du bas, comme au clavier. */
    if (mods_ouvert()) {
        static u32 avant = 0xFFFF;
        u32 g = manette_lire();
        u32 nouveau = avant & ~g;          /* ce qui vient d'etre enfonce */
        if (nouveau & 0x1000u) mods_deplacer(-1);
        if (nouveau & 0x4000u) mods_deplacer(+1);
        if (nouveau & 0x8000u) mods_changer(-1);
        if (nouveau & 0x2000u) mods_changer(+1);
        if (nouveau & 0x0100u) mods_basculer();
        avant = g;
        boutons = 0xFFFF;
        return;
    }
    k = SDL_GetKeyboardState(NULL);
    /* La disposition suit ce qu'on a sous les doigts, pas la sérigraphie de la
       manette : les flèches dirigent, la barre d'espace accélère. */
    if (k[SDL_SCANCODE_UP])       m &= ~0x1000u;
    if (k[SDL_SCANCODE_RIGHT])    m &= ~0x2000u;
    if (k[SDL_SCANCODE_DOWN])     m &= ~0x4000u;
    if (k[SDL_SCANCODE_LEFT])     m &= ~0x8000u;
    if (k[SDL_SCANCODE_RETURN])   m &= ~0x0800u;   /* start  */
    if (k[SDL_SCANCODE_RSHIFT] || k[SDL_SCANCODE_LSHIFT])
                                  m &= ~0x0100u;   /* select */
    if (k[SDL_SCANCODE_SPACE] || k[SDL_SCANCODE_X])
                                  m &= ~0x0040u;   /* croix : accelerer */
    if (k[SDL_SCANCODE_C])        m &= ~0x0020u;   /* rond  : freiner   */
    if (k[SDL_SCANCODE_D])        m &= ~0x0010u;   /* triangle */
    if (k[SDL_SCANCODE_S])        m &= ~0x0080u;   /* carre    */
    if (k[SDL_SCANCODE_A])        m &= ~0x0004u;   /* L1 */
    if (k[SDL_SCANCODE_E])        m &= ~0x0008u;   /* R1 */
    boutons = m & manette_lire();
}

void video_image(const u16 *vram, int x, int y, int l, int h)
{
    void *pixels;
    int pas, i, j;
    if (!rendu) return;
    if (!texture || tex_l != l || tex_h != h) {
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTexture(rendu, SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING, l, h);
        tex_l = l; tex_h = h;
    }
    if (!texture) return;
    if (SDL_LockTexture(texture, NULL, &pixels, &pas) != 0) return;
    for (j = 0; j < h; j++) {
        u32 *ligne = (u32 *)((char *)pixels + (size_t)j * pas);
        const u16 *src = vram + (((y + j) & 511) << 10);
        for (i = 0; i < l; i++) {
            u16 c = src[(x + i) & 1023];
            /* Cinq bits par composante deviennent huit : on recopie les trois
               bits hauts en bas, pour que le blanc reste blanc. */
            u32 r = (c & 31), g = (c >> 5) & 31, b = (c >> 10) & 31;
            ligne[i] = 0xFF000000u
                     | (((r << 3) | (r >> 2)) << 16)
                     | (((g << 3) | (g >> 2)) << 8)
                     |  ((b << 3) | (b >> 2));
        }
    }
    /* Le menu se dessine dans l'image finale, apres la memoire video et non
       dedans : le jeu ne peut pas l'effacer, et nous ne salissons pas ce qu'il
       a produit. */
    mods_dessiner((u32 *)pixels, pas, l, h);
    SDL_UnlockTexture(texture);
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, texture, NULL, NULL);
    SDL_RenderPresent(rendu);
    touches();
    cadencer();
}

u32 video_manette(void) { return boutons; }
int video_fermee(void) { return ferme; }

void video_fin(void)
{
    if (texture) SDL_DestroyTexture(texture);
    if (rendu) SDL_DestroyRenderer(rendu);
    if (fenetre) SDL_DestroyWindow(fenetre);
    SDL_Quit();
}

#endif
