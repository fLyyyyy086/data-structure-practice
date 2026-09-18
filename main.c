#include<stdio.h>
#include<stdlib.h>

//单链表结点定义
typedef struct Node
{
	int data;
	struct Node* next;
}slink;

//创建新结点
slink* CreateNode(int data)
{
    slink* p = (slink*)malloc(sizeof(slink));

    if (p == NULL)
    {
        printf("内存分配失败！\n");
        exit(1);
    }

    p->data = data;
    p->next = NULL;

    return p;
}
//初始化带头结点的单链表
void InitList(slink* L)
{
    L->next = NULL;
}
//判断集合中是否已存在某个元素
int Exists(slink* L, int x)
{
    slink* p = L->next;

    while (p != NULL)
    {
        if (p->data == x)
        {
            return 1;
        }

        p = p->next;
    }

    return 0;
}
//尾插法插入元素
void Insert(slink* L, int x)
{
    slink* p;
    slink* newNode;

  /*集合不能有重复元素*/
    if (Exists(L, x))
    {
        return;
    }

    newNode = CreateNode(x);

    p = L;

    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = newNode;
}

//输入集合
void InputSet(slink* L)
{
    int n;
    int i;
    int x;

    printf("请输入集合元素个数：");
    scanf_s("%d", &n);

    printf("请输入 %d 个整数：\n", n);

    for (i = 0; i < n; i++)
    {
        scanf_s("%d", &x);
        Insert(L, x);
    }
}
//输出集合
void PrintList(slink* L)
{
    slink* p = L->next;

    printf("{ ");

    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("}\n");
}
//实现递增排序
slink* Sort(slink* L)
{
    slink* p;
    slink* q;
    slink* minNode;
    int temp;

    if (L == NULL || L->next == NULL)
    {
        return L;
    }

    p = L->next;

    while (p != NULL)
    {
        minNode = p;
        q = p->next;

        while (q != NULL)
        {
            if (q->data < minNode->data)
            {
                minNode = q;
            }

            q = q->next;
        }

        /* 交换数据 */
        if (minNode != p)
        {
            temp = p->data;
            p->data = minNode->data;
            minNode->data = temp;
        }

        p = p->next;
    }

    return L;
}
//求并集
void Union(slink* la, slink* lb, slink* lc)
{
    slink* pa = la->next;
    slink* pb = lb->next;

    /* 清空 C */
    lc->next = NULL;

    while (pa != NULL && pb != NULL)
    {
        if (pa->data < pb->data)
        {
            Insert(lc, pa->data);
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            Insert(lc, pb->data);
            pb = pb->next;
        }
        else
        {
            /* 两个集合元素相同，只加入一次 */
            Insert(lc, pa->data);

            pa = pa->next;
            pb = pb->next;
        }
    }

    /* A 中剩余元素 */
    while (pa != NULL)
    {
        Insert(lc, pa->data);
        pa = pa->next;
    }

    /* B 中剩余元素 */
    while (pb != NULL)
    {
        Insert(lc, pb->data);
        pb = pb->next;
    }
}
//求交集
void InerSect(slink* la, slink* lb, slink* lc)
{
    slink* pa = la->next;
    slink* pb = lb->next;

    /* 清空 C */
    lc->next = NULL;

    while (pa != NULL && pb != NULL)
    {
        if (pa->data < pb->data)
        {
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            pb = pb->next;
        }
        else
        {
            /* 相等，说明属于交集 */
            Insert(lc, pa->data);

            pa = pa->next;
            pb = pb->next;
        }
    }
}
//求差集
void Subs(slink* la, slink* lb, slink* lc)
{
    slink* pa = la->next;
    slink* pb = lb->next;

    /* 清空 C */
    lc->next = NULL;

    while (pa != NULL && pb != NULL)
    {
        if (pa->data < pb->data)
        {
            /* A 中有，B 中没有 */
            Insert(lc, pa->data);
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            /* B 当前元素较小，继续移动 B */
            pb = pb->next;
        }
        else
        {
            /* 两个集合都有，不属于 A-B */
            pa = pa->next;
            pb = pb->next;
        }
    }

    /* A 中剩余元素全部属于 A-B */
    while (pa != NULL)
    {
        Insert(lc, pa->data);
        pa = pa->next;
    }
}
//释放链表
void DestroyList(slink* L)
{
    slink* p;
    slink* q;

    p = L->next;

    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }

    L->next = NULL;
}
//主函数
int main()
{
    slink A;
    slink B;
    slink C;

    /* 初始化三个链表 */
    InitList(&A);
    InitList(&B);
    InitList(&C);

    printf("========== 集合 A ==========\n");
    InputSet(&A);

    printf("\n========== 集合 B ==========\n");
    InputSet(&B);

    /* 排序 */
    Sort(&A);
    Sort(&B);

    printf("\n========== 排序后的集合 ==========\n");

    printf("A = ");
    PrintList(&A);

    printf("B = ");
    PrintList(&B);


    /* 求并集 */
    Union(&A, &B, &C);

    printf("\n========== 并集 ==========\n");
    printf("A ∪ B = ");
    PrintList(&C);


    /* 求交集 */
    InerSect(&A, &B, &C);

    printf("\n========== 交集 ==========\n");
    printf("A ∩ B = ");
    PrintList(&C);


    /* 求差集 */
    Subs(&A, &B, &C);

    printf("\n========== 差集 ==========\n");
    printf("A - B = ");
    PrintList(&C);


    /* 释放内存 */
    DestroyList(&A);
    DestroyList(&B);
    DestroyList(&C);

    return 0;
}
