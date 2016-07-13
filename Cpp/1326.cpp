#include <iostream>
#include <cstring>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
#define ERROR 0;
#define OK 1;

typedef int Status;
typedef int ElemType;
typedef struct LNode {
    ElemType data;
    LNode *next;
} LNode, *LinkedList;


Status GetElem_Link(LinkedList &L, int i, ElemType &e) {
    //L为带头结点的单链表的头指针
    //当第i个元素存在时，把第i个元素赋给e，并返回OK，否则返回ERROR
    LinkedList p;
    p = L->next;
    int j = 1; //初始化，p指向第1个节点，j为计数器
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;
    e = p->data;
    return OK;
}

Status ListInsert_Link(LinkedList &L, int i, ElemType e) {
    /**
     * 在带头结点的单链线性表L的第i个元素之前插入元素e
     */
    LinkedList p, s;
    p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1)
        return ERROR;
    s = (LinkedList) malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status ListDelete_Link(LinkedList &L, int i, ElemType &e) {
    //在头结点的单链表L中，删除第i个元素,并由e返回其值
    LinkedList p, q;
    p = L;
    int j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i - 1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}

void CreateList_Link(LinkedList &L, int n) {
    //逆位序输入n个元素的值,建立带头结点的单链表
    LinkedList p;
    int i;
    L = (LinkedList) malloc(sizeof(LNode)); //L是头结点
    L->next = NULL;
    for (i = n; i > 0; --i) {
        p = (LinkedList) malloc(sizeof(LNode));
        scanf("%d", &p->data);
        /**
         * 以下是头插法增加节点
         */
        p->next = L->next;
        L->next = p;
    }
}

int main(int argc, char *argv[]) {

}




