/* A window, and a live keyboard.
 *
 * Until now the harness wrote frames to disk and read a script written in
 * advance. That was the right choice as long as the job was to find defects: a
 * reproducible run can be compared, a game actually played cannot. But one
 * does not judge handling from screenshots, and a moment comes when the only
 * question left is "does it play".
 *
 * This file is optional. Without SDL2 everything else works exactly as before,
 * frames on disk and a script -- it is `build.py` that decides, by looking at
 * whether the library is there.
 *
 * What is displayed is the screen area the GPU designates, as it stands in
 * video memory, converted on the fly. The rasteriser does not change: it is
 * verified, and replacing it with hardware is another undertaking.
 */
#include "rt.h"

#ifndef WITH_SDL

/* The settings menu reads this value even with no window: without it, the
   SDL-less build does not link. It then serves no purpose, which is the right
   way for a frame-rate variable not to exist. */
double mod_hz = 60.0;

int video_init(void) { return 0; }
void video_image(const u16 *v, int x, int y, int w, int h) { (void)v; (void)x; (void)y; (void)w; (void)h; }
u32 video_pad(void) { return 0xFFFF; }
int video_negcon(unsigned char *q) { (void)q; return 0; }
int video_closed(void) { return 0; }
void video_quit(void) {}

#else

/* On Windows, SDL diverts main() through a macro and demands its own startup
   library. We tell it instead that the main is already written and declare it
   ready ourselves: one dependency fewer, and the same code on both sides. */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int mods_is_open(void);
void mods_toggle(void);
void mods_move(int);
void mods_change(int);
void mods_draw(u32 *, int, int, int);

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *texture;
static int tex_w, tex_h;
static int closed;
static u32 buttons = 0xFFFF;
static SDL_GameController *pad;
static void pad_open(int);
static void pad_close(void);
static u32 pad_read(void);

/* The frame rate.
 *
 * Nothing holds the game back: the translated code runs at the host machine's
 * speed, and it produces its frames as fast as it is allowed to. On the
 * console it is the video scanout that sets the tempo -- sixty times a second
 * in NTSC, which is what the Japanese version is. Without that limit the car
 * accelerates four times too fast and the game becomes unplayable for a reason
 * that has nothing to do with it.
 *
 * So after showing the frame we wait out what remains of its sixtieth of a
 * second. Waiting here rather than elsewhere has a reason: the game blocks on
 * its own buffer swap, so throttling the display throttles everything else
 * without our having to touch the time base.
 *
 * Lateness does not accumulate. If a frame cost more than its time, we start
 * again from now rather than chase it: making up for lost time on a racing
 * game amounts to making it stutter for nothing.
 */
double mod_hz = 60.0;
#define hz mod_hz
static Uint64 next_frame, freq;

static void pace(void)
{
    Uint64 now;
    if (hz <= 0.0) return;
    if (!freq) { freq = SDL_GetPerformanceFrequency(); next_frame = SDL_GetPerformanceCounter(); }
    next_frame += (Uint64)((double)freq / hz);
    now = SDL_GetPerformanceCounter();
    if (now > next_frame) { next_frame = now; return; }
    {
        double left = (double)(next_frame - now) / (double)freq;
        if (left > 0.002) SDL_Delay((Uint32)((left - 0.001) * 1000.0));
        while (SDL_GetPerformanceCounter() < next_frame) { }
    }
}

int video_init(void)
{
    SDL_SetMainReady();
    /* Two hints to give SDL before it opens anything at all.
     *
     * On Windows, SDL reads Xbox controllers through RAWINPUT by default, then
     * cross-references that with XInput to recover the triggers. When that
     * cross-referencing fails, one gets a half-alive controller: the axes
     * respond, the buttons stay at zero -- exactly what we saw. XInput alone
     * is older and coarser, but it returns everything.
     *
     * And a controller must not fall silent because the window has lost focus:
     * one plays looking at the screen, not the taskbar. */
    SDL_SetHint(SDL_HINT_JOYSTICK_RAWINPUT, "0");
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        fprintf(stderr, "SDL : %s\n", SDL_GetError());
        return 0;
    }
    window = SDL_CreateWindow("Ridge Racer", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 640, 480,
                              SDL_WINDOW_RESIZABLE);
    if (!window) {
        fprintf(stderr, "SDL : %s\n", SDL_GetError());
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "SDL : %s\n", SDL_GetError());
        return 0;
    }
    /* Linear filtering softens a 320 by 240 display stretched to 640 by 480.
       That is a taste, not a fidelity: the console had none. */
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    {   /* A controller already plugged in raises no event: it has to be looked
           for once at startup. */
        int i;
        for (i = 0; i < SDL_NumJoysticks(); i++)
            if (SDL_IsGameController(i)) { pad_open(i); break; }
        if (!pad) printf("controller: none, the keyboard will do\n");
    }
    {   /* HZ=0 to throttle nothing, HZ=30 for the frame rate the race holds on
           the console -- there the game draws one frame every two scanouts. */
        const char *h = getenv("HZ");
        if (h) hz = atof(h);
        if (hz > 0.0) printf("window: %g frames per second at most\n", hz);
        else printf("window: free running\n");
    }
    return 1;
}

/* --- the controller ------------------------------------------------------
 *
 * SDL can recognise most controllers and give them a common layout, which
 * saves writing one table per model. We open the first one that turns up, and
 * we accept that it may arrive or leave mid-game -- a controller that is
 * plugged back in must work again without restarting the game.
 *
 * The game knows two controllers. The digital one, which returns only sixteen
 * buttons; and Namco's neGcon, whose body twists and whose I and II buttons
 * measure how hard they are pressed. Ridge Racer was written for that
 * controller: the function that reads the port tests for type 0x23 and, in
 * that case, takes the twist as the steering angle and the two buttons as
 * pedals. Digital mode does no more than manufacture the same values from the
 * directions.
 *
 * The left stick can therefore become either a D-pad or a twist. See
 * pad_negcon below.
 */
static void pad_open(int index)
{
    if (pad) return;
    pad = SDL_GameControllerOpen(index);
    if (pad) {
        SDL_Joystick *j = SDL_GameControllerGetJoystick(pad);
        printf("controller: %s\n", SDL_GameControllerName(pad));
        /* What the device declares, before any interpretation. A controller
           that announces zero buttons is not the same failure as a controller
           that announces fourteen and returns none of them. */
        if (j)
            printf("   %d buttons, %d axes, %d hats\n",
                   SDL_JoystickNumButtons(j), SDL_JoystickNumAxes(j),
                   SDL_JoystickNumHats(j));
    }
}

/* The raw state, without the "game controller" layer. Serves to tell a mute
   device apart from a mapping that maps to nothing. */
static void pad_raw(void)
{
    static char before[128];
    char line[128], *p = line;
    SDL_Joystick *j;
    int i, n;
    if (!pad) return;
    j = SDL_GameControllerGetJoystick(pad);
    if (!j) return;
    p += sprintf(p, "raw: b");
    n = SDL_JoystickNumButtons(j);
    if (n > 20) n = 20;
    for (i = 0; i < n; i++) *p++ = SDL_JoystickGetButton(j, i) ? '1' : '.';
    n = SDL_JoystickNumHats(j);
    if (n > 0) p += sprintf(p, " hat %02X", SDL_JoystickGetHat(j, 0));
    n = SDL_JoystickNumAxes(j);
    if (n > 6) n = 6;
    for (i = 0; i < n; i++)
        p += sprintf(p, " %d:%6d", i, SDL_JoystickGetAxis(j, i));
    *p = 0;
    if (strcmp(line, before)) {
        strcpy(before, line);
        printf("%s\n", line);
        fflush(stdout);
    }
}

static void pad_close(void)
{
    if (pad) { SDL_GameControllerClose(pad); pad = 0; }
}

static u32 pad_read(void)
{
    u32 m = 0xFFFF;
    int x, y;
    const int DEADZONE = 12000;   /* dead zone: a stick at rest is never exactly
                                     at the centre */
    if (!pad) return m;
    /* Ask for the update rather than rely on the event loop: it does it
       already, but it is not the only caller of ours, and a state one frame
       old is a defect one would not see. */
    SDL_GameControllerUpdate();
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_UP))    m &= ~0x1000u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) m &= ~0x2000u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN))  m &= ~0x4000u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_DPAD_LEFT))  m &= ~0x8000u;
    /* The layout follows the position of the buttons, not their names: the
       bottom button accelerates, the right one brakes, like cross and
       circle. */
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_A))     m &= ~0x0040u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_B))     m &= ~0x0020u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_X))     m &= ~0x0080u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_Y))     m &= ~0x0010u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_LEFTSHOULDER))  m &= ~0x0004u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) m &= ~0x0008u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_START)) m &= ~0x0800u;
    if (SDL_GameControllerGetButton(pad, SDL_CONTROLLER_BUTTON_BACK))  m &= ~0x0100u;
    if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERLEFT)  > 8000) m &= ~0x0001u;
    if (SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 8000) m &= ~0x0002u;
    x = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTX);
    y = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTY);
    if (x < -DEADZONE) m &= ~0x8000u;
    if (x >  DEADZONE) m &= ~0x2000u;
    if (y < -DEADZONE) m &= ~0x1000u;
    if (y >  DEADZONE) m &= ~0x4000u;
    return m;
}

/* The neGcon's report: four bytes after the buttons.
 *
 *   byte 4  twist of the body, 0x00 full left, 0x80 at rest, 0xFF full right
 *   byte 5  button I,  0x00 released to 0xFF fully pressed
 *   byte 6  button II, likewise
 *   byte 7  L trigger, likewise
 *
 * The thresholds are the game's, read out of read_pad_input: it clamps I, II
 * and L at 0x6A and then divides by 0x6A, so that the useful travel stops
 * there; and it manufactures the digital directions from the twist, right
 * beyond 0xA3, left below 0x5E. We therefore produce 0x6A for a full press,
 * not 0xFF: beyond that we would waste half of the triggers' travel.
 *
 * The D-pad and the face buttons stay connected: they push the twist and the
 * pedals all the way. Nothing is lost by going analogue, only the intermediate
 * values are added.
 */
static int pad_negcon(unsigned char *q)
{
    const int FULL = 0x6A;
    const int DEADZONE = 3000;
    int x, t, i, ii, l;
    if (!pad) return 0;

    x = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_LEFTX);
    if (x > -DEADZONE && x < DEADZONE) x = 0;
    else x -= (x > 0 ? DEADZONE : -DEADZONE);
    t = 0x80 + x * 127 / (32767 - DEADZONE);
    if (t < 0) t = 0;
    if (t > 255) t = 255;

    i  = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) * FULL / 32767;
    ii = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_TRIGGERLEFT)  * FULL / 32767;
    l  = 0;
    if (i < 0) i = 0;
    if (ii < 0) ii = 0;

    /* What the keyboard or the buttons ask for wins: all or nothing. */
    if (!(buttons & 0x8000u)) t = 0x00;
    if (!(buttons & 0x2000u)) t = 0xFF;
    if (!(buttons & 0x0040u)) i = FULL;
    if (!(buttons & 0x0020u)) ii = FULL;
    if (!(buttons & 0x0004u)) l = FULL;

    q[0] = (unsigned char)t;
    q[1] = (unsigned char)i;
    q[2] = (unsigned char)ii;
    q[3] = (unsigned char)l;
    return 1;
}

int video_negcon(unsigned char *q) { return pad_negcon(q); }

static void poll_input(void)
{
    SDL_Event e;
    const Uint8 *k;
    u32 m = 0xFFFF;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) closed = 1;
        /* Plugging in a controller is handled here and nowhere else: this loop
           drains the whole queue, so the second pass that looked for these
           events further down never found anything. A controller plugged in
           mid-game was seen only by chance. */
        if (e.type == SDL_CONTROLLERDEVICEADDED) { pad_open(e.cdevice.which); continue; }
        if (e.type == SDL_CONTROLLERDEVICEREMOVED) { pad_close(); continue; }
        if (e.type != SDL_KEYDOWN) continue;
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE: closed = 1; break;
        case SDLK_F1:     mods_toggle(); break;
        /* While the menu is open the arrows belong to it: we do not want to
           drive and adjust at the same time. */
        case SDLK_UP:     if (mods_is_open()) mods_move(-1); break;
        case SDLK_DOWN:   if (mods_is_open()) mods_move(+1); break;
        case SDLK_LEFT:   if (mods_is_open()) mods_change(-1); break;
        case SDLK_RIGHT:  if (mods_is_open()) mods_change(+1); break;
        default: break;
        }
    }
    /* The menu is also driven from the controller: the D-pad and the bottom
       button, as on the keyboard. */
    if (mods_is_open()) {
        static u32 before = 0xFFFF;
        u32 now = pad_read();
        u32 pressed = before & ~now;          /* what has just been pressed */
        if (pressed & 0x1000u) mods_move(-1);
        if (pressed & 0x4000u) mods_move(+1);
        if (pressed & 0x8000u) mods_change(-1);
        if (pressed & 0x2000u) mods_change(+1);
        if (pressed & 0x0100u) mods_toggle();
        before = now;
        buttons = 0xFFFF;
        return;
    }
    k = SDL_GetKeyboardState(NULL);
    /* The layout follows what one has under the fingers, not the printing on
       the controller: the arrows steer, the space bar accelerates. */
    if (k[SDL_SCANCODE_UP])       m &= ~0x1000u;
    if (k[SDL_SCANCODE_RIGHT])    m &= ~0x2000u;
    if (k[SDL_SCANCODE_DOWN])     m &= ~0x4000u;
    if (k[SDL_SCANCODE_LEFT])     m &= ~0x8000u;
    if (k[SDL_SCANCODE_RETURN])   m &= ~0x0800u;   /* start  */
    if (k[SDL_SCANCODE_RSHIFT] || k[SDL_SCANCODE_LSHIFT])
                                  m &= ~0x0100u;   /* select */
    if (k[SDL_SCANCODE_SPACE] || k[SDL_SCANCODE_X])
                                  m &= ~0x0040u;   /* cross  : accelerate */
    if (k[SDL_SCANCODE_C])        m &= ~0x0020u;   /* circle : brake      */
    if (k[SDL_SCANCODE_D])        m &= ~0x0010u;   /* triangle */
    if (k[SDL_SCANCODE_S])        m &= ~0x0080u;   /* square   */
    if (k[SDL_SCANCODE_A])        m &= ~0x0004u;   /* L1 */
    if (k[SDL_SCANCODE_E])        m &= ~0x0008u;   /* R1 */
    buttons = m & pad_read();
    { extern int mod_show_pad; if (mod_show_pad) pad_raw(); }
}

void video_image(const u16 *vram, int x, int y, int w, int h)
{
    void *pixels;
    int pitch, i, j;
    if (!renderer) return;
    if (!texture || tex_w != w || tex_h != h) {
        if (texture) SDL_DestroyTexture(texture);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                    SDL_TEXTUREACCESS_STREAMING, w, h);
        tex_w = w; tex_h = h;
    }
    if (!texture) return;
    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0) return;
    for (j = 0; j < h; j++) {
        u32 *line = (u32 *)((char *)pixels + (size_t)j * pitch);
        const u16 *src = vram + (((y + j) & 511) << 10);
        for (i = 0; i < w; i++) {
            u16 c = src[(x + i) & 1023];
            /* Five bits per component become eight: the three high bits are
               copied back into the low ones, so that white stays white. */
            u32 r = (c & 31), g = (c >> 5) & 31, b = (c >> 10) & 31;
            line[i] = 0xFF000000u
                    | (((r << 3) | (r >> 2)) << 16)
                    | (((g << 3) | (g >> 2)) << 8)
                    |  ((b << 3) | (b >> 2));
        }
    }
    /* The menu is drawn into the final image, after video memory rather than
       inside it: the game cannot erase it, and we do not soil what it has
       produced. */
    mods_draw((u32 *)pixels, pitch, w, h);
    SDL_UnlockTexture(texture);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    poll_input();
    pace();
}

u32 video_pad(void) { return buttons; }
int video_closed(void) { return closed; }

void video_quit(void)
{
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif
