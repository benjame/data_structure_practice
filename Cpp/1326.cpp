#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1

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

int ShowLinkedList(LinkedList L) {
    //显示链表中的元素
    int numOfList = 0; //记录链表中元素个数
    LinkedList p = L->next; //用来遍历链表元素的指针
    while (p) {
        if (numOfList) {
            putchar(' ');
        }
        ++numOfList;
        printf("%d", p->data);
        p = p->next;
    }
    if (numOfList == 0)
        return 0; //numOfList为0表示链表为空直接返回0表示链表中元素数目为0
    else {
        printf("\n");
        return numOfList; //返回链表中元素的个数
    }
}

int main(int argc, char *argv[]) {
    int n;    // 初始时元素的数目
    int m;    // 指令的数目
    char strInst[30];  // 存储指令:instruction
    int a;    // 存储位置数据
    LinkedList L;  // 链表
    int e;   // 定义节点，用来存储获取的节点或者删除的节点
    scanf("%d", &n); // 读入元素的数目
    CreateList_Link(L, n); // 创建链表
    scanf("%d", &m); // 读取指令的数目
    while (m--) { // 做 m 次循环
        scanf("%s", strInst);  // 读取指令
        if (strcmp(strInst, "get") == 0) // 如果是需要获取某个元素
        {
            scanf("%d", &a);  // 读取元素的位置
            if (GetElem_Link(L, a, e) == OK) // 如果获取元素成功
            {
                printf("%d\n", e); // 输出元素的值
            }
            else  // 如果获取元素失败
            {
                puts("get fail");  // 输出获取元素的出错信息
            }
        }
        else if (strcmp(strInst, "insert") == 0) // 如果是插入某个元素
        {
            scanf("%d%d", &a, &e);   // 获取待插入的位置以及待插入的值
            if (ListInsert_Link(L, a, e) == OK) // 如果插入元素成功
            {
                puts("insert OK"); // 输出插入成功的信息
            }
            else
            {
                puts("insert fail"); // 否则输出插入失败的信息
            }
        }
        else if (strcmp(strInst, "delete") == 0) // 如果是删除某个元素
        {
            scanf("%d", &a);  // 获得待删除元素的位置
            if (ListDelete_Link(L, a, e) == OK)        // 如果删除成功
            {
                puts("delete OK"); // 输出删除成功的信息
            }
            else
            {
                puts("delete fail"); // 否则输出删除失败的信息
            }
        }
        else if (strcmp(strInst, "show") == 0) // 如果是显示链表
        {
            if (ShowLinkedList(L) == 0) // 如果链表为空
            {
                puts("Link list is empty"); //显示量表为空的信息
            }
        }
    }

    return 0;
}




