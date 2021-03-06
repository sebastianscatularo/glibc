/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 *
 * Adapted for `long double' by Ulrich Drepper <drepper@cygnus.com>.
 * Changed to use fyl2xp1 for values near 1, <drepper@cygnus.com>.
 * Adapted for i686 instructions.
 */

#include <machine/asm.h>

	.section .rodata.cst8,"aM",@progbits,8

	.p2align 3
	.type one,@object
one:	.double 1.0
	ASM_SIZE_DIRECTIVE(one)
	/* It is not important that this constant is precise.  It is only
	   a value which is known to be on the safe side for using the
	   fyl2xp1 instruction.  */
	.type limit,@object
limit:	.double 0.29
	ASM_SIZE_DIRECTIVE(limit)


#ifdef PIC
# define MO(op) op##@GOTOFF(%edx)
#else
# define MO(op) op
#endif

	.text
ENTRY(__ieee754_logl)
	fldln2			// log(2)
	fldt	4(%esp)		// x : log(2)
	fucomi	%st
	jp	3f
#ifdef PIC
	LOAD_PIC_REG (dx)
#endif
	fld	%st		// x : x : log(2)
	fsubl	MO(one)		// x-1 : x : log(2)
	fld	%st		// x-1 : x-1 : x : log(2)
	fabs			// |x-1| : x-1 : x : log(2)
	fld	MO(limit)	// 0.29 : |x-1| : x-1 : x : log(2)
	fcomip	%st(1)		// |x-1| : x-1 : x : log(2)
	fstp	%st(0)		// x-1 : x : log(2)
	jc	2f
	fstp	%st(1)		// x-1 : log(2)
	fyl2xp1			// log(x)
	ret

2:	fstp	%st(0)		// x : log(2)
	fyl2x			// log(x)
	ret

3:	fstp	%st(1)
	ret
END (__ieee754_logl)

ENTRY(__logl_finite)
	fldln2			// log(2)
	fldt	4(%esp)		// x : log(2)
#ifdef PIC
	LOAD_PIC_REG (dx)
#endif
	fld	%st		// x : x : log(2)
	fsubl	MO(one)		// x-1 : x : log(2)
	fld	%st		// x-1 : x-1 : x : log(2)
	fabs			// |x-1| : x-1 : x : log(2)
	fld	MO(limit)	// 0.29 : |x-1| : x-1 : x : log(2)
	fcomip	%st(1)		// |x-1| : x-1 : x : log(2)
	fstp	%st(0)		// x-1 : x : log(2)
	jc	2b
	fstp	%st(1)		// x-1 : log(2)
	fyl2xp1			// log(x)
	ret
END(__logl_finite)
