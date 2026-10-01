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
# unconditionally before every function split, regardless of match status;
# it's purely an informational marker (scripts/matching_report.py filters
# symbols ending in .NON_MATCHING when reading objdiff's symbol table), so
# this just emits that marker object and has no effect on the actual code.
.macro nonmatching label, size=1
    .global \label\().NON_MATCHING
    .type \label\().NON_MATCHING, @object
    .size \label\().NON_MATCHING, \size
    \label\().NON_MATCHING:
.endm
