#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int count1=0;
int count2=0;

Stack_Node *Init_Link_Stack()
{
	Stack_Node *top=NULL;
	printf("��ʼ����ջ�ɹ���\n\n");
	return (top);
}

Stack_Node *push(Stack_Node *top,ElemType e)
{
	Stack_Node *p;
	p=(Stack_Node *)malloc(sizeof(Stack_Node));
	if(!p)
	{
		printf("�����½��ʧ�ܣ�\n\n");
		return ERROR;
	}
	p->data=e;
	p->next=top;
	top=p;
	count1++;
	printf("��%d��Ԫ��%dѹջ�ɹ���\n\n",count1,e);
	return p;
}

Stack_Node *pop(Stack_Node *top)
{
	ElemType e;
	Stack_Node *p;
	if (top==NULL)
	{
		printf("ջ�ѿգ�����ջ��Ԫ��ʧ��!\n\n");
		return ERROR;
	}
	p=top;
	e=p->data;
	count2++;
	printf("��%d��Ԫ�ص�����Ԫ��Ϊ%d",count2,e);
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


