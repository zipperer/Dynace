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



#line 32 "Thread.d"
typedef struct _priority_queue *PQ; 

#define	CLASS	Thread_c
#define	ivType	Thread_iv_t

#include "generics.h"

object	Thread_c;


#line 50 "Thread.c"
typedef struct  _Thread_iv_t  {
	object iObj;
	char * iName;
	int ( * iFun ) ( void * );
	jmp_buf iRtn;
	char * iStack_buf;
	char * iStack_location;
	INT_PTR iStack_buf_size;
	INT_PTR iStack_size;
	int iState;
	int iAutoDispose;
	int iPriority;
	void * iArg;
	int iPrev_state;
	int iHold_count;
	int iRtnVal;
	int iWr;
	object iWait;
	struct _Thread_iv_t * iTwait;
	struct _Thread_iv_t * iNext , * iPrev;
	object iSema;
}	Thread_iv_t;


#line 75 "Thread.c"
typedef struct  _Thread_cv_t  {
	char * cTs_stkpos;
	PQ cMpq;
	PQ cCpq;
	ivType * cCt;
	ivType * cTnr;
	ivType * cGkt;
	PQ cFpql;
	object cThreads;
	unsigned long cThrno;
}	Thread_cv_t;

static	Thread_cv_t	*Thread_cv;


#line 80 "Thread.d"
struct _priority_queue { 
	int priority; 
	ivType *thread; 
	PQ next; 
}; 


#include <string.h> 

#if !defined(unix) && !defined(__APPLE__) && !defined(PLAN9) && !defined(__minix) 
#include <conio.h> 
#ifdef _MSC_VER 
#if _MSC_VER >= 1400 
#define kbhit _kbhit 
#define getch _getch 
#endif 


#line 96 "Thread.d"
#endif 


#line 97 "Thread.d"
#else 


#line 98 "Thread.d"
int getch(void); 
int kbhit(void); 
#endif 


#line 104 "Thread.d"
jmp_buf _t_start; 



#define STACKINC 100 



#define NTICKS 1 

static objrtn Release(object self, int yld); 

#ifdef FUNCTIONS 

#define NEXT_THREAD next_thread() 

static void next_thread(void); 
static void add_tnr(ivType *t); 
static void del_tnr(ivType *t); 

#else 


#line 136 "Thread.d"
#define NEXT_THREAD if (Thread_cv->cCpq) Thread_cv->cCpq->thread = Thread_cv->cCpq->thread->iNext; if (Thread_cv->cGkt && kbhit()) { Release(Thread_cv->cGkt->iObj, 0); Thread_cv->cGkt = NULL; } if (Thread_cv->cCpq = Thread_cv->cMpq) Thread_cv->cCt = Thread_cv->cCpq->thread; else exit(0) 

#line 142 "Thread.d"
#define add_tnr(t) if (t->iNext = Thread_cv->cTnr) Thread_cv->cTnr->iPrev = t; t->iPrev = NULL; Thread_cv->cTnr = t 

#line 150 "Thread.d"
#define del_tnr(t) if (t->iPrev) t->iPrev->iNext = t->iNext; else Thread_cv->cTnr = t->iNext; if (t->iNext) t->iNext->iPrev = t->iPrev 

#endif 


#line 154 "Thread.d"
extern void _start_timer(void); 


static void start_thread(ivType *s); 
static void stop_thread(ivType *t); 
static void resolve_waits(ivType *t); 
static void delete_wait(ivType *t); 
static PQ new_pq(void); 
static void free_pq(PQ t); 
static void delete_sema_waits(ivType *t); 
static void _dynace_yield(void); 
static char *strsave(char *); 

#ifdef FUNCTIONS 

static void next_thread(void) 
{ 
	if (Thread_cv->cCpq) 
		Thread_cv->cCpq->thread = Thread_cv->cCpq->thread->iNext; 
	if (Thread_cv->cGkt && kbhit()) { 
		Release(Thread_cv->cGkt->iObj, 0); 
		Thread_cv->cGkt = NULL; 
	} 
	if (Thread_cv->cCpq = Thread_cv->cMpq) 
		Thread_cv->cCt = Thread_cv->cCpq->thread; 
	else 
		exit(0); 
} 

#endif 


#line 188 "Thread.d"
static void start_thread(ivType *s) 
{ 
	PQ tpq, ppq, npq; 

	for (ppq=NULL, tpq=Thread_cv->cMpq ; tpq && s->iPriority < tpq->priority ; ppq=tpq, tpq=tpq->next); 
	if (!tpq || s->iPriority != tpq->priority) { 
		npq = new_pq(); 
		s->iNext = s->iPrev = s; 
		npq->priority = s->iPriority; 
		npq->thread = s; 
		npq->next = tpq; 
		if (ppq) 
			ppq->next = npq; 
		else 
			Thread_cv->cMpq = npq; 
	} else 
		if (tpq == Thread_cv->cCpq) { 
		s->iNext = tpq->thread->iNext; 
		s->iPrev = tpq->thread; 
		tpq->thread->iNext = s; 
		s->iNext->iPrev = s; 
	} else { 
		s->iNext = tpq->thread; 
		s->iPrev = tpq->thread->iPrev; 
		tpq->thread->iPrev = s; 
		s->iPrev->iNext = s; 
		tpq->thread = s; 
	} 
} 



static void stop_thread(ivType *t) 
{ 
	PQ pq, ppq; 

	for (ppq=NULL, pq=Thread_cv->cMpq ; pq && pq->priority != t->iPriority ; 
	ppq=pq, pq=pq->next); 
	if (!pq) 
		goto error; 
	if (t->iNext != t) { 
		t->iPrev->iNext = t->iNext; 
		t->iNext->iPrev = t->iPrev; 
		if (pq->thread == t) { 
			pq->thread = t->iNext; 
			if (pq == Thread_cv->cCpq) 
				Thread_cv->cCpq = NULL; 
		} 
	} else { 
		if (pq->thread != t) 
			goto error; 
		if (pq == Thread_cv->cCpq) 
			Thread_cv->cCpq = NULL; 
		if (ppq) 
			ppq->next = pq->next; 
		else 
			Thread_cv->cMpq = pq->next; 
		free_pq(pq); 
	} 
	return; 
	error: 
	fprintf(stderr, "Bad priority queue\n"); 
	exit(1); 
} 

#ifdef FUNCTIONS 



static void add_tnr(ivType *t) 
{ 
	if (t->iNext = Thread_cv->cTnr) 
		Thread_cv->cTnr->iPrev = t; 
	t->iPrev = NULL; 
	Thread_cv->cTnr = t; 
} 



static void del_tnr(ivType *t) 
{ 
	if (t->iPrev) 
		t->iPrev->iNext = t->iNext; 
	else 
		Thread_cv->cTnr = t->iNext; 
	if (t->iNext) 
		t->iNext->iPrev = t->iPrev; 
} 

#endif 


#line 279 "Thread.d"
PMETHOD objrtn Kill(object self, int rtn)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	if (iv->iState == DONE_THREAD) 
		return self; 
	INHIBIT_THREADER; 
	iv->iRtnVal = rtn; 
	if (iv->iStack_buf) { 
		free(iv->iStack_buf); 
		iv->iStack_buf = NULL; 
		iv->iStack_buf_size = iv->iStack_size = 0; 
	} 
	if (iv->iState == NEW_THREAD || iv->iState == RUNNING_THREAD) { 
		stop_thread(iv); 
		add_tnr(iv); 
	} else if (iv->iState == WAITING_FOR_THREAD) 
		delete_wait(iv); 
	iv->iState = DONE_THREAD; 
	if (iv->iSema) 
		delete_sema_waits(iv); 
	if (iv->iWait) 
		resolve_waits(iv); 
	if (iv == Thread_cv->cGkt) 
		Thread_cv->cGkt = NULL; 
#if 0 
		if (iKmrp) { 
		static gRemoveRegisteredMemory_t rrm = NULL; 

		if (!rrm) 
			rrm = cmcPointer(Dynace, gRemoveRegisteredMemory); 
		(rrm)(Dynace, iKmrp); 
		iKmrp = NULL; 
	} 
#endif 

#line 312 "Thread.d"
		ENABLE_THREADER; 
	if (!Thread_cv->cCpq || Thread_cv->cCt == iv) { 
		Thread_cv->cCt = NULL; 
		_dynace_yield(); 
	} 
	return self; 
} 

PMETHOD objrtn Dispose(object self)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	INHIBIT_THREADER; 
	if (iv->iStack_buf) 
		free(iv->iStack_buf); 
	if (iv->iState == NEW_THREAD || iv->iState == RUNNING_THREAD) 
		stop_thread(iv); 
	else { 
		if (iv->iState == WAITING_FOR_THREAD) 
			delete_wait(iv); 
		del_tnr(iv); 
	} 

	iv->iState = DONE_THREAD; 
	if (iv->iSema) 
		delete_sema_waits(iv); 
	if (iv->iWait) { 
		static gDispose_t dispose = NULL; 

		if (!dispose) 
			dispose = imcPointer(LinkObject, gDispose); 
		resolve_waits(iv); 
		(*dispose)(iv->iWait); 
	} 
	if (iv == Thread_cv->cGkt) 
		Thread_cv->cGkt = NULL; 
#if 0 
		if (iKmrp) { 
		static gRemoveRegisteredMemory_t rrm = NULL; 

		if (!rrm) 
			rrm = cmcPointer(Dynace, gRemoveRegisteredMemory); 
		(*rrm)(Dynace, iKmrp); 
	} 
#endif 

#line 355 "Thread.d"
		gRemoveStr(Thread_cv->cThreads, iv->iName); 
	free(iv->iName); 
	oSuper(Thread_c, gDispose, self)(self); 
	ENABLE_THREADER; 
	if (!Thread_cv->cCpq || Thread_cv->cCt == iv) { 
		Thread_cv->cCt = NULL; 
		_dynace_yield(); 
	} 
	return NULL; 
} 

static char *strsave(char *s) 
{ 
	char *p = Tnalloc(char, strlen(s)+1); 
	strcpy(p, s); 
	return p; 
} 

cmeth objrtn Thread_cm_gNew(object self)
{ 
	return gShouldNotImplement(self, "gNew"); 
} 

cmeth objrtn Thread_cm_gNewThread(object self, char *name, ifun fun, int priority, void *arg, int run, int autoDispose)
{ 
	char buf[30]; 
	object obj = oSuper(Thread_c, gNew, self)(self); 
	ivType *iv = ivPtr(obj); 
	static gFindStr_t find = NULL; 
	static gAddStr_t add = NULL; 

	INHIBIT_THREADER; 
	iv->iObj = obj; 
	if (name) 
		iv->iName = strsave(name); 
	else { 
		sprintf(buf, "unnamed-%ld", ++Thread_cv->cThrno); 
		iv->iName = strsave(buf); 
	} 
	if (!find) 
		find = imcPointer(StringDictionary, gFindStr); 
	if ((*find)(Thread_cv->cThreads, iv->iName)) { 
		free(iv->iName); 
		oSuper(Thread_c, gDispose, self)(self); 
		ENABLE_THREADER; 
		return NULL; 
	} 

	iv->iFun = (int (*)(void *)) fun; 
	iv->iPriority = priority; 
	iv->iArg = arg; 
	iv->iAutoDispose = autoDispose; 

	if (!add) 
		add = imcPointer(StringDictionary, gAddStr); 
	(*add)(Thread_cv->cThreads, iv->iName, obj); 
	ENABLE_THREADER; 

	if (run) { 
		iv->iState = NEW_THREAD; 
		start_thread(iv); 
		if (Thread_cv->cCt && Thread_cv->cCt->iPriority < priority) 
			_dynace_yield(); 
	} else { 
		iv->iPrev_state = NEW_THREAD; 
		iv->iState = HOLD_THREAD; 
		iv->iHold_count = 1; 
		add_tnr(iv); 
	} 

	return obj; 
} 

void _start_threader(char *stkpos) 
{ 
	object t; 

	Thread; 
	if (Thread_cv->cMpq) 
		return; 

	INHIBIT_THREADER; 
	t = gNewThread(CLASS, "main", NULL, DEFAULT_PRIORITY, NULL, 1, 0); 
	ENABLE_THREADER; 
	Thread_cv->cCt = ivPtr(t); 

	Thread_cv->cCt->iState = RUNNING_THREAD; 
	Thread_cv->cCpq = Thread_cv->cMpq; 

	Thread_cv->cTs_stkpos = stkpos; 

	_start_timer(); 
} 

void _start_thread(void) 
{ 
	Thread_cv->cCt->iState = RUNNING_THREAD; 
	_tick_count = NTICKS; 
	Thread_cv->cCt->iRtnVal = (*Thread_cv->cCt->iFun)(Thread_cv->cCt->iArg); 
	Kill(Thread_cv->cCt->iObj, Thread_cv->cCt->iRtnVal); 
	if (Thread_cv->cCt->iAutoDispose) 
		Dispose(Thread_cv->cCt->iObj); 
} 

PMETHOD objrtn Hold(object self)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	if (iv->iState == DONE_THREAD) 
		return self; 
	if (iv->iState == HOLD_THREAD) { 
		iv->iHold_count++; 
		return self; 
	} 
	if (iv->iState == NEW_THREAD || iv->iState == RUNNING_THREAD) { 
		stop_thread(iv); 
		add_tnr(iv); 
	} 
	iv->iPrev_state = iv->iState; 
	iv->iState = HOLD_THREAD; 
	iv->iHold_count = 1; 
	if (iv == Thread_cv->cCt) 
		_dynace_yield(); 
	return self; 
} 

PMETHOD objrtn Release(object self, int yld)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	if (iv->iState == HOLD_THREAD && !--iv->iHold_count) { 
		iv->iState = iv->iPrev_state; 
		if (iv->iState == NEW_THREAD || iv->iState == RUNNING_THREAD) { 
			del_tnr(iv); 
			start_thread(iv); 
			if (yld && iv->iPriority > Thread_cv->cCt->iPriority) 
				_dynace_yield(); 
		} 
	} 
	return self; 
} 

static void _dynace_yield(void) 
{ 
	ivType *t; 



	if (Thread_cv->cCt && Thread_cv->cCt->iState != DONE_THREAD) { 
#ifdef sparc 

		Thread_cv->cCt->iStack_location = (char *) &t - 0x80; 
#else 


#line 504 "Thread.d"
		Thread_cv->cCt->iStack_location = (char *) &t; 
#endif 


#line 506 "Thread.d"
		if ((int)(Thread_cv->cCt->iStack_size = Thread_cv->cTs_stkpos - Thread_cv->cCt->iStack_location) < 0) 
			Thread_cv->cCt->iStack_size = 0; 
		if (Thread_cv->cCt->iStack_size > Thread_cv->cCt->iStack_buf_size) { 
			Thread_cv->cCt->iStack_buf_size = ((Thread_cv->cCt->iStack_size / STACKINC) + 1) * STACKINC; 
			if (Thread_cv->cCt->iStack_buf) 
				Thread_cv->cCt->iStack_buf = Tnrealloc(char, Thread_cv->cCt->iStack_buf_size, Thread_cv->cCt->iStack_buf); 
			else 
				Thread_cv->cCt->iStack_buf = Tnalloc(char, Thread_cv->cCt->iStack_buf_size); 
#if 0 
			{ 
				static gChangeRegisteredMemory_t crm=NULL; 
				static gRegisterMemory_t rm; 

				if (!crm) { 
					INHIBIT_THREADER; 
					crm = cmcPointer(Dynace, gChangeRegisteredMemory); 
					rm = cmcPointer(Dynace, gRegisterMemory); 
					ENABLE_THREADER; 
				} 
				if (Thread_cv->cCt->iKmrp) 
					(*crm)(Dynace, Thread_cv->cCt->iKmrp, Thread_cv->cCt->iStack_buf, (long) Thread_cv->cCt->iStack_buf_size); 
				else 
					Thread_cv->cCt->iKmrp = (void *)(*rm)(Dynace, Thread_cv->cCt->iStack_buf, (long) Thread_cv->cCt->iStack_buf_size); 
			} 
#endif 


#line 531 "Thread.d"
		} 
		if (Thread_cv->cCt->iStack_size) { 
#ifdef sparc 
			asm("t 3"); 
#endif 


#line 536 "Thread.d"
			memcpy(Thread_cv->cCt->iStack_buf, Thread_cv->cCt->iStack_location, Thread_cv->cCt->iStack_size); 
		} 



		if (setjmp(Thread_cv->cCt->iRtn)) { 



			if (Thread_cv->cCt->iStack_size) 
				memcpy(Thread_cv->cCt->iStack_location, Thread_cv->cCt->iStack_buf, Thread_cv->cCt->iStack_size); 
			_tick_count = NTICKS; 
			return; 
		} 
	} 



	NEXT_THREAD; 

	if (Thread_cv->cCt->iState == NEW_THREAD) 
		longjmp(_t_start, 1); 
	else { 
#ifdef sparc 
		if (Thread_cv->cCt->iStack_size){ 
			asm("t 3"); 
			memcpy(Thread_cv->cCt->iStack_location, Thread_cv->cCt->iStack_buf, Thread_cv->cCt->iStack_size); 
		} 
#endif 


#line 565 "Thread.d"
		longjmp(Thread_cv->cCt->iRtn, 1); 
	} 
} 

cmeth objrtn Thread_cm_gFindStr(object self, char *name)
{ 
	USE(self); 
	return name ? gFindValueStr(Thread_cv->cThreads, name) : (Thread_cv->cCt ? Thread_cv->cCt->iObj : (object) NULL); 
#if 0 
	ivType *t, *s; 
	PQ pq; 

	if (!name) 
		return Thread_cv->cCt ? Thread_cv->cCt->iObj : NULL; 
	for (pq=Thread_cv->cMpq ; pq ; pq=pq->next) { 
		s = t = pq->thread; 
		do { 
			if (t->iName && !strcmp(t->iName, name)) 
				return t->iObj; 
			t = t->iNext; 
		} while (t != s); 
	} 
	for (t=Thread_cv->cTnr ; t ; t=t->iNext) 
		if (t->iName && !strcmp(t->iName, name)) 
		return t->iObj; 
	return NULL; 
#endif 


#line 592 "Thread.d"
} 

imeth int Thread_im_gIntValue(object self)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	return iv->iRtnVal; 
} 

imeth int Thread_im_gState(object self)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	return iv->iState; 
} 

imeth char * Thread_im_gName(object self)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	return iv->iName; 
} 

imeth int Thread_im_gPriority(object self)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	return iv->iPriority; 
} 

imeth objrtn Thread_im_gChangePriority(object self, int p)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	int f, oldp; 

	oldp = iv->iPriority; 
	if (f = iv->iState == NEW_THREAD || iv->iState == RUNNING_THREAD) 
		stop_thread(iv); 
	iv->iPriority = p; 
	if (f) 
		start_thread(iv); 
	if (Thread_cv->cCt == iv && p < oldp && Thread_cv->cMpq->thread->iPriority > p || 
		Thread_cv->cCt != iv && f && p > Thread_cv->cCt->iPriority) 
		_dynace_yield(); 
	return self; 
} 

imeth int Thread_im_gWaitFor(object self)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	if (iv == Thread_cv->cCt) 
		return 0; 
	if (iv->iState != DONE_THREAD) { 
		stop_thread(Thread_cv->cCt); 
		add_tnr(Thread_cv->cCt); 

		INHIBIT_THREADER; 
		if (!iv->iWait) 
			iv->iWait = gNew(LinkObject); 
		gAddFirst(iv->iWait, Thread_cv->cCt->iObj); 
		ENABLE_THREADER; 

		Thread_cv->cCt->iTwait = iv; 
		Thread_cv->cCt->iState = WAITING_FOR_THREAD; 
		_dynace_yield(); 
		return Thread_cv->cCt->iWr; 
	} else 
		return iv->iRtnVal; 
} 



static void resolve_waits(ivType *t) 
{ 
	object thread; 
	static gFirst_t first=NULL; 
	static gDisposeFirst_t disposeFirst; 

	if (!t->iWait) 
		return; 
	INHIBIT_THREADER; 
	if (!first) { 
		first = imcPointer(LinkObject, gFirst); 
		disposeFirst = imcPointer(LinkObject, gDisposeFirst); 
	} 
	while (thread = (*first)(t->iWait)) { 
		ivType *tt; 

		tt = ivPtr(thread); 
		tt->iState = RUNNING_THREAD; 
		del_tnr(tt); 
		start_thread(tt); 
		tt->iWr = t->iRtnVal; 
		t->iTwait = NULL; 
		(*disposeFirst)(t->iWait); 
	} 
	ENABLE_THREADER; 
} 




static void delete_wait(ivType *t) 
{ 
	object linkSequence, linkValue, thread; 
	static gDispose_t disposeNode, dispose; 
	static gValue_t value; 
	static gNext_t next; 
	static gSequenceLinks_t sequenceLinks = NULL; 

	if (!t->iTwait->iWait) 
		return; 
	INHIBIT_THREADER; 
	if (!sequenceLinks) { 
		sequenceLinks = imcPointer(LinkObject, gSequenceLinks); 
		next = imcPointer(LinkSequence, gNext); 
		value = imcPointer(LinkValue, gValue); 
		disposeNode = imcPointer(LinkValue, gDispose); 
		dispose = imcPointer(LinkSequence, gDispose); 
	} 
	linkSequence = (*sequenceLinks)(t->iTwait->iWait); 
	while (linkValue = (*next)(linkSequence)) { 
		thread = (*value)(linkValue); 
		if (thread == t->iObj) { 
			(*disposeNode)(linkValue); 
			break; 
		} 
	} 
	if (linkValue) 
		(*dispose)(linkSequence); 
	ENABLE_THREADER; 
} 

static PQ new_pq(void) 
{ 
	PQ t; 

	if (Thread_cv->cFpql) { 
		t = Thread_cv->cFpql; 
		Thread_cv->cFpql = t->next; 
		memset(t, 0, sizeof(*t)); 
	} else 
		t = Tcalloc(struct _priority_queue); 
	return(t); 
} 

static void free_pq(PQ t) 
{ 
	t->next = Thread_cv->cFpql; 
	Thread_cv->cFpql = t; 
} 

static void delete_sema_waits(ivType *t) 
{ 
	static gRemoveWaits_t removeWaits = NULL; 

	INHIBIT_THREADER; 
	if (!removeWaits) 
		removeWaits = imiPointer(t->iSema, gRemoveWaits); 
	(*removeWaits)(t->iSema, t->iObj); 
	t->iSema = NULL; 
	ENABLE_THREADER; 
} 

cmeth int Thread_cm_gBlockingGetkey(object self)
{ 
	USE(self); 
	if (Thread_cv->cGkt) 
		return -1; 
	if (!kbhit()) { 
		Thread_cv->cGkt = Thread_cv->cCt; 
		Hold(Thread_cv->cCt->iObj); 
	} 
	return getch(); 
} 



imeth objrtn Thread_im_gReleaseSemaphore(object self)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	if (iv->iState == WAITING_FOR_SEMAPHORE) { 
		iv->iState = RUNNING_THREAD; 
		del_tnr(iv); 
		start_thread(iv); 
	} else if (iv->iState == HOLD_THREAD && iv->iPrev_state == WAITING_FOR_SEMAPHORE) 
		iv->iPrev_state = RUNNING_THREAD; 
	iv->iSema = NULL; 
	return self; 
} 



imeth objrtn Thread_im_gWaitSemaphore(object self, object sema)
{ Thread_iv_t *iv = GetIVs(Thread, self);
	stop_thread(iv); 
	add_tnr(iv); 
	iv->iState = WAITING_FOR_SEMAPHORE; 
	iv->iSema = sema; 
	return self; 
} 

static objrtn MarkThreadStacks(object self) 
{ 
	ivType *t, *s; 
	PQ pq; 
	static gMarkRange_t markRange = NULL; 

	if (!markRange) 
		markRange = cmcPointer(Dynace, gMarkRange); 

	for (pq=Thread_cv->cMpq ; pq ; pq=pq->next) { 
		s = t = pq->thread; 
		do { 
			if (t->iStack_buf && t->iStack_size) 
				(*markRange)(Dynace, (char _HUGE_ **)t->iStack_buf, (char _HUGE_ **)(t->iStack_buf + t->iStack_size)); 
			t = t->iNext; 
		} while (t != s); 
	} 
	for (t=Thread_cv->cTnr ; t ; t=t->iNext) 
		if (t->iStack_buf && t->iStack_size) 
		(*markRange)(Dynace, (char _HUGE_ **) t->iStack_buf, (char _HUGE_ **)(t->iStack_buf + t->iStack_size)); 
	return self; 
} 

#if defined(unix) || defined(__APPLE__) || defined(PLAN9) || defined(__minix) 



int kbhit(void) 
{ 
	return 0; 
} 

int getch(void) 
{ 
	return getchar(); 
} 

#endif 


#line 822 "Thread.d"
imeth objrtn Thread_im_gCopy(object self)
{ 
	return gShouldNotImplement(self, "Copy/DeepCopy"); 
} 

static void init_class(void) 
{ 



	__dynace_yield = _dynace_yield; 

	Thread_cv->cThreads = gNewWithInt(StringDictionary, 41); 

	gMarkingMethod(CLASS, (ofun) MarkThreadStacks); 
} 

#line 871 "Thread.c"

objrtn	Thread_initialize(void)
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

	if (Thread_c) {
		LEAVECRITICALSECTION(cs);
		return Thread_c;
	}
	INHIBIT_THREADER;
	Thread_c = gNewClass(Class, "Thread", sizeof(Thread_iv_t), sizeof(Thread_cv_t), END);
	cMethodFor(Thread, gNewThread, Thread_cm_gNewThread);
	cMethodFor(Thread, gFindStr, Thread_cm_gFindStr);
	cMethodFor(Thread, gBlockingGetkey, Thread_cm_gBlockingGetkey);
	cMethodFor(Thread, gNew, Thread_cm_gNew);
	iMethodFor(Thread, gChangePriority, Thread_im_gChangePriority);
	iMethodFor(Thread, gIntValue, Thread_im_gIntValue);
	iMethodFor(Thread, gState, Thread_im_gState);
	iMethodFor(Thread, gWaitSemaphore, Thread_im_gWaitSemaphore);
	iMethodFor(Thread, gPriority, Thread_im_gPriority);
	iMethodFor(Thread, gHold, Hold);
	iMethodFor(Thread, gRelease, Release);
	iMethodFor(Thread, gDispose, Dispose);
	iMethodFor(Thread, gName, Thread_im_gName);
	iMethodFor(Thread, gKill, Kill);
	iMethodFor(Thread, gReleaseSemaphore, Thread_im_gReleaseSemaphore);
	iMethodFor(Thread, gCopy, Thread_im_gCopy);
	iMethodFor(Thread, gDeepDispose, Dispose);
	iMethodFor(Thread, gDeepCopy, Thread_im_gCopy);
	iMethodFor(Thread, gWaitFor, Thread_im_gWaitFor);

	Thread_cv = GetCVs(Thread);

	init_class();

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return Thread_c;
}



