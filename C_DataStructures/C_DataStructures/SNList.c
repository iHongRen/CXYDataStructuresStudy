//
//  SNList.c
//  CXYDataStuctures
//
//  Created by chen on 16/7/6.
//  Copyright © 2016年 ___CHEN___. All rights reserved.
//

/**
 *  动态单链表（带头结点）
 */
#include "SNList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef int SNElemType;

typedef struct LNode {
    SNElemType data;
    struct LNode *next;
}LNode, *LinkList;


void SNListInit(LinkList *L) {
    /**
     *  创建头结点【*(*L)】，并使L指向头结点；
     *  要改变参数的值，所有需要用指针作为参数
     */
    *L = (LinkList)malloc(sizeof(LNode));
    if (!*L) return exit(-1);
    (*L)->next = NULL;
    printf("初始化成功\n");
}

void SNListDestroy(LinkList *L) {
    if (!L) return;
    LinkList q;
    while (*L) {
        q = (*L)->next;
        free(*L);
        *L = q;
    }
}

void SNListClear(LinkList L) {  /*不改变L,即不需要使用指针*/
    if (!L) return;
    LinkList p = L->next;
    while (p) {
        LinkList q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}

bool SNListEmpty(LinkList L) {
    return L->next == NULL;
}


int SNListLength(LinkList L) {
    if (!L) return 0;
    int i = 0;
    LinkList p = L->next;
    while (p) {
        i++;
        p = p->next;
    }
    return i;
}


void SNListGetElem(LinkList L, int i, SNElemType *e) {
    if (!L) return;
    
    int j = 1;
    LinkList p = L->next;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        printf("没有找到！\n");
        return;
    }
    *e = p->data;
}


bool SNListInsert(LinkList L, int i, SNElemType e) {
    if (!L) return false;
    int j = 0;
    LinkList p = L;
    while (p && j < i-1) {
        p = p->next;
        j++;
    }
    
    if (!p && j > i-1) {
        printf("插入位置不对\n");
        return false;
    }
    
    LinkList q = (LinkList)malloc(sizeof(LNode));
    q->data = e;
    q->next = p->next;
    p->next = q;
    return true;
}


bool SNListDelete(LinkList L, int i, SNElemType *e) {
    if (!L) return false;
    int j = 0;
    LinkList p = L;
    while (p->next && j < i-1) {
        p = p->next;
        j++;
    }
    
    if (!p->next || j>i-1) {
        printf("删除位置越界！\n");
        return false;
    }
    
    LinkList q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return true;
}

void SNListTraverse(LinkList L, void(*vi)(SNElemType)) {
    if (!L) return;
     printf("遍历开始\n");
    LinkList p = L->next;
    while (p) {
        vi(p->data);
        p = p->next;
    }
}


int SNListLocateElem(LinkList L,SNElemType e,bool(*compare)(SNElemType,SNElemType)) {
    if (!L) return 0;
    int i = 0;
    LinkList p = L->next;
    while (!p) {
        i++;
        if (compare(e,p->data)) {
            return i;
        }
        p = p->next;
    }
    printf("没有找到对应的位置\n");
    return 0;
}


/**
 *  链表反转(1.循环法)
 *  思路： 如链表：*L(头结点)， 10，20，30，40.
 *  第一次循环将20移到L与10之间：L,20,10,30,40,
 *  第二次循环将30移到L与20之间：L,30,20,10,40,
 *  第三次循环将40移到L与30之间：L,40,30,20,10.
 *  以此类推... 就完成了单链表的反转
 */
void SNListReversal(LinkList L) {
    if (!L) return;
    printf("开始反转\n");
    LinkList p = L->next;
    LinkList q = NULL;
    while (p->next) {
        q = p->next;
        p->next = q->next;
        q->next = L->next;
        L->next = q;
    }
}


//打印元素
void SNListPrint(SNElemType e) {
    printf("%d ",e);
}


void SNListTest() {
    LNode node;
    LinkList L = &node;
    
    SNListInit(&L); //L 头结点指针
    for (int i=0; i<5; i++) {
        SNListInsert(L,i+1,(i+1)*10);
    }
    SNListTraverse(L, SNListPrint);

    SNListReversal(L);
    SNListTraverse(L, SNListPrint);
}

