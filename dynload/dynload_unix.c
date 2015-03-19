/*

 Package: dyncall
 Library: dynload
 File: dynload/dynload_unix.c
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



/*

  dynload_unix.c

  dynload module for .so (unix) and .dylib (mach-o darwin/OS X) files

*/


#include "dynload.h"

#include <dlfcn.h>


DLLib* dlLoadLibrary(const char* libPath)
{
  return (DLLib*)dlopen(libPath,RTLD_NOW|RTLD_GLOBAL);
}


void* dlFindSymbol(DLLib* libHandle, const char* symbol)
{
  return dlsym((void*)libHandle, symbol);
}


void dlFreeLibrary(DLLib* libHandle)
{

  // Check for NULL for cross-platform consistency. *BSD seems
  // to do that in dlclose, Linux does not. POSIX states "if handle
  // does not refer to an open object, dlclose() returns a non-zero
  // value", which unfortunately sounds like it's not explicitly
  // specified.
  if(libHandle)
  	dlclose((void*)libHandle);
}

