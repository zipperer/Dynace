/*
  Copyright (c) 1996 Blake McBride
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



/*  This file automatically generated by dpp - do not edit  */

#define	DPP_STRATEGY	2
#define	DPP_FASTWIDE	0




#define	CLASS	LinkObject_c
#define	ivType	LinkObject_iv_t

#include "generics.h"

object	LinkObject_c;


#line 35 "LinkObject.d"
#define FIRST gNext 
#define LAST gPrevious 

cvmeth objrtn LinkObject_cvm_vMakeList(object self, va_list _rest_)
{ 
	object lst, obj; 

	lst = gNew(self); 
	while (obj = GetArg(object)) 
		gAddBefore(lst, gNewWithObj(LinkValue, obj)); 
	return lst; 
} 

#line 62 "LinkObject.c"

static	objrtn	LinkObject_cfm_vMakeList(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = LinkObject_cvm_vMakeList(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 48 "LinkObject.d"
ivmeth objrtn LinkObject_ivm_vGetValues(object self, va_list _rest_)
{ 
	object *var, seq, obj; 

	seq = gSequence(self); 
	obj = gNext(seq); 
	while (var = GetArg(object *)) { 
		*var = obj; 
		if (obj) 
			obj = gNext(seq); 
	} 
	if (obj) 
		gDispose(seq); 
	return self; 
} 

#line 93 "LinkObject.c"

static	objrtn	LinkObject_ifm_vGetValues(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = LinkObject_ivm_vGetValues(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 64 "LinkObject.d"
imeth objrtn LinkObject_im_gAddFirst(object self, object obj)
{ 
	object lnk; 

	ChkArgNul(obj, 2); 
	lnk = gNewWithObj(LinkValue, obj); 

	gAddAfter(self, lnk); 
	return self; 
} 

imeth objrtn LinkObject_im_gPop(object self)
{ 

	object lnk = FIRST(self); 
	if (lnk) { 
		lnk = gValue(lnk); 
		gDisposeFirst(self); 
	} 
	return lnk; 
} 

imeth objrtn LinkObject_im_gFirst(object self)
{ 

	object lnk = FIRST(self); 
	return lnk ? gValue(lnk) : NULLOBJ; 
} 

imeth objrtn LinkObject_im_gAddLast(object self, object obj)
{ 
	object lnk; 

	ChkArgNul(obj, 2); 
	lnk = gNewWithObj(LinkValue, obj); 

	gAddBefore(self, lnk); 
	return self; 
} 

imeth objrtn LinkObject_im_gLast(object self)
{ 

	object lnk = LAST(self); 
	return lnk ? gValue(lnk) : NULLOBJ; 
} 

imeth objrtn LinkObject_im_gSequence(object self)
{ 
	return gNewWithObj(LinkObjectSequence, FIRST(self)); 
} 

imeth objrtn LinkObject_im_gSequenceLinks(object self)
{ 
	return gNewWithObj(LinkSequence, FIRST(self)); 
} 

imeth objrtn LinkObject_im_gNth(object self, int idx)
{ 
	object r = oSuper(LinkObject_c, gNth, self)(self, idx); 
	return r ? gValue(r) : NULLOBJ; 
} 


#line 172 "LinkObject.c"

objrtn	LinkObject_initialize(void)
{
	static  CRITICALSECTION  cs;
	static  int volatile once = 0;

	ENTERCRITICALSECTION(_CI_CS_);
	if (!once) {
		INITIALIZECRITICALSECTION(cs);
		once = 1;
	}
	LEAVECRITICALSECTION(_CI_CS_);

	ENTERCRITICALSECTION(cs);

	if (LinkObject_c) {
		LEAVECRITICALSECTION(cs);
		return LinkObject_c;
	}
	INHIBIT_THREADER;
	LinkList_initialize();
	if (LinkObject_c)  {
		ENABLE_THREADER;
		LEAVECRITICALSECTION(cs);
		return LinkObject_c;
	}
	LinkObject_c = gNewClass(Class, "LinkObject", 0, 0, LinkList, END);
	cvMethodFor(LinkObject, vMakeList, LinkObject_cvm_vMakeList, LinkObject_cfm_vMakeList);
	iMethodFor(LinkObject, gAddFirst, LinkObject_im_gAddFirst);
	iMethodFor(LinkObject, gPop, LinkObject_im_gPop);
	iMethodFor(LinkObject, gFirst, LinkObject_im_gFirst);
	iMethodFor(LinkObject, gPush, LinkObject_im_gAddFirst);
	iMethodFor(LinkObject, gLast, LinkObject_im_gLast);
	iMethodFor(LinkObject, gSequence, LinkObject_im_gSequence);
	ivMethodFor(LinkObject, vGetValues, LinkObject_ivm_vGetValues, LinkObject_ifm_vGetValues);
	iMethodFor(LinkObject, gSequenceLinks, LinkObject_im_gSequenceLinks);
	iMethodFor(LinkObject, gAddLast, LinkObject_im_gAddLast);
	iMethodFor(LinkObject, gNth, LinkObject_im_gNth);

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return LinkObject_c;
}



