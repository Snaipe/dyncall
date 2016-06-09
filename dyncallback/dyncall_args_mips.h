/*

 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_args_mips.h
 Description: Callback's Arguments VM - Header for MIPS
 License:

   Copyright (c) 2013-2015 Daniel Adler <dadler@uni-goettingen.de>,
                           Tassilo Philipp <tphilipp@potion-studios.com>

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


#ifndef DYNCALLBACK_ARGS_MIPS_H
#define DYNCALLBACK_ARGS_MIPS_H

#include "dyncall_args.h"

struct DCArgs
{
	/* Don't change order! */
#if defined(DC__ABI_MIPS_O32)
	int freg_count;
#else
#  define DCARGS_MIPS_PARAM_REGS 8
	struct { int i; float f; } reg_data[DCARGS_MIPS_PARAM_REGS];
	struct { int i; int   f; } reg_count;
#endif
	unsigned char* stackptr;
};

#endif /* DYNCALLBACK_ARGS_MIPS_H */

