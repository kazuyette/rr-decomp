/* cand_func_80021BE0.c -- written by hand from the disassembly.
 *
 * The first function attempted individually rather than generated. m2c's
 * version was measured against all five pipelines and matched under none,
 * so this is not a regeneration: it is a reading.
 *
 * What the function does, and why the reading is more than guesswork:
 *
 * D_8007C210 is the track selector -- the same "< 3" test that track_select
 * uses to choose between the two 256-node tables and the 368-node one. The
 * length it picks here is 0x10000 or 0x17000, which is 256*256 and 368*256:
 * the node counts multiplied by the 256 units of progress per node that
 * track_query_surface divides by. So the value is the lap length in the
 * car's own trackPos units, and that agreement across three independently
 * recovered facts is what makes the reading trustworthy.
 *
 * D_8007C260 is a position along that lap, compared against a marker that
 * also depends on the selected track (0x2800 in one phase; 0xB900 or
 * 0x12900 in the other). The distance is taken forward from the marker,
 * wrapping through the lap length when the position is behind it.
 *
 * D_801D77B8 selects between those two phases and, when it is neither 0 nor
 * 1, the function returns without storing anything -- which is why the
 * store sits under a condition rather than at the end.
 *
 * The result is that distance plus the lap length times D_8007C32C, less
 * D_8007C32E: a lap counter and an offset, making the total a cumulative
 * race distance. The names stay at their addresses because "cumulative
 * distance" is an inference from shape, and a wrong name costs more than a
 * dull one.
 */
#include "m2c_macros.h"

extern s16 D_8007C210;
extern s16 D_801D77B8;
extern s32 D_8007C260;
extern s16 D_8007C32C;
extern s16 D_8007C32E;
extern s32 D_80173348;

void func_80021BE0(void) {
    s32 lap;
    s32 pos;
    s32 dist;
    s32 mark;
    s16 phase;

    lap = (D_8007C210 < 3) ? 0x10000 : 0x17000;

    phase = D_801D77B8;
    if (phase == 0) {
        pos = D_8007C260;
        if (pos < 0x2800) {
            dist = 0x2800 - pos;
        } else {
            dist = (lap + 0x2800) - pos;
        }
    } else if (phase == 1) {
        mark = (D_8007C210 < 3) ? 0xB900 : 0x12900;
        pos = D_8007C260;
        if (pos < mark) {
            dist = (lap - mark) + pos;
        } else {
            dist = pos - mark;
        }
    } else {
        return;
    }

    D_80173348 = dist + (lap * D_8007C32C - D_8007C32E);
}
