//
//  SqStack.c
//  CXYDataStuctures
//
//  Created by chen on 16/7/23.
//  Copyright © 2016年 ___CHEN___. All rights reserved.
//
/**
 *  顺序栈
 */
#include "SqStack.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static const int MAX_SIZE = 5;

typedef int ElemType;

typedef struct {
    ElemType *elem;
    int top;
}SqStack;

bool SqStackInit(SqStack *s) {
    s->elem = (ElemType*)malloc(MAX_SIZE*sizeof(ElemType));
    if(!s->elem) return false;
    s->top = -1;
    return true;
}

void SqStackDestroy(SqStack *s) {
    if (!s) return;
    free(s->elem);
    s->elem = NULL;
    s->top = -1;
}

void SqStackClear(SqStack *s) {
    if (!s) return;
    s->top = -1;
}

bool SqStackIsEmpty(SqStack *s) {
    if (!s) return true;
    return s->top == -1;
}

bool SqStackIsFull(SqStack *s) {
    if (!s) return true;
    return s->top >= MAX_SIZE-1;
}

int SqStackLength(SqStack *s) {
    if (!s) return 0;
    return s->top+1;
}

ElemType* SqStackElem(SqStack *s, int loc) {
    if (SqStackIsEmpty(s)) return NULL;
    if (loc > s->top || loc < 0) return NULL;
    
    return s->elem+loc;
}

bool SqStackPush(SqStack *s, ElemType e) {
    if (!s || SqStackIsFull(s)) return false;
    s->top++;
    ElemType *te = SqStackElem(s,s->top);
    *te = e;
    return true;
}

ElemType* SqStackPop(SqStack *s) {
    if (SqStackIsEmpty(s)) return NULL;
    ElemType *e = s->elem+s->top;
    s->top--;
    return e;
}

void SqStackTraverse(SqStack *s, void (*Myfunc)(ElemType*)) {
    if (SqStackIsEmpty(s)) return;
    
    printf("遍历开始:\n");
    int top = s->top;
    do {
        Myfunc(s->elem+top);
    } while (top--);
}


void SqStackPrint(ElemType *e) {
    if (e) {
        printf("%d ",*e);
    }
}

void SqStackTest() {
    SqStack stack, *s;
    s = &stack;
    
    SqStackInit(s);
    for (int i=0; i<MAX_SIZE; i++) {
        SqStackPush(s, i+1);
    }
  
    SqStackPop(s);
    
    ElemType *e = SqStackElem(s, 1);
    if (e) {
        printf("e = %d\n",*e);
    }
    SqStackTraverse(s, SqStackPrint);
}



