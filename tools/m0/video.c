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

int video_init(void) { return 0; }
void video_image(const u16 *v, int x, int y, int w, int h) { (void)v; (void)x; (void)y; (void)w; (void)h; }
u32 video_manette(void) { return 0xFFFF; }
int video_fermee(void) { return 0; }
void video_fin(void) {}

#else

#include <SDL2/SDL.h>
#include <stdio.h>

static SDL_Window *fenetre;
static SDL_Renderer *rendu;
static SDL_Texture *texture;
static int tex_l, tex_h;
static int ferme;
static u32 boutons = 0xFFFF;

int video_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
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
    return 1;
}

static void touches(void)
{
    SDL_Event e;
    const Uint8 *k;
    u32 m = 0xFFFF;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) ferme = 1;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) ferme = 1;
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
    boutons = m;
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
    SDL_UnlockTexture(texture);
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, texture, NULL, NULL);
    SDL_RenderPresent(rendu);
    touches();
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
