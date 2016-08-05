//
//  BiTree.c
//  C_DataStructures
//
//  Created by chen on 16/7/28.
//  Copyright © 2016年 ___CHEN___. All rights reserved.
//
/**
 *  二叉树链表存储表示
 */
#include "BiTree.h"
#include <stdlib.h>
#include <stdbool.h>

typedef char TElemType;

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiNode, *BiTree;


/*创建二叉树*/
/*按先序次序输入二叉树中结点的值，#表示空树*/
void BTreeInit(BiTree *T) {
    char ch;
    scanf("%c", &ch);
    if (ch == '#') {  //#表示空结点
        *T = NULL;
    } else {
        *T = (BiTree)malloc(sizeof(BiNode));
        if (!T) {
            printf("分配失败！");
            exit(-1);
        }
        (*T)->data = ch;            //生成根结点
        BTreeInit(&(*T)->lchild);   //构造左子树
        BTreeInit(&(*T)->rchild);   //构造右子树
    }
}

//递归实现遍历 -----------------------------------------------------
/*先序遍历*/
void BTreePreOrderTraverse(BiTree T, void(*vi)(TElemType e)) {
    if (!T || !vi) return;
    vi(T->data);
    BTreePreOrderTraverse(T->lchild,vi);
    BTreePreOrderTraverse(T->rchild,vi);
}


/*中序遍历*/
void BTreeInOrderTraverse(BiTree T, void(*vi)(TElemType e)) {
    if (!T || !vi) return;
    BTreeInOrderTraverse(T->lchild,vi);
    vi(T->data);
    BTreeInOrderTraverse(T->rchild,vi);
}

/*后序遍历*/
void BTreeBackOrderTraverse(BiTree T, void(*vi)(TElemType e)) {
    if (!T || !vi) return;
    BTreeBackOrderTraverse(T->lchild,vi);
    BTreeBackOrderTraverse(T->rchild,vi);
    vi(T->data);
}


//非递归实现遍历 -----------------------------------------------------
//TODO:


//求深度
int BTreeDepth(const BiTree T) {
    int depth = 0;
    if(T) {
        int left = BTreeDepth(T->lchild);
        int right = BTreeDepth(T->rchild);
        depth = (left>right?left:right)+1;
    }
    return depth;
}

//叶子结点个数
void BTreeLeafCount(const BiTree T, int *count) {
    if (T) {
        if (!T->lchild && !T->rchild) (*count)++;
        BTreeLeafCount(T->lchild, count);
        BTreeLeafCount(T->rchild, count);
    }
}

//所有结点个数
void BTreeAllCount(const BiTree T, int *count) {
    if (T) {
        (*count)++;
        BTreeAllCount(T->lchild, count);
        BTreeAllCount(T->rchild, count);
    }
}

//test
/* 如下面二叉树， 先序输入为：ABC##D##EF### ABCD###E##F##
     A
   B   E
  C D F
 
*/
void BTreePrint(const TElemType e) {
    if (e) {
        printf("%c ",e);
    }
}

void BTreeTest() {
    printf("请输入二叉树：");
    BiTree T = NULL;
    BTreeInit(&T);
    printf("----创建成功！-----");
    
    printf("\n先序遍历：");
    BTreePreOrderTraverse(T,BTreePrint);
    
    printf("\n中序遍历：");
    BTreeInOrderTraverse(T,BTreePrint);
    
    printf("\n后序遍历：");
    BTreeBackOrderTraverse(T,BTreePrint);
    
    printf("\n深度=%d\n",BTreeDepth(T));
    
    int count = 0;
    BTreeLeafCount(T,&count);
    printf("\n叶子结点个数=%d\n",count);

    count = 0;
    BTreeAllCount(T,&count);
    printf("\n所有结点个数=%d\n",count);

}

