#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

#define OK 0;
#define ERROR -1;

using namespace std;
typedef int Status;

typedef struct {
    char name[100];
} ElemType;

typedef struct {
    ElemType *elem;
    int length; //当前长度
    int listsize;   //当前分配的存储容量
} SqList;

Status InitList_Sq(SqList &L) {
    //构造一个空的线性表
    L.elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        return ERROR;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e) {
    //在顺序表的第i个元素前插入新的元素e
    //i的合法范围为1 <= i <= ListLength_Sq(L) + 1
    ElemType *p;
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= L.listsize) {
        ElemType * newbase = (ElemType *) realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return ERROR;
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    ElemType *q = &(L.elem[i - 1]); //q为插入位置
    for (p = &(L.elem[L.length - 1]); p >= q; --p) //从第i - 1个位置开始往后挪1个位置，从后往前依次往后挪
        *(p + 1) = *p;
    *q = e; //插入的位置赋值为e
    ++L.length; //表长增1
    return OK;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e) {
    //在顺序线性表中删除第i个元素,并用e返回其值
    //i的合法值为1 <= i <= ListLength_Sq(L)
    ElemType *p, *q;
    if (i < 1 || i > L.length)
        return ERROR;
    p = &(L.elem[i - 1]); //p为被删除元素的位置
    e = *p;
    q = L.elem + L.length - 1;
    for (++p; p < q; ++p)
        *(p - 1) = *p;
    --L.length;
    return OK;
}

int LocateElem_Sq(SqList L, ElemType e, Status (*compare) (ElemType, ElemType)) {
    //在顺序表L中查找第1个与e满足compare()的元素的位置
    //若找到返回其在L中的位序,否则返回0
    int i;
    ElemType *p;
    i = 1; //i的初值为第1个元素的位置
    p = L.elem; //p的初值为第1个元素的存储位置
    while (i <= L.length && !(*compare) (*p++, e))
        ++i;
    if (i <= L.length)
        return i;
    else
        return 0;
}

void ListShow(SqList L)
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (i)
            printf(" ");
        printf("%s", L.elem[i].name);
    }
    printf("\n");
}

Status compare(ElemType e1, ElemType e2) {
    return (Status)!strcmp(e1.name, e2.name);
}

int main(int argc, char *argv[]) {
    SqList namelist;
    InitList(&namelist);
    char strInstruct[10];
    int pos;
    ElemType e;

    while (~scanf("%s", strInstruct)) {
        if (!strcmp(strInstruct, "insert")) {
            scanf("%d%s", &pos, e.name);
            ListInsert(&namelist, pos, e);
        }
        else if (!strcmp(strInstruct, "show")) {
            ListShow(namelist);
        }
        else if (!strcmp(strInstruct, "delete")) {
            scanf("%s", e.name);
            pos = LocateElem(namelist, e, cmp);
            ListDelete(&namelist, pos, &e);
        }
        else if (!strcmp(strInstruct, "search")) {
            scanf("%s", e.name);
            printf("%d\n", LocateElem(namelist, e, cmp));
        }
    }
    return 0;
}







