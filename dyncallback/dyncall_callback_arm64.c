/*

 Package: dyncall
 Library: dyncallback
 File: dyncallback/dyncall_callback_arm64.c
 Description: Callback - Implementation for ARM64 / ARMv8 / AAPCS64
 License:

   Copyright (c) 2015 Daniel Adler <dadler@uni-goettingen.de>,
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

#include "dyncall_callback.h"
#include "dyncall_alloc_wx.h"
#include "dyncall_thunk.h"

extern void dcCallbackThunkEntry();

struct DCCallback
{
                                //  off  size
                                // ----|-----
  DCThunk            thunk;	//   0     32
  DCCallbackHandler* handler; 	//  32      8
  void*              userdata;	//  40      8
                                //
                                //  size   48 
                                // aligned 48 
};

void dcbInitCallback(DCCallback* pcb, const char* signature, DCCallbackHandler* handler, void* userdata)
{
  pcb->handler = handler;
  pcb->userdata = userdata;
}

DCCallback* dcbNewCallback(const char* signature, DCCallbackHandler* handler, void* userdata)
{
  int err;
  DCCallback* pcb;
  err = dcAllocWX(sizeof(DCCallback), (void**) &pcb);
  if (err != 0) return 0;

  dcbInitThunk(&pcb->thunk, dcCallbackThunkEntry);
  dcbInitCallback(pcb, signature, handler, userdata);
  return pcb;
}

void dcbFreeCallback(DCCallback* pcb)
{
  dcFreeWX(pcb, sizeof(DCCallback));
}

void* dcbGetUserData(DCCallback* pcb)
{
  return pcb->userdata;
}

