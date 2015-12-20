/*

 Package: dyncall
 Library: test
 File: test/ellipsis/ellipsis.cc
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



#include "config.h"
#include "../../dyncall/dyncall.h"
#include "../../dyncall/dyncall_value.h"


#if defined(__SUNPRO_CC) || defined(__ANDROID__)
#include <stdarg.h>
#else
#include <cstdarg>
#endif

DCValue mValue[NARGS];

void clearValues() { for(int i = 0;i<NARGS;++i) mValue[i].L = 0xCAFEBABEDEADC0DEULL; }

template<typename T> void g(T value, int pos);

template<> void g(DCchar value, int pos) { mValue[pos].c = value; }
template<> void g(DCshort value, int pos) { mValue[pos].s = value; }
template<> void g(DCint value, int pos) { mValue[pos].i = value; }
template<> void g(DClong value, int pos) { mValue[pos].j = value; }
template<> void g(DClonglong value, int pos) { mValue[pos].l = value; }
template<> void g(DCfloat value, int pos) { mValue[pos].f = value; }
template<> void g(DCdouble value, int pos) { mValue[pos].d = value; }
template<> void g(DCpointer value, int pos) { mValue[pos].p = value; }

DCValue* getArg(int pos) { return &mValue[pos]; }

int gID;
int getId() { return gID; }

extern "C" {

#define VF0(id,S) void S () {gID=id;}
#define VF1(id,A1,S) void S (A1 a1) {gID=id;g<A1>(a1,0);}
#define VF2(id,A1,A2,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);va_end(l);}
#define VF3(id,A1,A2,A3,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);g<A3>(va_arg(l,A3),2);va_end(l);}
#define VF4(id,A1,A2,A3,A4,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);g<A3>(va_arg(l,A3),2);g<A4>(va_arg(l,A4),3);va_end(l);}
#define VF5(id,A1,A2,A3,A4,A5,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);g<A3>(va_arg(l,A3),2);g<A4>(va_arg(l,A4),3);g<A5>(va_arg(l,A5),4);va_end(l);}
#define VF6(id,A1,A2,A3,A4,A5,A6,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);g<A3>(va_arg(l,A3),2);g<A4>(va_arg(l,A4),3);g<A5>(va_arg(l,A5),4);g<A6>(va_arg(l,A6),5);va_end(l);}
#define VF7(id,A1,A2,A3,A4,A5,A6,A7,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);g<A3>(va_arg(l,A3),2);g<A4>(va_arg(l,A4),3);g<A5>(va_arg(l,A5),4);g<A6>(va_arg(l,A6),5);g<A7>(va_arg(l,A7),6);va_end(l);}
#define VF8(id,A1,A2,A3,A4,A5,A6,A7,A8,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);g<A3>(a3,2);g<A4>(a4,3);g<A5>(a5,4);g<A6>(a6,5);g<A7>(a7,6);g<A8>(a8,7);va_end(l);}
#define VF9(id,A1,A2,A3,A4,A5,A6,A7,A8,A9,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);g<A3>(a3,2);g<A4>(a4,3);g<A5>(a5,4);g<A6>(a6,5);g<A7>(a7,6);g<A8>(a8,7);g<A9>(a9,8);va_end(l);}
#define VF10(id,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,S) void S (A1 a1, ...) {va_list l;va_start(l,a1);gID=id;g<A1>(a1,0);g<A2>(va_arg(l,A2),1);g<A3>(a3,2);g<A4>(a4,3);g<A5>(a5,4);g<A6>(a6,5);g<A7>(a7,6);g<A8>(a8,7);g<A9>(a9,8);g<A10>(a10,9);va_end(l);}

#include "case.h"

}

#undef VF0
#undef VF1
#undef VF2
#undef VF3
#undef VF4
#undef VF5
#undef VF6
#undef VF7
#undef VF8
#undef VF9
#undef VF10

#define VF0(id,S) (void*)S,
#define VF1(id,A1,S) (void*)S,
#define VF2(id,A1,A2,S) (void*)S,
#define VF3(id,A1,A2,A3,S) (void*)S,
#define VF4(id,A1,A2,A3,A4,S) (void*)S,
#define VF5(id,A1,A2,A3,A4,A5,S) (void*)S,
#define VF6(id,A1,A2,A3,A4,A5,A6,S) (void*)S,
#define VF7(id,A1,A2,A3,A4,A5,A6,A7,S) (void*)S,
#define VF8(id,A1,A2,A3,A4,A5,A6,A7,A8,S) (void*)S,
#define VF9(id,A1,A2,A3,A4,A5,A6,A7,A8,A9,S) (void*)S,
#define VF10(id,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,S) (void*)S,

DCpointer gFuncTable[] = {
#include "case.h"
};

DCpointer getFunc(int x) {
  return gFuncTable[x];
}
