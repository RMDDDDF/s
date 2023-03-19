/***************************************************************************************
 *	File Name				:	linkedList.h
 *	CopyRight				:	2020 QG Studio
 *	SYSTEM					:   win10
 *	Create Data				:	2020.3.28
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *
 *
 ***************************************************************************************/

 /**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#define _CRT_SECURE_NO_WARNINGS 1//不要报warning
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/**************************************************************
*	Macro Define Section
**************************************************************/

#define OVERFLOW -1
#define LEN sizeof(struct LNode)//定义常量LEN表示一个节点的长度

/**************************************************************
*	Struct Define Section
**************************************************************/

// define element type
typedef int ElemType;

// define struct of linked list
typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LNode, * LinkedList;

// define Status
typedef enum Status {
	ERROR,
	SUCCESS
} Status;


/**************************************************************
*	Prototype Declare Section
**************************************************************/
/**
 *  @name        : int menu(void)
 *	@description : create a menu
 *	@param		 : void
 *	@return		 : int
 *  @notice      : None
 */
int menu(void)
{
	printf("***********************************\n");
	printf("*       单向链表功能测试          *\n");
	printf("*     0.退出                      *\n");
	printf("*     1.初始化链表                *\n");
	printf("*     2.销毁链表                  *\n");
	printf("*     3.在p节点后插入             *\n");
	printf("*     4.删除指定节点后一个节点    *\n");
	printf("*     5.遍历链表并输出内容        *\n");
	printf("*     6.找寻某一节点              *\n");
	printf("*     7.反转链表                  *\n");
	printf("*     8.判断是否是循环链表        *\n");
	printf("***********************************\n");
	printf("请选择>");
	int option;//用户做出的选择
	scanf("%d", &option);
	return option;

}
/**
 *  @name        : int judge(char string[])
 *	@description : judge whether the data is right
 *	@param		 : char string[]
 *	@return		 : int
 *  @notice      : None
 */
int judge(char string[])
{

	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] < '0' || (string[i] > '9'))
		{
			return 0;
		}
	}
	return 1;
}
/**
 *  @name        : int translate(char string[])
 *	@description : translate the string into a number whose form is int
 *	@param		 : char string[]
 *	@return		 : int
 *  @notice      : None
 */
int translate(char string[])
{
	int arr[100] = { 0 };
	int ret = 0;
	int i = 0;
	int j;
	for (i = 0, j = strlen(string); i < strlen(string); i++, j--)
	{
		arr[j - 1] = string[i] - 48;
	}
	int x = 1;//控制个十百千位数
	for (int o = 0; o < i; o++)
	{
		ret += arr[o] * x;
		x *= 10;
	}

	return ret;
}
/**
 *  @name        : LNode* GetQ(void)
 *	@description : get the data of q
 *	@param		 : void
 *	@return		 : LNode*
 *  @notice      : None
 */
LNode* GetQ(char string[])
{
	char useless[100] = "0";//用来吞掉回车键
	gets(useless);
	string[100] = "0";
	LNode* q = (LNode*)malloc(LEN);
	printf("请输入要插入的节点data：\n");
	gets(string);
	while (!judge(string))//当输入的数据超出范围时提醒重新输入
	{
		printf("输入错误\n");
		printf("请输入data：\n");
		gets(string);
	}
	q->data = translate(string);
	return q;
}
/**
 *  @name        : LNode* GetP(void)
 *	@description : get the data of q
 *	@param		 : LinkedList *head
 *	@return		 : LNode*
 *  @notice      : None
 */
LNode* GetP(LinkedList* head)
{
	LinkedList* L = head;
	char string[100] = "0";//用于存储输入的data
	int jud = 0;//判断是否找到对应的节点
	LNode* p = NULL;
	if ((*L) == NULL)//链表没有初始化
	{
		printf("链表不存在！");
		return NULL;
	}
	if ((*L)->next == NULL)//说明此节点为末尾
	{
		printf("此为末尾！");
		return *head;
	}
	if ((*L)->next != NULL)
	{
		printf("请输入p节点的data：\n");
		gets(string);
		if (judge(string))
		{

			while (*L)
			{
				if ((*L)->data == translate(string))
				{
					p = *L;
					jud = 1;
					return p;
				}
				*L = (*L)->next;
			}
			if (jud == 0)
			{
				printf("未找到该数值对应的节点，请检查\n");
			}
		}
	}
}
/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */

Status InitList(LinkedList* L)
{
	/*L = (LinkedList)malloc(LEN);*/
	L = &(*L);
	*L = (LinkedList)malloc(LEN);
	(*L)->next = NULL;
	printf("链表初始化成功！\n");
	return SUCCESS;
};


/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList* L)
{
	if ((*L)->next == NULL)
	{
		printf("链表不存在！\n");
	}
	else
	{
		LinkedList p1, p2;
		p1 = p2 = *L;//令p1和p2先指向头指针
		while (p1->next)
		{
			p2 = p1->next;
			free(p1);
			p1 = p2->next;
		}
		L = NULL;//最后使头指针指向空，链表销毁完毕
		printf("链表销毁完毕！\n");
	}
};

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode* p, LNode* q) 
{
	
	if (p == NULL)//链表还未初始化
	{
		printf("错误!\n");
		return ERROR;
	}
	//if (p->next == NULL)//仅存在头指针
	//{
	//	p->next = q;
	//	q->next = NULL;
	//	printf("该指针已成为链表中第一个节点！");
	//	return SUCCESS;
	//}
	else
	{
		LNode* pr;//用以存储插入前p的下一个节点
		pr = p->next;
		p->next = q;
		q->next = pr;
		printf("插入完成！\n");

		return SUCCESS;
	}

};

/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode* p, ElemType* e) 
{
	if (p == NULL)//链表还未初始化
	{
		printf("错误!\n");
		return ERROR;
	}
	if (p->next == NULL)//p为最后一个
	{
		printf("错误!\n");
		return ERROR;
	}
	if (p->next != NULL) 
	{
		LNode* ne;//创建q指针指向p的下一个节点
		ne = p->next;
		p->next = ne->next;//使p的next指针指向q的下一个节点
		*e = ne->data;//将数据交给e
		printf("节点删除成功，数据为%d\n", *e);
		free(ne);
		return SUCCESS;
		
	}
	
};

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */

void visitData(ElemType* e)//访问当前节点的数据
{
	if (e != NULL)
		printf("当前访问的数据如下：%d\n", *e);
}

void TraverseList(LinkedList L, void (*visit)(ElemType* e))
{
	ElemType* e = NULL;
	if (L->next == NULL)//头指针为空
	{
		printf("链表为空，请输入数据后再尝试遍历！\n");//报错机制
	}
	else
	{
		LNode* q = L;//第一个
			while (q)//当L不指向空时
			{
				visit(&(q->data));
				q = q->next;
			}
		
	}


};


/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */

Status SearchList(LinkedList L, ElemType e) 
{

	if (L != NULL) //当头指针指向的位置存有数据时
	{
		int judge = 0;//判断是否找到
		LinkedList p1 = L;
		while (p1) //当链表存在时
		{
			if (e==p1->data) {
				printf("存在该节点");
				judge = 1;
				return SUCCESS;
			}
			p1 = p1->next;
		}
		if (judge == 0)
		{
			printf("不存在该节点！");
			return ERROR;

		}
	}
	else {
		printf("链表为空！\n");
		return ERROR;
	}
		
};

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList* L) {

	if (L != NULL)
	{
		LinkedList  beg = NULL;
		LinkedList  mid = *L;
		LinkedList  end = (*L)->next;
		while (1)//一直遍历
		{

			mid->next = beg;//使mid的下一个节点指向beg

			if (end == NULL) //判断 end 是否为 NULL，如果成立则退出循环
				break;
			//整体向后移动 3 个指针
			beg = mid;
			mid = end;
			end = end->next;
		}
		*L = mid;//最后使头指针指向mid
		printf("反转链表完成！\n");
		return SUCCESS;
	}
	else 
	{
		printf("链表不存在！\n");
		return ERROR;
		
	}
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L)
{
	if ((L != NULL)&&(L->next!=NULL))
	{
		LinkedList p1, p2;
		p1 = L;
		p2 = L->next;
		int judge = 0;//判断是否有循环链表，0为没有，1为有

		while ((p2 != NULL) && (p2->next != NULL))//判断此时p2和p2的下一节点是否为空指针
		{
			p2 = p2->next->next;//p2比p1走得快
			p1 = p1->next;
			if (p1 == p2)
				judge = 1;
				return SUCCESS;
		}
		if (judge == 0)
		{
			printf("该链表不是循环链表！\n");
			return ERROR;
		}
		
	}
	else
	{
		printf("链表不存在！\n");
		return ERROR;
	}
};

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/

void main()
{
	LinkedList* head = (LinkedList*)malloc(LEN);//创建头指针
	//head->next = NULL;
	*head = NULL;
	char string[100] = "0";//用于存储输入的data
	//LNode* p = (LNode*)malloc(LEN);//创建p指针
	ElemType* e = NULL;
	bool isDone = false;
	while (!isDone)
	{
		//根据具体的功能处理//
		switch (menu())
		{
		case 0:
				isDone = true;
				break;
		case 1:
				InitList(head);
				break;
			case 2:
				DestroyList(head);
				break;
			case 3:
				InsertList(GetP(head), GetQ(string));
				break;
			case 4:
				DeleteList(GetP(head), e);
				break;
			case 5:
				TraverseList(*head, visitData);
				break;
			case 6:
				printf("请输入要查询的节点的data：");
				gets(string);
				gets(string);
				int data;
				if (judge(string))
				{
					data = translate(string);
				}
				SearchList(*head, data);
				break;
			case 7:
				ReverseList(head);
				break;
			case 8:
				IsLoopList(*head);
				break;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
		//清屏
		system("pause");
		system("cls");
	}




}
