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



#line 32 "Array.d"
#ifdef _MSC_VER 
#if _MSC_VER > 1200 
#define _CRT_SECURE_NO_DEPRECATE 
#endif 


#line 36 "Array.d"
#endif 


#line 40 "Array.d"
#include <string.h> 
#include "memalloc.h" 


#include "array1.h" 
#include "array2.h" 

#define	CLASS	Array_c
#define	ivType	Array_iv_t

#include "generics.h"

object	Array_c;


#line 66 "Array.c"
typedef struct  _Array_iv_t  {
	char iType;
	unsigned iRank;
	INDEX_TYPE * iShape;
	INDEX_TYPE iNelm;
	void * iArray;
	void * iRmp;
}	Array_iv_t;


#line 58 "Array.d"
#ifdef PROFILE 
#undef PMETHOD 
#define PMETHOD 
#endif 


#line 64 "Array.d"
static int Index_origin = 0; 

static int _A_esize(int type); 
static void print_val(object str,ivType *iv,char *fmt1,char *fmt2); 
static void p_val_mat(object str,unsigned rank,unsigned *shape,char **val ,int size,char *fmt,unsigned *bit_indx,char *buf, int typ); 
static objrtn print_nest(object s, ivType *iv); 
static objrtn Array_Dup(object self,int ntype,int dval,int deep); 
static int convert(ivType *iv,ivType *iv2); 



static unsigned char pow1[] = { 1, 2, 4, 8, 16, 32, 64, 128 }; 
static unsigned char pow2[] = { ~1, ~2, ~4, ~8, ~16, ~32, ~64, 
		(unsigned char)~128 }; 

static char OOB[] = "Error: Out of bounds array index.\n"; 


cmeth objrtn Array_cm_gNew(object self)
{ 
	return gShouldNotImplement(self, "gNew"); 
} 

cmeth objrtn Array_cm_gNewArray(object self, int type, int rank, va_list _rest_)
{ 
	int i; 
	INDEX_TYPE n; 
	object array = oSuper(Array_c, gNew, self)(self); 
	ivType *iv = ivPtr(array); 

	iv->iType = type; 
	iv->iRank = rank; 
	iv->iShape = rank ? MTnalloc(INDEX_TYPE, rank, iv->iShape) : (INDEX_TYPE *) NULL; 
	for (i=0, n=1 ; i < rank ; ++i) 
		n *= iv->iShape[i] = GetArg(unsigned); 
	iv->iNelm = n; 
	if (type == AT_OBJ) { 
		iv->iArray = n ? Tncalloc(char, (unsigned) SIZE(type, n)) : NULL; 
		iv->iRmp = gRegisterMemory(Dynace, iv->iArray, (long) SIZE(type, n)); 
	} else 
		iv->iArray = n ? MTncalloc(char, (unsigned) SIZE(type, n), iv->iArray) : NULL; 
	return array; 
} 



PMETHOD objrtn Array_NewArray(object self, int type, int rank, unsigned *idx)
{ 
	int i; 
	INDEX_TYPE n; 
	object array = oSuper(Array_c, gNew, self)(self); 
	ivType *iv = ivPtr(array); 

	iv->iType = type; 
	iv->iRank = rank; 
	iv->iShape = rank ? MTnalloc(INDEX_TYPE, rank, iv->iShape) : (INDEX_TYPE *) NULL; 
	for (i=0, n=1 ; i < rank ; ++i) 
		n *= iv->iShape[i] = idx[i]; 
	iv->iNelm = n; 
	if (type == AT_OBJ) { 
		iv->iArray = n ? Tncalloc(char, (unsigned) SIZE(type, n)) : NULL; 
		iv->iRmp = gRegisterMemory(Dynace, iv->iArray, (long) SIZE(type, n)); 
	} else 
		iv->iArray = n ? MTncalloc(char, (unsigned) SIZE(type, n), iv->iArray) : NULL; 
	return array; 
} 

imeth objrtn Array_im_gDispose(object self)
{ Array_iv_t *iv = GetIVs(Array, self);
	if (iv->iShape) 
		MA_free(iv->iShape); 
	if (iv->iArray) 
		if (iv->iType == AT_OBJ) 
		free(iv->iArray); 
	else 
		MA_free(iv->iArray); 
	if (iv->iRmp) 
		gRemoveRegisteredMemory(Dynace, iv->iRmp); 
	oSuper(Array_c, gDispose, self)(self); 
	return NULL; 
} 

imeth objrtn Array_im_gDeepDispose(object self)
{ Array_iv_t *iv = GetIVs(Array, self);
	object *v; 
	INDEX_TYPE i; 

	if (iv->iType == AT_OBJ) { 
		v = (object *) iv->iArray; 
		for (i=0 ; i != iv->iNelm ; ++i) 
			if (v[i]) { 
			gDeepDispose(v[i]); 
			v[i] = NULL; 
		} 
	} 

	if (iv->iShape) 
		MA_free(iv->iShape); 
	if (iv->iArray) 
		if (iv->iType == AT_OBJ) 
		free(iv->iArray); 
	else 
		MA_free(iv->iArray); 
	if (iv->iRmp) 
		gRemoveRegisteredMemory(Dynace, iv->iRmp); 
	oSuper(Array_c, gDispose, self)(self); 
	return NULL; 
} 

imeth void * Array_im_gArrayPointer(object self)
{ Array_iv_t *iv = GetIVs(Array, self);
	return iv->iArray; 
} 

imeth unsigned Array_im_gRank(object self)
{ Array_iv_t *iv = GetIVs(Array, self);
	return iv->iRank; 
} 

imeth objrtn Array_im_gShape(object self)
{ Array_iv_t *iv = GetIVs(Array, self);
	unsigned i; 
	object r; 
	ivType *iv2; 

	r = vNew(ShortArray, 1, iv->iRank); 
	iv2 = ivPtr(r); 

	for (i=0 ; i < iv->iRank ; ++i) 
		((INDEX_TYPE *) iv2->iArray)[i] = iv->iShape[i]; 

	return r; 
} 

imeth void * Array_im_gIndex(object self, va_list _rest_)
{ Array_iv_t *iv = GetIVs(Array, self);
	INDEX_TYPE offset, r, i; 

	if (iv->iType == AT_BIT) 
		gError(self, "Cannot use gIndex on BitArray\n"); 
	if (!iv->iRank) 
		return iv->iArray; 
	r = iv->iRank - 1; 
	for (i=0, offset=(INDEX_TYPE) 0 ; i <= r ; ++i) { 
		INDEX_TYPE m, n, j; 

		n = GetArg(unsigned) - Index_origin; 
		if (n >= iv->iShape[i]) 
			gError(self, OOB); 
		for (m=1, j=r ; j != i ; ) 
			m *= iv->iShape[j--]; 
		if (!m) 
			gError(self, OOB); 
		offset += m * n; 
	} 
	return (void *) ((char *) iv->iArray + _A_esize(iv->iType) * offset); 
} 

ivmeth int Array_ivm_vBitValue(object self, va_list _rest_)
{ Array_iv_t *iv = GetIVs(Array, self);
	int i, r; 
	INDEX_TYPE offset; 
	MAKE_REST(self); 

	if (iv->iType != AT_BIT) 
		gError(self, "Error: Can't use vBitValue on non-BitArrays\n"); 
	r = iv->iRank - 1; 
	for (i=0, offset=(INDEX_TYPE) 0 ; i <= r ; ++i) { 
		INDEX_TYPE m; 
		INDEX_TYPE n; 
		register int j; 

		n = GetArg(INDEX_TYPE) - Index_origin; 
		if (n >= iv->iShape[i]) 
			gError(self, OOB); 
		for (m=1, j=r ; j != i ; ) 
			m *= iv->iShape[j--]; 
		if (!m) 
			gError(self, OOB); 
		offset += m * n; 
	} 
	return !!BIT_VAL(iv->iArray, offset); 
} 

#line 269 "Array.c"

static	int	Array_ifm_vBitValue(object self, ...)
{
	va_list	_rest_;
	int	_ret_;
	va_start(_rest_, self);
	_ret_ = Array_ivm_vBitValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 248 "Array.d"
ivmeth objrtn Array_ivm_vChangeBitValue(object self, va_list _rest_)
{ Array_iv_t *iv = GetIVs(Array, self);int v = va_arg(_rest_, int);
	int i, r; 
	INDEX_TYPE offset; 
	MAKE_REST(v); 

	if (iv->iType != AT_BIT) 
		gError(self, "Error: Can't use vChangeBitValue on non-BitArrays\n"); 
	r = iv->iRank - 1; 
	for (i=0, offset=(INDEX_TYPE) 0 ; i <= r ; ++i) { 
		INDEX_TYPE m; 
		INDEX_TYPE n; 
		register int j; 

		n = GetArg(INDEX_TYPE) - Index_origin; 
		if (n >= iv->iShape[i]) 
			gError(self, OOB); 
		for (m=1, j=r ; j != i ; ) 
			m *= iv->iShape[j--]; 
		if (!m) 
			gError(self, OOB); 
		offset += m * n; 
	} 
	SET_BIT(iv->iArray, offset, v); 
	return self; 
} 

#line 311 "Array.c"

static	objrtn	Array_ifm_vChangeBitValue(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = Array_ivm_vChangeBitValue(self, _rest_);
	va_end(_rest_);
	return _ret_;
}



#line 275 "Array.d"
cmeth objrtn Array_cm_gIota(object self, int n)
{ 
	INDEX_TYPE c; 
	int i; 
	object a; 
	ivType *iv; 

	USE(self); 
	a = vNew(ShortArray, 1, n); 
	iv = ivPtr(a); 
	for (c=Index_origin, i=0 ; i < n ; ) 
		((short *) iv->iArray)[i++] = c++; 
	return a; 
} 

ivmeth objrtn Array_ivm_vReshape(object self, va_list _rest_)
{ Array_iv_t *iv = GetIVs(Array, self);unsigned rank = va_arg(_rest_, unsigned);
	INDEX_TYPE n, *shape, d, i; 
	MAKE_REST(rank); 

	shape = rank ? MTnalloc(INDEX_TYPE, rank, iv->iShape) : (INDEX_TYPE *) NULL; 
	for (i=0, n=1 ; i < rank ; ++i) { 
		d = GetArg(INDEX_TYPE); 
		n *= d; 
		shape[i] = d; 
	} 

	if (iv->iNelm != n) { 
		char *fp, *tp; 
		void *array; 
		INDEX_TYPE s1, s2, s1org; 

		s1org = s1 = SIZE(iv->iType, iv->iNelm); 
		s2 = SIZE(iv->iType, n); 
		if (iv->iType == AT_OBJ) 
			array = n ? Tncalloc(char, s2) : NULL; 
		else 
			array = n ? MTncalloc(char, s2, iv->iArray) : NULL; 

		fp = (char *) iv->iArray; 
		tp = (char *) array; 
		while (s2) { 
			unsigned m; 

			m = s2 < s1 ? s2 : s1; 
			memcpy(tp, fp, m); 
			s2 -= m; 
			s1 -= m; 
			if (!s1) { 
				fp = (char *) iv->iArray; 
				s1 = s1org; 
			} else 
				fp += m; 
			tp += m; 
		} 
		if (iv->iArray) 
			if (iv->iType == AT_OBJ) 
			free(iv->iArray); 
		else 
			MA_free(iv->iArray); 
		iv->iArray = array; 

		iv->iNelm = n; 
		if (iv->iType == AT_OBJ) { 
			void *rmp = gRegisterMemory(Dynace, iv->iArray, (long) SIZE(iv->iType, iv->iNelm)); 
			gRemoveRegisteredMemory(Dynace, iv->iRmp); 
			iv->iRmp = rmp; 
		} 
	} 
	iv->iRank = rank; 
	if (iv->iShape) 
		MA_free(iv->iShape); 
	iv->iShape = shape; 

	return self; 
} 

#line 403 "Array.c"

static	objrtn	Array_ifm_vReshape(object self, ...)
{
	va_list	_rest_;
	objrtn	_ret_;
	va_start(_rest_, self);
	_ret_ = Array_ivm_vReshape(self, _rest_);
	va_end(_rest_);
	return _ret_;
}


#line 354 "Array.d"
static int _A_esize(int type) 
{ 
	switch (type) { 
		case AT_CHAR: return sizeof(char); 
		case AT_SHRT: return sizeof(short); 
		case AT_USHT: return sizeof(_ushort); 
		case AT_INT: return sizeof(int); 
		case AT_LONG: return sizeof(long); 
		case AT_FLOT: return sizeof(float); 
		case AT_DBLE: return sizeof(double); 
		case AT_OBJ: return sizeof(object); 
		case AT_BIT: return 0; 
		case AT_PNTR: return sizeof(char *); 
		default: return 0; 
	} 
} 

imeth int Array_im_gSize(object self)
{ Array_iv_t *iv = GetIVs(Array, self);
	return iv->iNelm; 
} 

imeth int Array_im_gEqual(object self, object obj)
{ Array_iv_t *iv = GetIVs(Array, self);
	ivType *iv2; 
	unsigned i; 

	ChkArg(obj, 2); 
	if (!gIsKindOf(obj, CLASS)) 
		return 0; 
	iv2 = ivPtr(obj); 
	if (iv->iType != iv2->iType || iv->iRank != iv2->iRank || iv->iNelm != iv2->iNelm) 
		return 0; 
	for (i=0 ; i < iv->iRank ; ++i) 
		if (iv->iShape[i] != iv2->iShape[i]) 
		return 0; 
	return iv->iArray ? !memcmp(iv->iArray, iv2->iArray, (int) SIZE(iv->iType, iv->iNelm)) : 1; 
} 

imeth objrtn Array_im_gStringRepValue(object self)
{ Array_iv_t *iv = GetIVs(Array, self);
	object s; 

	s = gNew(String); 
	switch (iv->iType) { 
		case AT_CHAR: print_val(s, iv, "%c", "%c"); break; 
		case AT_SHRT: print_val(s, iv, "%hd ", "%6hd "); break; 
		case AT_USHT: print_val(s, iv, "%hu ", "%5hu "); break; 
		case AT_INT: print_val(s, iv, "%d ", "%6d "); break; 
		case AT_LONG: print_val(s, iv, "%ld ", "%10ld "); break; 
		case AT_FLOT: print_val(s, iv, "%hf ", "%10.2hf "); break; 
		case AT_DBLE: print_val(s, iv, "%lf ", "%10.2lf "); break; 
		case AT_OBJ: print_nest(s, iv); break; 
		case AT_BIT: print_val(s, iv, "%d ", "%1d "); break; 
		case AT_PNTR: print_val(s, iv, "%lx ", "%8lx "); break; 
	} 
	return s; 
} 

imeth objrtn Array_im_gStringRep(object self)
{ Array_iv_t *iv = GetIVs(Array, self);
	char *t, buf[60]; 
	object s; 

	switch (iv->iType) { 
		case AT_CHAR: t = "Character"; break; 
		case AT_SHRT: t = "Short"; break; 
		case AT_USHT: t = "Unsigned Short"; break; 
		case AT_INT: t = "Integer"; break; 
		case AT_LONG: t = "Long"; break; 
		case AT_FLOT: t = "Float"; break; 
		case AT_DBLE: t = "Double"; break; 
		case AT_OBJ: t = "Object Array"; break; 
		case AT_BIT: t = "Bit"; break; 
		case AT_PNTR: t = "Pointer"; break; 
		default: t = "Unknown"; break; 
	} 
	s = vSprintf(String, "Type  = %s\n", t); 
	sprintf(buf, "Rank  = %d\n", (int) iv->iRank); 
	gAppend(s, (object) buf); 

	if (iv->iRank) { 
		unsigned i; 

		gAppend(s, (object) "Shape = "); 
		for (i=0 ; i < iv->iRank ; ) { 
			sprintf(buf, PRNT_SHAPE, iv->iShape[i++]); 
			gAppend(s, (object) buf); 
		} 
		gAppend(s, (object) "\n"); 
	} 
	gAppend(s, (object) "Value = "); 
	switch (iv->iType) { 
		case AT_CHAR: print_val(s, iv, "%c", "%c"); break; 
		case AT_SHRT: print_val(s, iv, "%hd ", "%6hd "); break; 
		case AT_USHT: print_val(s, iv, "%hu ", "%5hu "); break; 
		case AT_INT: print_val(s, iv, "%d ", "%6d "); break; 
		case AT_LONG: print_val(s, iv, "%ld ", "%10ld "); break; 
		case AT_FLOT: print_val(s, iv, "%hf ", "%10.2hf "); break; 
		case AT_DBLE: print_val(s, iv, "%lf ", "%10.2lf "); break; 
		case AT_OBJ: print_nest(s, iv); break; 
		case AT_BIT: print_val(s, iv, "%d ", "%1d "); break; 
		case AT_PNTR: print_val(s, iv, "%lx ", "%8lx "); break; 
	} 
	return s; 
} 

static void _fmt(char *buf, char *fmt, void *var, int typ) 
{ 
	switch (typ) { 
		case AT_CHAR: sprintf(buf, fmt, *((char *) var)); break; 
		case AT_SHRT: sprintf(buf, fmt, *((short *) var)); break; 
		case AT_USHT: sprintf(buf, fmt, *((_ushort *) var)); break; 
		case AT_INT: sprintf(buf, fmt, *((int *) var)); break; 
		case AT_LONG: sprintf(buf, fmt, *((long *) var)); break; 
		case AT_FLOT: sprintf(buf, fmt, *((float *) var)); break; 
		case AT_DBLE: sprintf(buf, fmt, *((double *) var)); break; 
		case AT_OBJ: sprintf(buf, fmt, *((object *) var)); break; 
		case AT_PNTR: sprintf(buf, fmt, *((void **) var)); break; 
	} 
} 

static void print_val(object str, ivType *iv, char *fmt1, char *fmt2) 
{ 
	INDEX_TYPE i, bit_indx = 0; 
	int s = _A_esize(iv->iType); 
	char buf[60], *val; 

	switch (iv->iRank) { 
		case 0: if (iv->iType != AT_BIT) { 
			_fmt(buf, fmt1, iv->iArray, iv->iType); 
			if (iv->iType == AT_CHAR) 
				vBuild(str, NULL, "\"", buf, "\"\n", NULL); 
			else 
				vBuild(str, NULL, buf, "\n", NULL); 
		} else { 
			sprintf(buf, fmt1, !!BIT_VAL(iv->iArray, 0)); 
			vBuild(str, NULL, buf, "\n", NULL); 
		} 
		break; 
		case 1: if (iv->iType != AT_BIT) { 
			if (iv->iType == AT_CHAR) 
				gAppend(str, (object) "\""); 
			val = (char *) iv->iArray; 
			for (i=0 ; i++ != *iv->iShape ; val+=s) { 
				_fmt(buf, fmt1, val, iv->iType); 
				gAppend(str, (object) buf); 
			} 
			if (iv->iType == AT_CHAR) 
				gAppend(str, (object) "\""); 
		} else 
			for (i=0 ; i != *iv->iShape ; ++i) { 
			sprintf(buf, fmt1, !!BIT_VAL(iv->iArray, i)); 
			gAppend(str, (object) buf); 
		} 
		gAppend(str, (object) "\n"); 
		break; 
		default:gAppend(str, (object) "\n\n"); 
		val = (char *) iv->iArray; 
		p_val_mat(str, iv->iRank, iv->iShape, &val, s, fmt2, &bit_indx, buf, iv->iType); 
	} 
} 

static void p_val_mat(object str, unsigned rank, INDEX_TYPE *shape, char **val, int size, char *fmt, INDEX_TYPE *bit_indx, char *buf, int type) 
{ 
	INDEX_TYPE r, c; 

	if (rank == 2) 
		if (size) 
		for (r=0 ; r++ != *shape ; ) { 
		for (c=0 ; c++ != shape[1] ; (*val)+=size) { 
			_fmt(buf, fmt, *val, type); 
			gAppend(str, (object) buf); 
		} 
		gAppend(str, (object) "\n"); 
	} 
	else 
		for (r=0 ; r++ != *shape ; ) { 
		for (c=0 ; c++ != shape[1] ; (*bit_indx)++) { 
			sprintf(buf, fmt, !!BIT_VAL(*val, *bit_indx)); 
			gAppend(str, (object) buf); 
		} 
		gAppend(str, (object) "\n"); 
	} 
	else 
		for (r=0 ; r++ != *shape ; ) { 
		p_val_mat(str, rank-1, shape+1, val, size, fmt, bit_indx, buf, type); 
		gAppend(str, (object) "\n"); 
	} 
} 

static objrtn print_nest(object s, ivType *iv) 
{ 
	INDEX_TYPE i; 
	object *val = (object *) iv->iArray; 
	object t; 

	for (i=0 ; i++ != iv->iNelm ; ) { 
		if (t = *val++) { 
			t = gStringRepValue(*val++); 
			vBuild(s, NULL, "\n", t, "\n", NULL); 
			gDispose(t); 
		} else 
			gAppend(s, (object) "NULL\n"); 
	} 
	return s; 
} 



PMETHOD objrtn Array_Dup(object self, int ntype, int dval, int deep)



{ Array_iv_t *iv = GetIVs(Array, self);
	register unsigned i; 
	object narray, cls; 
	ivType *iv2; 

	if (!ntype) 
		ntype = iv->iType; 
	if (ntype != iv->iType && ( 
		ntype == AT_OBJ || ntype == AT_PNTR || 
		iv->iType == AT_OBJ || iv->iType == AT_PNTR)) 
		gError(self, "Error:  Can't convert array to requested type.\n"); 

	switch (ntype) { 
		case AT_CHAR: cls = CharacterArray; break; 
		case AT_SHRT: cls = ShortArray; break; 
		case AT_USHT: cls = UnsignedShortArray; break; 
		case AT_INT: cls = IntegerArray; break; 
		case AT_LONG: cls = LongArray; break; 
		case AT_FLOT: cls = FloatArray; break; 
		case AT_DBLE: cls = DoubleFloatArray; break; 
		case AT_BIT: cls = BitArray; break; 
		case AT_OBJ: cls = ObjectArray; break; 
		case AT_PNTR: cls = PointerArray; break; 
		default: cls = NULL; break; 
	} 
	narray = Array_NewArray(cls, ntype, iv->iRank, iv->iShape); 
	iv2 = ivPtr(narray); 

	if (dval) 
		if (ntype == iv->iType) 
		if (iv->iType == AT_OBJ && deep) { 
		object *fv = (object *) iv->iArray; 
		object *tv = (object *) iv2->iArray; 
		for (i=0 ; i != iv->iNelm ; ++i) 
			if (fv[i]) 
			tv[i] = gDeepCopy(fv[i]); 
	} else 
		memcpy(iv2->iArray, iv->iArray, (int) SIZE(iv->iType, iv->iNelm)); 
	else 
		convert(iv, iv2); 
	return narray; 
} 

#define Ftod(x) (double)(x) 
#define Dtol(x) (long)(x) 

#if 0 
#define CONV(tt, ft) while (n--) *((tt *) nval)++ = (tt) *((ft *) val)++ 
#define CONVFI(tt, ft) while (n--) *((tt *) nval)++ = (tt) Dtol((double)*((ft *) val)++) 
#define CONVFD() while (n--) *((double *) nval)++ = Ftod(*((float *) val)++) 
#define CONVFB(tt) while (n--) *((tt *) nval)++ = (tt) !!BIT_VAL(val, n) 
#define CONVTB(ft) for (m=0 ; m != n ; m++) SET_BIT(nval, m, *((ft *) val)++) 
#else 


#line 626 "Array.d"
#define CONV(tt, ft) while (n--) { *((tt *) nval) = (tt) *((ft *) val); nval = (void *) (1 + (tt *) nval); val = (void *) (1 + (ft *) val); } 

#line 632 "Array.d"
#define CONVFI(tt, ft) while (n--) { *((tt *) nval) = (tt) Dtol((double)*(ft *) val); nval = (void *) (1 + (tt *) nval); val = (void *) (1 + (ft *) val); } 

#line 638 "Array.d"
#define CONVFD() while (n--) { *((double *) nval) = Ftod(*((float *) val)); nval = (void *) (1 + (double *) nval); val = (void *) (1 + (float *) val); } 




#define CONVFB(tt) while (n--) { *((tt *) nval) = (tt) !!BIT_VAL(val, n); nval = (void *) (1 + (tt *) nval); } 




#define CONVTB(ft) for (m=0 ; m != n ; m++) { SET_BIT(nval, m, *((ft *) val)); val = (void *) (1 + (ft *) val); } 
#endif 


#line 651 "Array.d"
static int convert(ivType *iv, ivType *iv2) 
{ 
	INDEX_TYPE m; 
	INDEX_TYPE n = iv->iNelm; 
	void *val = iv->iArray; 
	void *nval = iv2->iArray; 

	switch (iv2->iType) { 
		case AT_CHAR: 
		switch (iv->iType) { 
			case AT_SHRT: CONV(char, short); break; 
			case AT_USHT: CONV(char, _ushort); break; 
			case AT_INT: CONV(char, int); break; 
			case AT_LONG: CONV(char, long); break; 
			case AT_FLOT: CONVFI(char, float); break; 
			case AT_DBLE: CONVFI(char, double); break; 
			case AT_BIT: CONVFB(char); break; 
			default: return(1); break; 
		} 
		break; 
		case AT_SHRT: 
		switch (iv->iType) { 
			case AT_CHAR: CONV(short, char); break; 
			case AT_USHT: CONV(short, _ushort); break; 
			case AT_INT: CONV(short, int); break; 
			case AT_LONG: CONV(short, long); break; 
			case AT_FLOT: CONVFI(short, float); break; 
			case AT_DBLE: CONVFI(short, double); break; 
			case AT_BIT: CONVFB(short); break; 
			default: return(1); break; 
		} 
		break; 
		case AT_USHT: 
		switch (iv->iType) { 
			case AT_CHAR: CONV(_ushort, char); break; 
			case AT_SHRT: CONV(_ushort, short); break; 
			case AT_INT: CONV(_ushort, int); break; 
			case AT_LONG: CONV(_ushort, long); break; 
			case AT_FLOT: CONVFI(_ushort, float); break; 
			case AT_DBLE: CONVFI(_ushort, double); break; 
			case AT_BIT: CONVFB(_ushort); break; 
			default: return(1); break; 
		} 
		break; 
		case AT_INT: 
		switch (iv->iType) { 
			case AT_CHAR: CONV(int, char); break; 
			case AT_SHRT: CONV(int, short); break; 
			case AT_USHT: CONV(int, _ushort); break; 
			case AT_LONG: CONV(int, long); break; 
			case AT_FLOT: CONVFI(int, float); break; 
			case AT_DBLE: CONVFI(int, double); break; 
			case AT_BIT: CONVFB(int); break; 
			default: return(1); break; 
		} 
		break; 
		case AT_LONG: 
		switch (iv->iType) { 
			case AT_CHAR: CONV(long, char); break; 
			case AT_SHRT: CONV(long, short); break; 
			case AT_USHT: CONV(long, _ushort); break; 
			case AT_INT: CONV(long, int); break; 
			case AT_FLOT: CONVFI(long, float); break; 
			case AT_DBLE: CONVFI(long, double); break; 
			case AT_BIT: CONVFB(long); break; 
			default: return(1); break; 
		} 
		break; 
		case AT_FLOT: 
		switch (iv->iType) { 
			case AT_CHAR: CONV(float, char); break; 
			case AT_SHRT: CONV(float, short); break; 
			case AT_USHT: CONV(float, _ushort); break; 
			case AT_INT: CONV(float, int); break; 
			case AT_LONG: CONV(float, long); break; 
			case AT_DBLE: CONV(float, double); break; 
			case AT_BIT: CONVFB(float); break; 
			default: return(1); break; 
		} 
		break; 
		case AT_DBLE: 
		switch (iv->iType) { 
			case AT_CHAR: CONV(double, char); break; 
			case AT_SHRT: CONV(double, short); break; 
			case AT_USHT: CONV(double, _ushort); break; 
			case AT_INT: CONV(double, int); break; 
			case AT_LONG: CONV(double, long); break; 
			case AT_FLOT: CONVFD(); break; 
			case AT_BIT: CONVFB(double); break; 
			default: return(1); break; 
		} 
		break; 
		case AT_BIT: 
		switch (iv->iType) { 
			case AT_CHAR: CONVTB(char); break; 
			case AT_SHRT: CONVTB(short); break; 
			case AT_USHT: CONVTB(_ushort); break; 
			case AT_INT: CONVTB(int); break; 
			case AT_LONG: CONVTB(long); break; 
			case AT_FLOT: CONVTB(float); break; 
			case AT_DBLE: CONVTB(double); break; 
			default: return(1); break; 
		} 
		break; 
		default: return(1); break; 
	} 
	return(0); 
} 

imeth objrtn Array_im_gCopy(object self)
{ 
	return Array_Dup(self, 0, 1, 0); 
} 

imeth objrtn Array_im_gDeepCopy(object self)
{ 
	return Array_Dup(self, 0, 1, 1); 
} 

cmeth objrtn Array_cm_gIndexOrigin(object self, int n)
{ 
	Index_origin = n; 
	return self; 
} 

#line 833 "Array.c"

objrtn	Array_initialize(void)
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

	if (Array_c) {
		LEAVECRITICALSECTION(cs);
		return Array_c;
	}
	INHIBIT_THREADER;
	Array_c = gNewClass(Class, "Array", sizeof(Array_iv_t), 0, END);
	cMethodFor(Array, gIndexOrigin, Array_cm_gIndexOrigin);
	cMethodFor(Array, gNew, Array_cm_gNew);
	cMethodFor(Array, gIota, Array_cm_gIota);
	cMethodFor(Array, gNewArray, Array_cm_gNewArray);
	ivMethodFor(Array, vReshape, Array_ivm_vReshape, Array_ifm_vReshape);
	iMethodFor(Array, gArrayPointer, Array_im_gArrayPointer);
	iMethodFor(Array, gShape, Array_im_gShape);
	iMethodFor(Array, gSize, Array_im_gSize);
	iMethodFor(Array, gDispose, Array_im_gDispose);
	iMethodFor(Array, gEqual, Array_im_gEqual);
	ivMethodFor(Array, vChangeBitValue, Array_ivm_vChangeBitValue, Array_ifm_vChangeBitValue);
	iMethodFor(Array, gGCDispose, Array_im_gDispose);
	ivMethodFor(Array, vBitValue, Array_ivm_vBitValue, Array_ifm_vBitValue);
	iMethodFor(Array, gRank, Array_im_gRank);
	iMethodFor(Array, gStringRepValue, Array_im_gStringRepValue);
	iMethodFor(Array, gCopy, Array_im_gCopy);
	iMethodFor(Array, gDeepDispose, Array_im_gDeepDispose);
	iMethodFor(Array, gIndex, Array_im_gIndex);
	iMethodFor(Array, gStringRep, Array_im_gStringRep);
	iMethodFor(Array, gDeepCopy, Array_im_gDeepCopy);

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return Array_c;
}



