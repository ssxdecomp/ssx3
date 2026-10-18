.macro glabel label
    .global \label
    .type \label, @function
    \label:
.endm
.macro dlabel label
    .global \label
    \label:
.endm

# Closes out a data symbol opened with glabel/dlabel so it gets a proper
# ELF size (current splat/spimdisasm emits this after every data symbol).
.macro enddlabel label
    .size \label, . - \label
.endm

# Marks a function as not-yet-matched. Current splat/spimdisasm emits this
# unconditionally before every function split, regardless of match status.
# Intentionally a no-op: emitting a `\label\().NON_MATCHING` object here puts
# a duplicate symbol on top of every function in obj/target, which objdiff
# lists as an unmatched symbol (obj/current is built with -DSKIP_ASM and
# never has them). objdiff already treats functions missing from
# obj/current as unmatched, so the marker isn't needed.
.macro nonmatching label, size=1
.endm
