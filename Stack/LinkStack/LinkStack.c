#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int count1=0;
int count2=0;

Stack_Node *Init_Link_Stack()
{
	Stack_Node *top=NULL;
	printf("初始化链栈成功！\n\n");
	return (top);
}

Stack_Node *push(Stack_Node *top,ElemType e)
{
	Stack_Node *p;
	p=(Stack_Node *)malloc(sizeof(Stack_Node));
	if(!p)
	{
		printf("申请新结点失败！\n\n");
		return ERROR;
	}
	p->data=e;
	p->next=top;
	top=p;
	count1++;
	printf("第%d个元素%d压栈成功！\n\n",count1,e);
	return p;
}

Stack_Node *pop(Stack_Node *top)
{
	ElemType e;
	Stack_Node *p;
	if (top==NULL)
	{
		printf("栈已空，弹出栈顶元素失败!\n\n");
		return ERROR;
	}
	p=top;
	e=p->data;
	count2++;
	printf("第%d个元素弹出的元素为%d",count2,e);
	printf("\n\n");
	top=p->next;
	free(p);
	return top;
}

void print_stack(Stack_Node *head)
{
	
	while (head)
	{
		printf("%4d",head->data);
		head=head->next;
	}
}


