# Rewrite the o32 temporaries $t0-$t7 to numeric $8-$15 before assembling.
#
# splat/spimdisasm emit o32 register names. Newer GNU as releases (seen with
# Homebrew's mips-linux-gnu-binutils 2.47) switched -mabi=eabi to the
# n32/n64 names, where $t0-$t3 mean $12-$15 and $t4-$t7 don't exist, so the
# same .s would silently mis-assemble. Numeric names are ABI-independent.
# Used by configure.py's `as` rule on macOS: perl -p tools/macos/o32_gpr_names.pl
s/\$t([0-7])(?![0-9A-Za-z_])/'$'.($1+8)/ge;
