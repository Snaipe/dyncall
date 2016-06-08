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
	.set    noreorder
	.set    nomacro

	/* Prolog. Just store the minimum, return address, frame pointer, spill area. */
	subu  $sp, 32       /* open frame: 32b for 8b aligned frame (retval+ra+fp+spill) */
	sw    $ra, 20($sp)  /* save link register */

	.frame  $fp,32,$31  /* specify our frame: fp,size,lr; creates virt $fp */

	/* Init return value */
	sw $zero, 24($sp)
	sw $zero, 28($sp)

	/* If we spill the first four, all arguments will be in one out in consecutive block */
	/* Caller doesn't and it's up to us to spill, so let's write $4-$7 ($a0-$a3) to the */
	/* dedicated spill area, first (at end of _caller's_ frame, so $fp points right to it). */
	sw $7, 12($fp)
	sw $6,  8($fp)
	sw $5,  4($fp)
	sw $4,  0($fp)

	/* Init DCArg, which contains stackptr* to the args, which is $fp. Use padding between */
	/* stored return address and parameter area as place to store it (hacky, but saves 8b) */
	sw $fp, 16($sp)

	/* Prepare callback handler call. */
	move  $4, $12       /* Param 0 = DCCallback*, $12 ($t4) holds pointer to thunk */
	addiu $5, $sp, 16   /* Param 1 = DCArgs*, pointer to where pointer to args is stored */
	addiu $6, $sp, 24   /* Param 2 = results pointer to 8b of local data on stack */
	lw    $7, 24($12)   /* Param 3 = userdata pointer */

	lw    $25, 20($12)  /* store handler entry in $25 ($t9), required for PIC */
	jalr  $25           /* jump */
	nop

	/* Copy result in corresponding registers $2-$3 ($v0-$v1) */
	lw    $2, 24($sp)
	lw    $3, 28($sp)

	/* Epilog. Tear down frame and return. */
	lw    $ra, 20($sp)  /* restore return address */
	addiu $sp, $sp, 32  /* close frame */
	j     $ra           /* return */
	nop

	.set    macro
	.set    reorder
	.end    dcCallbackThunkEntry
	.ident  "handwritten"

