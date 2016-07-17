/**
 * 一元多项式加减
 * 数据结构：链表的基本操作
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

typedef int PElemType;
typedef struct PLink {
    float coef;
    PElemType exp;
    struct PLink *next;
} PLink;

typedef struct {
    PLink *head;
    // PElemType length;
} PLinkList;


PLink* GetHead(PLinkList p) {
    if (p.head != nullptr)
        return p.head;
    else std::exit(EXIT_FAILURE);
}

PLink* NextPos(PLinkList p, PLink *h) {
    if (h != nullptr)
        return h->next;
    else std::exit(EXIT_FAILURE);
}

PElemType GetCurElem(PLink *p) {
    if (p != nullptr)
        return p->exp;
    else {
        std::cerr << "GetCurElem error!\n";
        std::exit(EXIT_FAILURE);
    }
}

int Compare(PElemType a, PElemType b) {
    if (a < b) return -1;
    if (a == b) return 0;
    else return 1;
}

void SetCurElem(PLink *p, PElemType t) {

}

void AddPolyn(PLinkList &Pa, PLinkList &Pb) {
    PLink *ha, *hb, *qa, *qb;
    PElemType a, b, temp;
    float sum;
    ha = GetHead(Pa);
    hb = GetHead(Pb);
    qa = NextPos(Pa, ha); //qa，qb分别指向La,Lb中的当前节点
    qb = NextPos(Pb, hb);
    while (qa && qb) {  //Pa, Pb均非空
        a = GetCurElem(qa);  //a和b为两表中当前比较元素
        b = GetCurElem(qb);
        switch (Compare(a, b)) {
        case -1: //多项式Pa中当前节点的指数值小
            ha = qa;
            qa = NextPos(Pa, qa);
            break;
        case 0: //俩者的指数值相等
            sum = qa->coef + qb->coef;
            if (sum != 0.0) {
                temp.coef = sum;
                temp.expn = a.expn;
                SetCurElem(qa, temp);
                ha = qa;
            } else { //删除多项式Pa当前节点
                DelFirst(ha, qa);
                FreeNode(qa);
            }
            DelFirst(ha, qb);
            FreeNode(qb);
            qb = NextPos(Pb, hb);
            qa = NextPos(Pa, ha);
            break;
        case 1: //多项式中Pb中当前节点指数值小
            DelFirst(hb, qb);
            InsFirst(ha, qb);
            qb = NextPos(Pb, hb);
            ha = NextPos(Pa, ha);
            break;
        }
    }
    if (!Empty(Pb))
        Append(Pa, qb); //链接Pb中剩余节点
    FreeNode(hb);   //释放Pb的头结点
} //AddPoly






