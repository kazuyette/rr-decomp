/* Small, already-understood functions that don't yet have a better home. */

/* Empty callback / no-op hook. Immediately precedes _start in the binary;
 * exact purpose not yet identified, but the body (jr $ra; nop) is trivial
 * and matches byte-for-byte, so it's tracked here rather than left as raw
 * asm.
 */
void func_8003FA94(void) {
}
