/*

 Package: dyncall
 Library: test
 File: test/common/platformInit.h
 Description: 
 License:

   Copyright (c) 2007-2015 Daniel Adler <dadler@uni-goettingen.de>, 
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


#ifndef PLATFORMINIT_H
#define PLATFORMINIT_H


#include "../../dyncall/dyncall_macros.h"

#if defined(DC__OS_NDS)
#  include <nds.h>
#  include <stdio.h>
#elif defined(DC__OS_PSP)
#  include <pspkernel.h>
#  include <pspdebug.h>
#  include <pspdisplay.h>
#  include <stdio.h>
#  define printf pspDebugScreenPrintf
/* All other platforms, usually just pulling in standard headers and empty init function. */
#else
#  if defined(__cplusplus)
#    if defined(__SUNPRO_CC) || defined(__ANDROID__) /* needed by SunPro .. otherwise printf not included */
#      include <stdio.h>
#    else
#      include <cstdio>
#    endif
#  else
#    include <stdio.h>
#  endif
#endif


/* Init/shutdown forwards, should be used by every (portable) test. */
void dcTest_initPlatform();
void dcTest_deInitPlatform();


#endif /* PLATFORMINIT_H */

