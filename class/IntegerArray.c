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



#line 33 "IntegerArray.d"
#include "array1.h" 

#define	CLASS	IntegerArray_c
#define	ivType	IntegerArray_iv_t

#include "generics.h"

object	IntegerArray_c;


#line 41 "IntegerArray.d"
#define TYPE int 


static gIndex_t _index; 


cvmeth objrtn IntegerArray_cvm_vNew(object self, va_list _rest_)
{ 
	unsigned rank = va_arg(_rest_, unsigned);

#line 49 "IntegerArray.d"
	static gNewArray_t cnew = NULL; 

	if (!cnew) 
		cnew = cmcPointer(Array, gNewArray); 
	return cnew(self, AT_INT, rank, _rest_); 
} 

#line 69 "IntegerArray.c"

static	objrtn	IntegerArray_cfm_vNew(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_cvm_vNew(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 56 "IntegerArray.d"
ivmeth char IntegerArray_ivm_vCharValue(object self, va_list _rest_)
{ 
	return (char) *((TYPE *) _index(self, _rest_)); 
} 

#line 89 "IntegerArray.c"

static	char	IntegerArray_ifm_vCharValue(object self, ...)
{
	va_list	_rest_;
	char	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vCharValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 61 "IntegerArray.d"
ivmeth short IntegerArray_ivm_vShortValue(object self, va_list _rest_)
{ 
	return (short) *((TYPE *) _index(self, _rest_)); 
} 

#line 109 "IntegerArray.c"

static	short	IntegerArray_ifm_vShortValue(object self, ...)
{
	va_list	_rest_;
	short	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vShortValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 66 "IntegerArray.d"
ivmeth unsigned short IntegerArray_ivm_vUnsignedShortValue(object self, va_list _rest_)
{ 
	return (unsigned short) *((TYPE *) _index(self, _rest_)); 
} 

#line 129 "IntegerArray.c"

static	unsigned short	IntegerArray_ifm_vUnsignedShortValue(object self, ...)
{
	va_list	_rest_;
	unsigned short	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vUnsignedShortValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 71 "IntegerArray.d"
ivmeth long IntegerArray_ivm_vLongValue(object self, va_list _rest_)
{ 
	return (long) *((TYPE *) _index(self, _rest_)); 
} 

#line 149 "IntegerArray.c"

static	long	IntegerArray_ifm_vLongValue(object self, ...)
{
	va_list	_rest_;
	long	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vLongValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 76 "IntegerArray.d"
ivmeth double IntegerArray_ivm_vDoubleValue(object self, va_list _rest_)
{ 
	return (double) *((TYPE *) _index(self, _rest_)); 
} 

#line 169 "IntegerArray.c"

static	double	IntegerArray_ifm_vDoubleValue(object self, ...)
{
	va_list	_rest_;
	double	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vDoubleValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 81 "IntegerArray.d"
ivmeth objrtn IntegerArray_ivm_vChangeValue(object self, va_list _rest_)
{ object val = va_arg(_rest_, object);
	ChkArg(val, 2); 
	*((TYPE *) _index(self, _rest_)) = (TYPE) gLongValue(val); 
	return self; 
} 

#line 191 "IntegerArray.c"

static	objrtn	IntegerArray_ifm_vChangeValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vChangeValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 88 "IntegerArray.d"
ivmeth objrtn IntegerArray_ivm_vChangeCharValue(object self, va_list _rest_)
{ int val = va_arg(_rest_, int);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 212 "IntegerArray.c"

static	objrtn	IntegerArray_ifm_vChangeCharValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vChangeCharValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 94 "IntegerArray.d"
ivmeth objrtn IntegerArray_ivm_vChangeShortValue(object self, va_list _rest_)
{ int val = va_arg(_rest_, int);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 233 "IntegerArray.c"

static	objrtn	IntegerArray_ifm_vChangeShortValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vChangeShortValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 100 "IntegerArray.d"
ivmeth objrtn IntegerArray_ivm_vChangeUShortValue(object self, va_list _rest_)
{ unsigned val = va_arg(_rest_, unsigned);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 254 "IntegerArray.c"

static	objrtn	IntegerArray_ifm_vChangeUShortValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vChangeUShortValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 106 "IntegerArray.d"
ivmeth objrtn IntegerArray_ivm_vChangeLongValue(object self, va_list _rest_)
{ long val = va_arg(_rest_, long);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 275 "IntegerArray.c"

static	objrtn	IntegerArray_ifm_vChangeLongValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vChangeLongValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 112 "IntegerArray.d"
ivmeth objrtn IntegerArray_ivm_vChangeDoubleValue(object self, va_list _rest_)
{ double val = va_arg(_rest_, double);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 296 "IntegerArray.c"

static	objrtn	IntegerArray_ifm_vChangeDoubleValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = IntegerArray_ivm_vChangeDoubleValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}


#line 118 "IntegerArray.d"
static void init_class(void) 
{ 
	_index = imcPointer(Array, gIndex); 
} 

#line 315 "IntegerArray.c"

objrtn	IntegerArray_initialize(void)
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

	if (IntegerArray_c) {
		LEAVECRITICALSECTION(cs);
		return IntegerArray_c;
	}
	INHIBIT_THREADER;
	NumberArray_initialize();
	if (IntegerArray_c)  {
		ENABLE_THREADER;
		LEAVECRITICALSECTION(cs);
		return IntegerArray_c;
	}
	IntegerArray_c = gNewClass(Class, "IntegerArray", 0, 0, NumberArray, END);
	cvMethodFor(IntegerArray, vNew, IntegerArray_cvm_vNew, IntegerArray_cfm_vNew);
	ivMethodFor(IntegerArray, vCharValue, IntegerArray_ivm_vCharValue, IntegerArray_ifm_vCharValue);
	ivMethodFor(IntegerArray, vChangeUShortValue, IntegerArray_ivm_vChangeUShortValue, IntegerArray_ifm_vChangeUShortValue);
	ivMethodFor(IntegerArray, vChangeValue, IntegerArray_ivm_vChangeValue, IntegerArray_ifm_vChangeValue);
	ivMethodFor(IntegerArray, vLongValue, IntegerArray_ivm_vLongValue, IntegerArray_ifm_vLongValue);
	ivMethodFor(IntegerArray, vChangeCharValue, IntegerArray_ivm_vChangeCharValue, IntegerArray_ifm_vChangeCharValue);
	ivMethodFor(IntegerArray, vUnsignedShortValue, IntegerArray_ivm_vUnsignedShortValue, IntegerArray_ifm_vUnsignedShortValue);
	ivMethodFor(IntegerArray, vChangeDoubleValue, IntegerArray_ivm_vChangeDoubleValue, IntegerArray_ifm_vChangeDoubleValue);
	ivMethodFor(IntegerArray, vDoubleValue, IntegerArray_ivm_vDoubleValue, IntegerArray_ifm_vDoubleValue);
	ivMethodFor(IntegerArray, vChangeShortValue, IntegerArray_ivm_vChangeShortValue, IntegerArray_ifm_vChangeShortValue);
	ivMethodFor(IntegerArray, vChangeLongValue, IntegerArray_ivm_vChangeLongValue, IntegerArray_ifm_vChangeLongValue);
	ivMethodFor(IntegerArray, vShortValue, IntegerArray_ivm_vShortValue, IntegerArray_ifm_vShortValue);

	init_class();

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return IntegerArray_c;
}



