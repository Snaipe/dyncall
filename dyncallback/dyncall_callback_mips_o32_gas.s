/*

 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_callback_mips_o32_gas.s
 Description: Callback Thunk - Implementation mips32 o32
 License:

   Copyright (c) 2016 Tassilo Philipp <tphilipp@potion-studios.com>

   Permission to use, copy, modify, and distribute this software for any
   purpose with or without fee is hereby granted, provided that the above
   copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
   ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

	/* input:
		$t4    -> thunk
		$t4+20 -> cb handler
		$t4+24 -> userdata
	*/

	.section .mdebug.abi32
	.previous
	.abicalls
	.text
	.align  2
	.globl dcCallbackThunkEntry
	.ent   dcCallbackThunkEntry
	.type  dcCallbackThunkEntry, @function

/* Called by thunk - thunk stores pointer to DCCallback in $12 ($t4), and pointer to called function in $25 ($t9, required for PIC) */
dcCallbackThunkEntry:
	.frame  $fp,32,$31      /* infos for debugger: reg use, sizes, */
	/*.mask   0x00000000,0    /* int stack usage, */
	/*.fmask  0x00000000,0    /* fp stack usage */
	.set    noreorder
	.set    nomacro

	/* Prolog. Just store the minimum, return address, frame pointer, spill area. */
	addiu $sp, $sp, -32   /* open frame: 32b for 8b aligned frame (retval+ra+fp+spill) */
	sw    $ra, 20($sp)    /* save link register */
	sw    $fp, 16($sp)    /* save frame pointer */
	nop
	move  $fp, $sp        /* frame pointer = sp */

	/* Since all arguments are in one consecutive block, we'll pass the pointer  */
	/* to them as second argument to the callback handler. Caller doesn't spill  */
	/* though, so let's write $4-$7 ($a0-$a3) to the dedicated spill area, first */
	/* (which is in _caller's_ frame).                                                  */
	sw $7, 44($sp)
	sw $6, 40($sp)
	sw $5, 36($sp)
	sw $4, 32($sp)

	/* Prepare callback handler call. */
	move  $4, $12        /* Param 0 = DCCallback*, $12 ($t4) holds pointer to thunk */
	addiu $5, $sp, 16    /* Param 1 = DCArgs*, basically location of where fp is stored */
	addiu $6, $sp, 24    /* Param 2 = results pointer to 8b of local data on stack */
	lw    $7, 24($12)    /* Param 3 = userdata pointer */

	lw    $25, 20($12)    /* store handler entry in $25 ($t9) */
	jalr  $25             /* jump */
	nop

	/* Epilog. Tear down frame and return. */
	move  $sp, $fp      /* restore stack pointer */
	nop
	lw    $ra, 20($sp)  /* restore return address */
	lw    $fp, 16($sp)  /* restore frame pointer */
	addiu $sp, $sp, 32  /* close frame */
	j     $ra           /* return */
	nop

	.set    macro
	.set    reorder
	.end    dcCallbackThunkEntry
	.ident  "handwritten"

