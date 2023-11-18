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



#line 33 "FloatArray.d"
#include "array1.h" 

#define	CLASS	FloatArray_c
#define	ivType	FloatArray_iv_t

#include "generics.h"

object	FloatArray_c;


#line 41 "FloatArray.d"
#define TYPE float 


static gIndex_t _index; 


cvmeth objrtn FloatArray_cvm_vNew(object self, va_list _rest_)
{ 
	unsigned rank = va_arg(_rest_, unsigned);

#line 49 "FloatArray.d"
	static gNewArray_t cnew = NULL; 

	if (!cnew) 
		cnew = cmcPointer(Array, gNewArray); 
	return cnew(self, AT_FLOT, rank, _rest_); 
} 

#line 69 "FloatArray.c"

static	objrtn	FloatArray_cfm_vNew(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_cvm_vNew(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 56 "FloatArray.d"
ivmeth char FloatArray_ivm_vCharValue(object self, va_list _rest_)
{ 
	return (char) *((TYPE *) _index(self, _rest_)); 
} 

#line 89 "FloatArray.c"

static	char	FloatArray_ifm_vCharValue(object self, ...)
{
	va_list	_rest_;
	char	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vCharValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 61 "FloatArray.d"
ivmeth short FloatArray_ivm_vShortValue(object self, va_list _rest_)
{ 
	return (short) *((TYPE *) _index(self, _rest_)); 
} 

#line 109 "FloatArray.c"

static	short	FloatArray_ifm_vShortValue(object self, ...)
{
	va_list	_rest_;
	short	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vShortValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 66 "FloatArray.d"
ivmeth unsigned short FloatArray_ivm_vUnsignedShortValue(object self, va_list _rest_)
{ 
	return (unsigned short) *((TYPE *) _index(self, _rest_)); 
} 

#line 129 "FloatArray.c"

static	unsigned short	FloatArray_ifm_vUnsignedShortValue(object self, ...)
{
	va_list	_rest_;
	unsigned short	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vUnsignedShortValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 71 "FloatArray.d"
ivmeth long FloatArray_ivm_vLongValue(object self, va_list _rest_)
{ 
	return (long) *((TYPE *) _index(self, _rest_)); 
} 

#line 149 "FloatArray.c"

static	long	FloatArray_ifm_vLongValue(object self, ...)
{
	va_list	_rest_;
	long	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vLongValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 76 "FloatArray.d"
ivmeth double FloatArray_ivm_vDoubleValue(object self, va_list _rest_)
{ 
	return (double) *((TYPE *) _index(self, _rest_)); 
} 

#line 169 "FloatArray.c"

static	double	FloatArray_ifm_vDoubleValue(object self, ...)
{
	va_list	_rest_;
	double	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vDoubleValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 81 "FloatArray.d"
ivmeth objrtn FloatArray_ivm_vChangeValue(object self, va_list _rest_)
{ object val = va_arg(_rest_, object);
	ChkArg(val, 2); 
	*((TYPE *) _index(self, _rest_)) = gDoubleValue(val); 
	return self; 
} 

#line 191 "FloatArray.c"

static	objrtn	FloatArray_ifm_vChangeValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vChangeValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 88 "FloatArray.d"
ivmeth objrtn FloatArray_ivm_vChangeCharValue(object self, va_list _rest_)
{ int val = va_arg(_rest_, int);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 212 "FloatArray.c"

static	objrtn	FloatArray_ifm_vChangeCharValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vChangeCharValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 94 "FloatArray.d"
ivmeth objrtn FloatArray_ivm_vChangeShortValue(object self, va_list _rest_)
{ int val = va_arg(_rest_, int);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 233 "FloatArray.c"

static	objrtn	FloatArray_ifm_vChangeShortValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vChangeShortValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 100 "FloatArray.d"
ivmeth objrtn FloatArray_ivm_vChangeUShortValue(object self, va_list _rest_)
{ unsigned val = va_arg(_rest_, unsigned);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 254 "FloatArray.c"

static	objrtn	FloatArray_ifm_vChangeUShortValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vChangeUShortValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 106 "FloatArray.d"
ivmeth objrtn FloatArray_ivm_vChangeLongValue(object self, va_list _rest_)
{ long val = va_arg(_rest_, long);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 275 "FloatArray.c"

static	objrtn	FloatArray_ifm_vChangeLongValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vChangeLongValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 112 "FloatArray.d"
ivmeth objrtn FloatArray_ivm_vChangeDoubleValue(object self, va_list _rest_)
{ double val = va_arg(_rest_, double);
	*((TYPE *) _index(self, _rest_)) = (TYPE) val; 
	return self; 
} 

#line 296 "FloatArray.c"

static	objrtn	FloatArray_ifm_vChangeDoubleValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = FloatArray_ivm_vChangeDoubleValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}


#line 118 "FloatArray.d"
static void init_class(void) 
{ 
	_index = imcPointer(Array, gIndex); 
} 

#line 315 "FloatArray.c"

objrtn	FloatArray_initialize(void)
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

	if (FloatArray_c) {
		LEAVECRITICALSECTION(cs);
		return FloatArray_c;
	}
	INHIBIT_THREADER;
	NumberArray_initialize();
	if (FloatArray_c)  {
		ENABLE_THREADER;
		LEAVECRITICALSECTION(cs);
		return FloatArray_c;
	}
	FloatArray_c = gNewClass(Class, "FloatArray", 0, 0, NumberArray, END);
	cvMethodFor(FloatArray, vNew, FloatArray_cvm_vNew, FloatArray_cfm_vNew);
	ivMethodFor(FloatArray, vCharValue, FloatArray_ivm_vCharValue, FloatArray_ifm_vCharValue);
	ivMethodFor(FloatArray, vChangeUShortValue, FloatArray_ivm_vChangeUShortValue, FloatArray_ifm_vChangeUShortValue);
	ivMethodFor(FloatArray, vChangeValue, FloatArray_ivm_vChangeValue, FloatArray_ifm_vChangeValue);
	ivMethodFor(FloatArray, vLongValue, FloatArray_ivm_vLongValue, FloatArray_ifm_vLongValue);
	ivMethodFor(FloatArray, vChangeCharValue, FloatArray_ivm_vChangeCharValue, FloatArray_ifm_vChangeCharValue);
	ivMethodFor(FloatArray, vUnsignedShortValue, FloatArray_ivm_vUnsignedShortValue, FloatArray_ifm_vUnsignedShortValue);
	ivMethodFor(FloatArray, vChangeDoubleValue, FloatArray_ivm_vChangeDoubleValue, FloatArray_ifm_vChangeDoubleValue);
	ivMethodFor(FloatArray, vDoubleValue, FloatArray_ivm_vDoubleValue, FloatArray_ifm_vDoubleValue);
	ivMethodFor(FloatArray, vChangeShortValue, FloatArray_ivm_vChangeShortValue, FloatArray_ifm_vChangeShortValue);
	ivMethodFor(FloatArray, vChangeLongValue, FloatArray_ivm_vChangeLongValue, FloatArray_ifm_vChangeLongValue);
	ivMethodFor(FloatArray, vShortValue, FloatArray_ivm_vShortValue, FloatArray_ifm_vShortValue);

	init_class();

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return FloatArray_c;
}



