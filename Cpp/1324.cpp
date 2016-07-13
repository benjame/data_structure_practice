#include <iostream>
#include <cstring>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
#define ERROR 0;
#define OK 1;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

using namespace std;
typedef int ElemType;
typedef int Status;
//typedef int Boolean;

typedef struct {
    ElemType *elem;
    int length;
    int listsize;
} List;


Status InitList(List &L) {
    L.elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        return ERROR;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert(List &L, int i, ElemType e) {
    /*初始条件：顺序线性表L已存在，1<=i<=ListLength(L) + 1*/
    /*操作结果：在L中第i个位置之前插入数据e，L的长度加1*/
    ElemType *newbase, *q, *p;
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= L.listsize) {
        newbase = (ElemType *) realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            std::exit(EXIT_FAILURE); //存储分配失败
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    q = L.elem + i - 1; //q指向插入的位置
    p = L.elem + L.length - 1;
    for (; p > q; --p)
        *(p + 1) = *p;
    *q = e;
    ++L.length;
    return OK;
}

Status ListTraverse(List L, void (*vi) (ElemType*)) {
    /* 初始条件：顺序线性表L已存在 */
    /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
    /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
    ElemType *p;
    int i;
    p = L.elem;
    for (i = 1; i <= L.length; ++i) {
        if (i != 1)
            printf(" ");
        vi(p++);
    }
    printf("\n");
    return OK;
}

int ListLength(List L) {
    return L.length;
}

Status GetElem(List L, int i, ElemType &e) {
    /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
    /* 操作结果：用e返回L中第i个数据元素的值 */
    if (i < 1 || i > L.length)
        std::exit(EXIT_FAILURE);
    e = *(L.elem + i - 1);
    return OK;
}

void print(ElemType *c) {
    printf("%d", *c);
}

void MergeList(List La, List Lb, List &Lc) {
    /* 已知线性表La和Lb中的数据元素按值非递减排列。 */
    /* 归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列 */
    int i = 1, j = 1, k = 0;
    int La_len, Lb_len;
    ElemType ai, bj;
    InitList(Lc); /* 创建空表Lc */
    La_len = ListLength(La);
    Lb_len = ListLength(Lb);
    while (i <= La_len && j <= Lb_len) {
        /* 表La和表Lb均非空 */
        GetElem(La, i, ai);
        GetElem(Lb, j, bj);
        if (ai <= bj) {
            ListInsert(Lc, ++k, ai);
            ++i;
        }
        else {
            ListInsert(Lc, ++k, bj);
            ++j;
        }
    }
    while (i <= La_len) {
        /* 表La非空且表Lb空 */
        GetElem(La, i++, ai);
        ListInsert(Lc, ++k, ai);
    }
    while (j <= Lb_len) {
        /* 表Lb非空且表La空 */
        GetElem(Lb, j++, bj);
        ListInsert(Lc, ++k, bj);
    }
}


int main(int argc, char *argv[]) {
    int n, m, a[105], b[105];
    while (~scanf("%d", &n)) {
        int j;
        for (j = 0; j < n; j++)
            scanf("%d", &a[j]);
        scanf("%d", &m);
        for (j = 0; j < m; j++)
            scanf("%d", &b[j]);
        List La, Lb, Lc;
        InitList(La); /* 创建空表La */
        for (j = 1; j <= n; j++) /* 在表La中插入n个元素 */
            ListInsert(La, j, a[j - 1]);
        InitList(Lb); /* 创建空表Lb */
        for (j = 1; j <= m; j++) /* 在表Lb中插入m个元素 */
            ListInsert(Lb, j, b[j - 1]);
        MergeList(La, Lb, Lc);
        /* 输出表Lc的内容 */
        ListTraverse(Lc, print);
    }
    return 0;
}


