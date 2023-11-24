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



#line 33 "BTreeNode.d"
#include <string.h> 

#define OBJECTS_PER_NODE 50 


#define MEMMOVE(a,b,c) memmove((void *)(a), (void *)(b), c) 
#define MEMSET(a,b,c) memset((void *)(a), b, c) 
#define MEMCPY(a,b,c) memcpy((void *)(a), (void *)(b), c) 

#define	CLASS	BTreeNode_c
#define	ivType	BTreeNode_iv_t

#include "generics.h"

object	BTreeNode_c;


#line 57 "BTreeNode.c"
typedef struct  _BTreeNode_iv_t  {
	int iUsed;
	int iType;
	object iKeys [ OBJECTS_PER_NODE ];
	object iObjects [ OBJECTS_PER_NODE + 1 ];
	object iBTree;
	object iPrevious;
}	BTreeNode_iv_t;


#line 68 "BTreeNode.c"
typedef struct  _BTreeNode_cv_t  {
	object cData;
}	BTreeNode_cv_t;

static	BTreeNode_cv_t	*BTreeNode_cv;



#line 57 "BTreeNode.d"
cmeth objrtn BTreeNode_cm_gNewNode(object self, object btree, int type)
{ 
	object obj = oSuper(BTreeNode_c, gNew, self)(self); 
	accessIVsOf(obj); 
	iv->iBTree = btree; 
	iv->iType = type; 
	if (!BTreeNode_cv->cData) 
		BTreeNode_cv->cData = gNew(Constant); 
	return obj; 
} 

imeth objrtn BTreeNode_im_gDispose(object self)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int i; 
	object n; 

	if (iv->iType == 1) { 
		for (i=0 ; i < iv->iUsed ; ++i) { 
			if (n = iv->iKeys[i]) 
				gDeepDispose(n); 
			if (n = iv->iObjects[i]) 
				gDispose(n); 
		} 
		if (n = iv->iObjects[iv->iUsed]) 
			gDispose(n); 
	} 
	return oSuper(BTreeNode_c, gDispose, self)(self); 
} 

imeth objrtn BTreeNode_im_gDeepDispose(object self)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int i; 
	object n; 

	for (i=0 ; i < iv->iUsed ; ++i) { 
		if (n = iv->iKeys[i]) 
			gDeepDispose(n); 
		if (n = iv->iObjects[i]) 
			gDeepDispose(n); 
	} 
	if (iv->iType == 1 && (n = iv->iObjects[iv->iUsed])) 
		gDeepDispose(n); 
	return oSuper(BTreeNode_c, gDispose, self)(self); 
} 

static int bsearch2(ivType *iv, int (*cfun)(void *, void *), object key, int *idx) 
{ 
	int low = 0, high = iv->iUsed-1, mid, cond; 

	while (low <= high) { 
		mid = (low + high) / 2; 
		cond = cfun(key, iv->iKeys[mid]); 
		if (cond < 0) 
			high = mid - 1; 
		else if (cond > 0) 
			low = mid + 1; 
		else 
			break; 
	} 
	if (low <= high) { 
		*idx = mid; 
		return 1; 
	} else { 
		*idx = low; 
		return 0; 
	} 
} 

PMETHOD objrtn find(object self, ifun cfun, object key, object *foundKey)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int found, idx; 

	found = bsearch2(iv, cfun, key, &idx); 
	if (iv->iType == 2) 
		if (found) { 
		if (foundKey) 
			*foundKey = iv->iKeys[idx]; 
		return iv->iObjects[idx]; 
	} else 
		return NULL; 
	return find(iv->iObjects[found+idx], cfun, key, foundKey); 
} 

PMETHOD objrtn findFirst(object self, ifun cfun, object *foundKey)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	if (iv->iType == 2) { 
		if (foundKey) 
			*foundKey = iv->iKeys[0]; 
		return iv->iObjects[0]; 
	} 
	return findFirst(iv->iObjects[0], cfun, foundKey); 
} 

PMETHOD objrtn findLast(object self, ifun cfun, object *foundKey)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	if (iv->iType == 2) { 
		if (foundKey) 
			*foundKey = iv->iKeys[iv->iUsed-1]; 
		return iv->iObjects[iv->iUsed-1]; 
	} 
	return findLast(iv->iObjects[iv->iUsed], cfun, foundKey); 
} 

PMETHOD objrtn findGE(object self, ifun cfun, object key, object *foundKey)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int found, idx; 
	object ret; 

	found = bsearch2(iv, cfun, key, &idx); 
	if (iv->iType == 2) 
		if (idx != iv->iUsed) { 
		if (foundKey) 
			*foundKey = iv->iKeys[idx]; 
		return iv->iObjects[idx]; 
	} else { 
		if (foundKey) 
			*foundKey = NULL; 
		return NULL; 
	} 
	for (idx=idx+found ; idx <= iv->iUsed ; idx++) 
		if (ret = findGE(iv->iObjects[idx], cfun, key, foundKey)) 
		return ret; 
	return NULL; 
} 

PMETHOD objrtn findGT(object self, ifun cfun, object key, object *foundKey)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int found, idx; 
	object ret; 

	found = bsearch2(iv, cfun, key, &idx); 
	if (found) 
		idx++; 
	if (iv->iType == 2) 
		if (idx != iv->iUsed) { 
		if (foundKey) 
			*foundKey = iv->iKeys[idx]; 
		return iv->iObjects[idx]; 
	} else { 
		if (foundKey) 
			*foundKey = NULL; 
		return NULL; 
	} 
	for ( ; idx <= iv->iUsed ; idx++) 
		if (ret = findGT(iv->iObjects[idx], cfun, key, foundKey)) 
		return ret; 
	return NULL; 
} 

PMETHOD objrtn findLE(object self, ifun cfun, object key, object *foundKey)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int found, idx; 
	object ret; 

	found = bsearch2(iv, cfun, key, &idx); 
	if (iv->iType == 2) 
		if (found) { 
		if (foundKey) 
			*foundKey = iv->iKeys[idx]; 
		return iv->iObjects[idx]; 
	} else if (idx) { 
		if (foundKey) 
			*foundKey = iv->iKeys[idx-1]; 
		return iv->iObjects[idx-1]; 
	} else { 
		if (foundKey) 
			*foundKey = NULL; 
		return NULL; 
	} 
	for (idx=idx+found ; idx >= 0 ; idx--) 
		if (ret = findLE(iv->iObjects[idx], cfun, key, foundKey)) 
		return ret; 
	return NULL; 
} 

PMETHOD objrtn findLT(object self, ifun cfun, object key, object *foundKey)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int idx; 
	object ret; 

	bsearch2(iv, cfun, key, &idx); 
	if (iv->iType == 2) 
		if (idx) { 
		if (foundKey) 
			*foundKey = iv->iKeys[idx-1]; 
		return iv->iObjects[idx-1]; 
	} else { 
		if (foundKey) 
			*foundKey = NULL; 
		return NULL; 
	} 
	for ( ; idx >= 0 ; idx--) 
		if (ret = findLT(iv->iObjects[idx], cfun, key, foundKey)) 
		return ret; 
	return NULL; 
} 

static void delete_intermediate_pointer(ivType *iv, object old_node) 
{ 
	int idx; 

	for (idx=0 ; iv->iObjects[idx] != old_node ; idx++); 
	if (!idx) { 
		gDeepDispose(iv->iKeys[0]); 
		MEMMOVE(iv->iKeys, iv->iKeys+1, (iv->iUsed-1)*sizeof(object)); 
		MEMMOVE(iv->iObjects, iv->iObjects+1, iv->iUsed*sizeof(object)); 
	} else { 
		gDeepDispose(iv->iKeys[idx-1]); 
		MEMMOVE(iv->iKeys+idx-1, iv->iKeys+idx, (iv->iUsed-idx)*sizeof(object)); 
		MEMMOVE(iv->iObjects+idx, iv->iObjects+idx+1, (iv->iUsed-idx)*sizeof(object)); 
	} 
	iv->iKeys[iv->iUsed-1] = iv->iObjects[iv->iUsed] = NULL; 
	iv->iUsed--; 
} 

static void collapse(ivType *liv, object lo, int deep, object save_pointer) 
{ 
	object self = liv->iPrevious; 
	ivType *iv = ivPtr(self); 

	if (liv->iType == 2) { 
		if (deep || liv->iType == 1) 
			gDeepDispose(lo); 
		else 
			gDispose(lo); 
		if (!iv->iPrevious) 
			if (iv->iUsed == 1) { 
			gSetTopNode(iv->iBTree, iv->iObjects[iv->iObjects[0] == lo]); 
			iv->iObjects[0] = iv->iObjects[1] = NULL; 
			gDeepDispose(self); 
		} else 
			delete_intermediate_pointer(iv, lo); 
		else 
			if (iv->iUsed == 1) { 
			object save = iv->iObjects[0] == lo ? iv->iObjects[1] : iv->iObjects[0]; 
			iv->iObjects[0] = iv->iObjects[1] = NULL; 
			collapse(iv, self, deep, save); 
		} else 
			delete_intermediate_pointer(iv, lo); 
	} else { 
		int idx; 

		for (idx=0 ; iv->iObjects[idx] != lo ; idx++); 
		iv->iObjects[idx] = save_pointer; 
		gDeepDispose(lo); 
	} 
} 

PMETHOD objrtn delete(object self, ifun cfun, object key, int deep, object prev)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int found, idx; 
	object res; 

	found = bsearch2(iv, cfun, key, &idx); 
	if (iv->iType == 2) { 
		if (!found) 
			return NULL; 
		if (iv->iUsed == 1 && prev) { 
			iv->iPrevious = prev; 
			collapse(iv, self, deep, NULL); 
		} else { 
			int n = iv->iUsed - idx - 1; 
			if (deep) { 
				gDeepDispose(iv->iKeys[idx]); 
				gDeepDispose(iv->iObjects[idx]); 
			} 
			MEMMOVE(iv->iKeys+idx, iv->iKeys+idx+1, n*sizeof(object)); 
			MEMMOVE(iv->iObjects+idx, iv->iObjects+idx+1, n*sizeof(object)); 
			iv->iUsed--; 
			iv->iKeys[iv->iUsed] = iv->iObjects[iv->iUsed] = NULL; 
		} 
		return self; 
	} 
	iv->iPrevious = prev; 
	res = delete(iv->iObjects[found+idx], cfun, key, deep, self); 
	iv->iPrevious = NULL; 
	return res; 
} 

static object split(object lo, ivType *left, ifun cfun) 
{ 
	object to, ro, ret; 
	ivType *right, *top; 
	int lhalf, rhalf; 

	ro = gNewNode(CLASS, left->iBTree, left->iType); 
	right = ivPtr(ro); 
	if (left->iType == 2) { 
		lhalf = left->iUsed / 2; 
		rhalf = left->iUsed - lhalf; 
		MEMCPY(right->iKeys, left->iKeys+lhalf, rhalf*sizeof(object)); 
		MEMSET(left->iKeys+lhalf, 0, rhalf*sizeof(object)); 
		left->iUsed = lhalf; 
		right->iUsed = rhalf; 
		MEMCPY(right->iObjects, left->iObjects+lhalf, rhalf*sizeof(object)); 
		MEMSET(left->iObjects+lhalf, 0, rhalf*sizeof(object)); 
	} else { 
		lhalf = left->iUsed / 2; 
		rhalf = left->iUsed - lhalf - 1; 
		MEMCPY(right->iKeys, left->iKeys+lhalf+1, rhalf*sizeof(object)); 
		MEMSET(left->iKeys+lhalf+1, 0, rhalf*sizeof(object)); 
		left->iUsed = lhalf; 
		right->iUsed = rhalf; 
		MEMCPY(right->iObjects, left->iObjects+lhalf+1, (rhalf+1)*sizeof(object)); 
		MEMSET(left->iObjects+lhalf+1, 0, (rhalf+1)*sizeof(object)); 
	} 

	if (!(ret=to=left->iPrevious)) { 
		ret = to = gNewNode(CLASS, left->iBTree, 1); 
		gSetTopNode(left->iBTree, to); 
		top = ivPtr(to); 
		if (left->iType == 1) { 
			top->iKeys[0] = left->iKeys[lhalf]; 
			left->iKeys[lhalf] = NULL; 
		} else 
			top->iKeys[0] = gDeepCopy(right->iKeys[0]); 
		top->iObjects[0] = lo; 
		top->iObjects[1] = ro; 
		top->iUsed = 1; 
	} else { 
		int found, idx, n; 

		top = ivPtr(to); 
		if (top->iUsed == OBJECTS_PER_NODE) { 
			ret = to = split(to, top, cfun); 
			top = ivPtr(to); 
			found = bsearch2(top, cfun, right->iKeys[0], &idx); 
			to = top->iObjects[found+idx]; 
			top = ivPtr(to); 
		} 
		found = bsearch2(top, cfun, right->iKeys[0], &idx); 
		if (found) 
			gError(Dynace, "BTreeNode error"); 
		n = top->iUsed - idx; 
		if (n) { 
			MEMMOVE(top->iKeys+idx+1, top->iKeys+idx, n*sizeof(object)); 
			MEMMOVE(top->iObjects+idx+2, top->iObjects+idx+1, n*sizeof(object)); 
		} 
		if (left->iType == 1) { 
			top->iKeys[idx] = left->iKeys[lhalf]; 
			left->iKeys[lhalf] = NULL; 
		} else 
			top->iKeys[idx] = gDeepCopy(right->iKeys[0]); 
		top->iObjects[idx+1] = ro; 
		top->iUsed++; 
	} 

	return ret; 
} 

#line 417 "BTreeNode.d"
#define DATA data ? data : BTreeNode_cv->cData 

PMETHOD objrtn add(object self, ifun cfun, object key, object data, int replace, int *replaced, object prev, object *old)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int found, idx; 
	object tmp, ret; 

	found = bsearch2(iv, cfun, key, &idx); 
	if (iv->iType == 1) { 
		iv->iPrevious = prev; 
		ret = add(iv->iObjects[found+idx], cfun, key, DATA, replace, replaced, self, old); 
		iv->iPrevious = NULL; 
		return ret; 
	} 

	if (found) 
		if (replace) { 
		*old = iv->iObjects[idx]; 
		iv->iObjects[idx] = DATA; 
		*replaced = 2; 
		return self; 
	} else { 
		*replaced = 0; 
		return self; 
	} 



	if (iv->iUsed == OBJECTS_PER_NODE) { 
		iv->iPrevious = prev; 
		tmp = split(self, iv, cfun); 
		iv->iPrevious = NULL; 
		return add(tmp, cfun, key, DATA, replace, replaced, NULL, old); 
	} 

	if (idx != iv->iUsed) { 
		int n = iv->iUsed - idx; 
		MEMMOVE(iv->iKeys+idx+1, iv->iKeys+idx, n*sizeof(object)); 
		MEMMOVE(iv->iObjects+idx+1, iv->iObjects+idx, n*sizeof(object)); 
	} 
	iv->iKeys[idx] = key; 
	iv->iObjects[idx] = DATA; 
	iv->iUsed++; 
	*replaced = 1; 
	return self; 
} 

imeth objrtn BTreeNode_im_gPrint(object self, object stream)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int i, n; 

	gPrintValue(self, stream); 
	gPuts(stream, "\n------------------------------------------------------------\n"); 
	if (iv->iType == 1) { 
		n = iv->iUsed + 1; 
		for (i=0 ; i < n ; i++) 
			gPrint(iv->iObjects[i], stream); 
	} 
	return self; 
} 

imeth objrtn BTreeNode_im_gPrintValue(object self, object stream)
{ BTreeNode_iv_t *iv = GetIVs(BTreeNode, self);
	int i, n; 
	object t, k; 

	vPrintf(stream, "BTree %8.8lx, %s node %8.8lx, %d used\n\n", iv->iBTree, iv->iType == 1 ? "Intermediate" : "Leaf", self, iv->iUsed); 
	if (!iv->iBTree) 
		vPrintf(stream, "ERROR: iBTRee not set\n"); 
	if (iv->iPrevious) 
		vPrintf(stream, "ERROR: iPrevious set\n"); 
	for (i=iv->iUsed ; i < OBJECTS_PER_NODE ; i++) 
		if (iv->iKeys[i]) 
		vPrintf(stream, "\nERROR:  iKeys[%d] has an unexpected value.\n", i); 
	for (i=iv->iUsed+(iv->iType==1) ; i <= OBJECTS_PER_NODE ; i++) 
		if (iv->iObjects[i]) 
		vPrintf(stream, "\nERROR:  iObjects[%d] has an unexpected value.\n", i); 
	if (iv->iType == 1) { 
		n = iv->iUsed + 1; 
		for (i=0 ; i < n ; i++) { 
			vPrintf(stream, "\t%8.8lx  \n", iv->iObjects[i]); 
			if (i < iv->iUsed) { 
				k = gStringRepValue(iv->iKeys[i]); 
				vPrintf(stream, "\t\t%s  \n", gStringValue(k)); 
				gDispose(k); 
			} 
		} 
	} else 
		for (i=0 ; i < iv->iUsed ; i++) { 
		t = gStringRepValue(iv->iObjects[i]); 
		k = gStringRepValue(iv->iKeys[i]); 
		vPrintf(stream, "\t%s - %s \n", gStringValue(k), gStringValue(t)); 
		gDispose(k); 
		gDispose(t); 
	} 
	gPuts(stream, "\n"); 
	return self; 
} 


#line 529 "BTreeNode.c"

objrtn	BTreeNode_initialize(void)
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

	if (BTreeNode_c) {
		LEAVECRITICALSECTION(cs);
		return BTreeNode_c;
	}
	INHIBIT_THREADER;
	BTreeNode_c = gNewClass(Class, "BTreeNode", sizeof(BTreeNode_iv_t), sizeof(BTreeNode_cv_t), END);
	cMethodFor(BTreeNode, gNewNode, BTreeNode_cm_gNewNode);
	iMethodFor(BTreeNode, gFindBTNGE, findGE);
	iMethodFor(BTreeNode, gFindBTNLT, findLT);
	iMethodFor(BTreeNode, gFindBTNFirst, findFirst);
	iMethodFor(BTreeNode, gFindBTNLE, findLE);
	iMethodFor(BTreeNode, gPrint, BTreeNode_im_gPrint);
	iMethodFor(BTreeNode, gAddBTreeNode, add);
	iMethodFor(BTreeNode, gFindBTNEQ, find);
	iMethodFor(BTreeNode, gFindBTNLast, findLast);
	iMethodFor(BTreeNode, gDispose, BTreeNode_im_gDispose);
	iMethodFor(BTreeNode, gFindBTNGT, findGT);
	iMethodFor(BTreeNode, gDeleteBTNode, delete);
	iMethodFor(BTreeNode, gDeepDispose, BTreeNode_im_gDeepDispose);
	iMethodFor(BTreeNode, gPrintValue, BTreeNode_im_gPrintValue);

	BTreeNode_cv = GetCVs(BTreeNode);

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return BTreeNode_c;
}



