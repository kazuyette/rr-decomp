/* The CD drive's audio.
 *
 * Ridge Racer's soundtrack is not synthesised: it is twelve ordinary audio
 * tracks, burned alongside the data, which the console played back with the
 * same mechanism as any compact disc. There is therefore no synthesiser to
 * write in order to hear it — only sectors to serve at the right rate.
 *
 * The format works out exactly: an audio sector is 2352 bytes, which is
 * precisely 588 sixteen-bit stereo frames at 44 100 Hz. No conversion, no
 * resampling. We read and we push.
 *
 * This file is optional like the window: without SDL2 it does nothing and the
 * rest works.
 */
#include "rt.h"

#ifndef WITH_SDL

int audio_init(void) { return 0; }
void audio_push(const void *d, int n) { (void)d; (void)n; }
unsigned audio_queued(void) { return 0; }
void audio_flush(void) {}

#else

/* On Windows, SDL diverts main() through a macro and demands its own startup
   library. We tell it instead that the main is already written and declare it
   ready ourselves: one dependency fewer, and the same code on both sides. */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

static SDL_AudioDeviceID device;

int audio_init(void)
{
    SDL_AudioSpec want, got;
    SDL_SetMainReady();
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL audio : %s\n", SDL_GetError());
        return 0;
    }
    SDL_memset(&want, 0, sizeof want);
    want.freq = 44100;
    want.format = AUDIO_S16LSB;
    want.channels = 2;
    want.samples = 1024;
    device = SDL_OpenAudioDevice(NULL, 0, &want, &got, 0);
    if (!device) {
        fprintf(stderr, "SDL audio : %s\n", SDL_GetError());
        return 0;
    }
    SDL_PauseAudioDevice(device, 0);
    return 1;
}

/* SDL's queue serves as buffer and metronome at once: as long as it is full
   enough, we do not read a sector. It is the sound card that sets the pace,
   not our clock -- if the two had to agree, one would drift from the other and
   the sound would crackle. */
void audio_push(const void *data, int bytes)
{
    if (device) SDL_QueueAudio(device, data, (Uint32)bytes);
}

unsigned audio_queued(void)
{
    return device ? (unsigned)SDL_GetQueuedAudioSize(device) : 0;
}

void audio_flush(void)
{
    if (device) SDL_ClearQueuedAudio(device);
}

#endif
