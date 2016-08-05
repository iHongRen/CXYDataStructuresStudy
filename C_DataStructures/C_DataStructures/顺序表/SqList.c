//
//  main.c
//  SqList
//
//  Created by chen on 16/7/6.
//  Copyright © 2016年 ___CHEN___. All rights reserved.
//

/*
	顺序表
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SqList.h"

static const int INIT_SIZE = 5;  //初始分配容量

typedef int ElemType;
typedef struct {
    ElemType *elem;   //元素指针(存储空间首地址)
    int length;       //当前长度
    int listsize;     //当前分配的存储容量
} SqList;


//分配并初始化
void SqListInit(SqList *L) {
    if (!L) return;
    L->elem = (ElemType*)malloc(INIT_SIZE*sizeof(ElemType));
    if(!L->elem) exit(-1);
    L->length = 0;
    L->listsize = INIT_SIZE;
    printf("初始化完成\n");
}

//销毁顺序表
void SqListDestroy(SqList *L) {
    if (!L) return;
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    printf("销毁了顺序表\n");
}

/**
 *  插入元素到i位置
 *
 *  @param L 顺序表指针
 *  @param e 要插入的元素
 *  @param i 插入位置
 *
 *  @return 返回true,表示插入成功
 */
bool SqListInsert(SqList *L, ElemType e, int i) {
    if (!L || i<1 || i>L->length+1) return false;
    ElemType *newbase,*q,*p;
    if (L->length>=L->listsize) {
        newbase = realloc(L->elem, (L->listsize+1)*sizeof(ElemType));
        if (!newbase) return false;
        L->elem = newbase;
        ++L->listsize;
    }
    q=L->elem+i-1;
    for (p=L->elem+L->length-1; p>=q; p--) {
        *(p+1) = *p;
    }
    *q = e;
    ++L->length;
    return true;
}

/**
 *  删除位置i的元素
 *
 *  @param L 顺序表指针
 *  @param i 元素位置
 *
 *  @return 被删除的元素指针
 */
ElemType* SqListDelete(SqList *L, int i) {
    if (!L || i<1 || i>L->length+1) return NULL;
    ElemType a,*p,*q;
    q = &a;
    *q = *(L->elem+i-1);
    for (p=L->elem+i-1; p<L->elem+L->length-1; p++) {
        *p = *(p+1);
    }
    --L->length;
    printf("删除的元素是%d\n",*q);
    return q;
}


/**
 *  根据位置i，查找元素
 *
 *  @param L 顺序表指针
 *  @param i 元素位置
 *
 *  @return 返回查找到的元素指针
 */
ElemType* SqListElem(SqList *L, int i) {
    if (i<1 || i>L->length+1) return NULL;
    return L->elem+i-1;
}

/**
 *  查找元素位置
 *
 *  @param L 顺序表指针
 *  @param e 元素
 *
 *  @return 返回查找到的位置，没有则返回0
 */
int SqListLocation(SqList *L, ElemType e) {
    int i = 1;
    for (ElemType *p = L->elem; p<L->elem+L->length; p++) {
        if (*p == e) {
            return i;
        }
        i++;
    }
    
    return 0;
}

//顺序表置空
void SqListClear(SqList *L) {
    L->length = 0;
    printf("已清空\n");
}



/**
 *  遍历顺序表
 *
 *  @param L      顺序表指针
 *  @param MyFunc 函数指针，用于打印
 */
void SqListTraverse(SqList *L, void (*MyFunc)(ElemType *)) {
    if (!L || !MyFunc) return;
    
    printf("遍历开始:");
    for (ElemType *p = L->elem; p<L->elem+L->length;p++) {
        MyFunc(p);
    }
    printf("遍历结束!\n");
}



/**
 *  测试用例
 */
//打印元素
void SqListPrint(ElemType *e) {
    if (e) {
        printf("%d ",*e);
    }
}

void SqListTest() {
    SqList sqlist,*L;
    L = &sqlist;
    
    SqListInit(L);
    printf("输入5个元素：\n");  //如：1，2，3，4，5
    for (int i=1;i<=INIT_SIZE;i++) {
        int a;
        scanf("%d",&a);
        SqListInsert(L, a, i);
    }
    SqListTraverse(L,SqListPrint);
    
    int loc = SqListLocation(L,4);
    printf("元素4的位置是%d\n",loc);
    
    SqListDelete(L,3);
    SqListTraverse(L,SqListPrint);
    
    SqListClear(L);
    SqListTraverse(L,SqListPrint);
    
    SqListDestroy(L);
}












