//
//  SLQueue.c
//  CXYDataStuctures
//
//  Created by chen on 16/7/25.
//  Copyright © 2016年 ___CHEN___. All rights reserved.
//
/**
 *  队列，是先进先出(FIFO,First-In-First-Out)的线性表。
 *  队列只允许在后端(rear)进行插入，在前段(front)进行删除。
 */
/**
 *  单链队列，使用链表作为基本数据结果，所以不存在伪溢出的问题。队列长度没有限制，但插入和读取的时间代价较高。
 */
#include "SLQueue.h"
#include <stdbool.h>
#include <stdlib.h>

typedef int QElemType;

// 单链队列存储结构
typedef struct QNode {
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} SLQueue;


void SLQueueInit(SLQueue *q) {
    q->front = (QueuePtr)malloc(sizeof(QNode)); //头结点
    if (!q->front) {
        printf("存储分配失败！");
        return;
    }
    q->rear = q->front;
    q->front->next = NULL;
}

void SLQueueDestroy(SLQueue *q) {
    while (q->front) {
        q->rear = q->front->next; /*q->rear 作为临时存储用*/
        free(q->front);
        q->front = q->rear;
    }
}

void SLQueueClear(SLQueue *q) {
    QueuePtr p,t;
    q->rear = q->front;  //尾指针也指向头结点，与初始化时一致。
    p = q->front->next;
    q->front->next = NULL;   //断开头结点与其他结点的连接
    while (p) {          //逐个释放其他结点
        t = p;
        p = p->next;
        free(t);
    }
}

bool SLQueueIsEmpty(SLQueue *q) {
    return q->front->next == NULL;   //头结点的next结点是否为空
}

int SLQueueLength(SLQueue *q) {
    QueuePtr p = q->front;
    int i = 0;
    while (p != q->rear) {
        i++;
        p = p->next;
    }
    return i;
}

bool SLQueueGetHead(SLQueue *q, QElemType *e) {
    if (q->front == q->rear) return false;
    QueuePtr p = q->front->next;
    *e = p->data;
    return true;
}

void SLQueueEn(SLQueue *q, QElemType e) {
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) {
        printf("插入分配失败！");
        return;
    }
    p->data = e;
    p->next = NULL;
    
    q->rear->next = p;
    q->rear = p;
}

bool SLQueueDe(SLQueue *q, QElemType *e) {
    if (q->front == q->rear) {
        return false;
    }
    
    QueuePtr p = q->front->next; 
    q->front->next = p->next;   //将头结点指向p的下一个结点
    *e = p->data;
    if (p == q->rear) {
        q->rear = q->front;  //最后一个元素p释放时，q->rear也释放了。此时需要将q->rear重新指向q->front;
    }
    free(p);
    return true;
}

void SLQueueTraverse(SLQueue *q,void(*MyFunc)(QElemType)) {
    printf("开始遍历：\n");
    QueuePtr p = q->front->next;
    while (p) {
        if (MyFunc) {
            MyFunc(p->data);
        }
        p = p->next;
    }
    printf("\n");
}


//测试
void SLQueuePrint(QElemType e) {
    printf("%d ", e);
}

void SLQueueTest() {
    SLQueue queue, *q;
    q = &queue;
    SLQueueInit(q);
    SLQueueEn(q, 1);
    SLQueueEn(q, 2);
    SLQueueEn(q, 3);
    SLQueueTraverse(q, SLQueuePrint);

    int len = SLQueueLength(q);
    printf("len = %d\n",len);

    QElemType e;
    SLQueueGetHead(q, &e);
    SLQueuePrint(e);
    printf("\n");
    
    SLQueueDe(q, &e);
    SLQueuePrint(e);
    printf("\n");
    SLQueueTraverse(q, SLQueuePrint);
}
