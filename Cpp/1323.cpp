#include <string>
#include <cstdio> 
#include <cstdlib> 
#include <cmath> 
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define LIST_INIT_SIZE 10 /* 线性表存储空间的初始分配量 */
#define LISTINCREMENT 2 /* 线性表存储空间的分配增量 */
typedef int ElemType;
typedef int Status;
typedef int Boolean;
typedef struct {
    ElemType *elem;
    /* 存储空间基址 */
    int length;
    /* 当前长度 */
    int listsize; /* 当前分配的存储容量(以sizeof(ElemType)为单位) */
} SqList;

Status InitList(SqList *L) /* 算法2.3 */
{
    /* 操作结果：构造一个空的顺序线性表 */
    (*L).elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType)); //LIST_INIT_SIZE为10的常量
    if (!(*L).elem)
        exit(OVERFLOW); /* 存储分配失败 */
    (*L).length = 0; /* 空表长度为0 */
    (*L).listsize = LIST_INIT_SIZE; /* 初始存储容量 */
    return OK;
}

Status ListInsert(SqList *L, int i, ElemType e) /* 算法2.4 */
{
    /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)+1 */
    /* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
    ElemType *newbase, *q, *p;
    if (i < 1 || i > (*L).length + 1) /* i值不合法 */
        return ERROR;
    if ((*L).length >= (*L).listsize) /* 当前存储空间已满,增加分配 */
    {
        newbase = (ElemType *) realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW); /* 存储分配失败 */
        (*L).elem = newbase; /* 新基址 */
        (*L).listsize += LISTINCREMENT; /* 增加存储容量 */
    }
    q = (*L).elem + i - 1; /* q为插入位置 */
    for (p = (*L).elem + (*L).length - 1; p >= q; --p) /* 插入位置及之后的元素右移 */
        *(p + 1) = *p;
    *q = e; /* 插入e */
    ++(*L).length; /* 表长增1 */
    return OK;
}

Status ListTraverse(SqList L, void(*vi)(ElemType *)) {
    /* 初始条件：顺序线性表L已存在 */
    /* 操作结果：依次对L的每个数据元素调用函数vi()。一旦vi()失败，则操作失败 */
    /*           vi()的形参加'&'，表明可通过调用vi()改变元素的值 */
    ElemType *p;
    int i;
    p = L.elem;
    for (i = 1; i <= L.length; i++) {
        if (i != 1)
            printf(" ");
        vi(p++);
    }
    printf("\n");
    return OK;
}

int ListLength(SqList L) {
    /* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
    return L.length;
}

Status GetElem(SqList L, int i, ElemType *e) {
    /* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
    /* 操作结果：用e返回L中第i个数据元素的值 */
    if (i < 1 || i > L.length)
        exit(ERROR);
    *e = *(L.elem + i - 1);
    return OK;
}

int LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    /* 初始条件：顺序线性表L已存在，compare()是数据元素判定函数(满足为1,否则为0) */
    /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
    /*           若这样的数据元素不存在，则返回值为0。算法2.6 */
    ElemType *p;
    int i = 1; /* i的初值为第1个元素的位序 */
    p = L.elem; /* p的初值为第1个元素的存储位置 */
    while (i <= L.length && !compare(*p++, e))
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

Status equal(ElemType c1, ElemType c2) {
    /* 判断是否相等的函数，Union()用到 */
    if (c1 == c2)
        return TRUE;
    else
        return FALSE;
}

void print(ElemType *c) {
    printf("%d", *c);
}

void Union(SqList *La, SqList Lb) /* 算法2.1 */
{
    /* 将所有在线性表Lb中但不在La中的数据元素插入到La中 */
    ElemType e;
    int La_len, Lb_len;
    int i;
    La_len = ListLength(*La); /* 求线性表的长度 */
    Lb_len = ListLength(Lb);
    for (i = 1; i <= Lb_len; i++) {
        GetElem(Lb, i, &e); /* 取Lb中第i个数据元素赋给e */
        if (!LocateElem(*La, e, equal)) /* La中不存在和e相同的元素,则插入之 */
            ListInsert(La, ++La_len, e);
        ListTraverse(*La, print);
    }
}

Status reverse(SqList *L) {

}

int main(int argc, char *argv[]) {
    int n, m, a[105], b[105], cas = 0;
    while (~scanf("%d", &n)) {
        int j;
        if (cas++)
            printf("\n");
        for (j = 0; j < n; j++)
            scanf("%d", &a[j]);
        scanf("%d", &m);
        for (j = 0; j < m; j++)
            scanf("%d", &b[j]);
        SqList La, Lb;
        InitList(&La);
        for (j = 0; j < n; j++)
            ListInsert(&La, j + 1, a[j]);
        InitList(&Lb);
        for (j = 0; j < m; j++)
            ListInsert(&Lb, j + 1, b[j]);
        ListTraverse(La, print);
        ListTraverse(Lb, print);
        Union(&La, Lb);
    }
    return 0;
}
