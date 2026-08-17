/* Le son du lecteur CD.
 *
 * La bande-son de Ridge Racer n'est pas synthétisée : ce sont douze pistes
 * audio ordinaires, gravées à côté des données, que la console lisait avec le
 * même mécanisme que n'importe quel disque compact. Il n'y a donc pas de
 * synthétiseur à écrire pour l'entendre — seulement des secteurs à servir au
 * bon rythme.
 *
 * Le format tombe juste : un secteur audio fait 2352 octets, soit exactement
 * 588 trames stéréo de seize bits à 44 100 Hz. Aucune conversion, aucun
 * rééchantillonnage. On lit et on pousse.
 *
 * Ce fichier est facultatif comme la fenêtre : sans SDL2, il ne fait rien et
 * le reste fonctionne.
 */
#include "rt.h"

#ifndef AVEC_SDL

int audio_init(void) { return 0; }
void audio_pousser(const void *d, int n) { (void)d; (void)n; }
unsigned audio_en_attente(void) { return 0; }
void audio_vider(void) {}

#else

/* Sous Windows, SDL detourne main() par une macro et reclame sa propre
   bibliotheque de demarrage. On lui dit plutot que le main est deja ecrit et
   on le declare pret nous-memes : une dependance de moins, et le meme code
   des deux cotes. */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

static SDL_AudioDeviceID sortie;

int audio_init(void)
{
    SDL_AudioSpec veut, obtenu;
    SDL_SetMainReady();
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL audio : %s\n", SDL_GetError());
        return 0;
    }
    SDL_memset(&veut, 0, sizeof veut);
    veut.freq = 44100;
    veut.format = AUDIO_S16LSB;
    veut.channels = 2;
    veut.samples = 1024;
    sortie = SDL_OpenAudioDevice(NULL, 0, &veut, &obtenu, 0);
    if (!sortie) {
        fprintf(stderr, "SDL audio : %s\n", SDL_GetError());
        return 0;
    }
    SDL_PauseAudioDevice(sortie, 0);
    return 1;
}

/* La file de SDL sert de tampon et de metronome a la fois : tant qu'elle est
   assez remplie, on ne lit pas de secteur. C'est la carte son qui donne le
   rythme, et non notre horloge -- si les deux devaient s'accorder, l'une
   deriverait de l'autre et le son craquerait. */
void audio_pousser(const void *donnees, int octets)
{
    if (sortie) SDL_QueueAudio(sortie, donnees, (Uint32)octets);
}

unsigned audio_en_attente(void)
{
    return sortie ? (unsigned)SDL_GetQueuedAudioSize(sortie) : 0;
}

void audio_vider(void)
{
    if (sortie) SDL_ClearQueuedAudio(sortie);
}

#endif
