#include <stdio.h>
#include "LinkStack.h"
extern int count1;
extern int count2;

int main() 
{
	Stack_Node *L;
	ElemType e;
	int i; 
	L=Init_Link_Stack(); 
	L=pop(L);
	printf("\n\n");
	L=push(L,5);
	L=push(L,15);
	int m=40;
	int n=40;
	while(n)
	{
		L=push(L,n*2);
		n--; 
	}
	printf("��%d��Ԫ��ѹջ��Ľ����\n\n",count1);
	print_stack(L);
	printf("\n\n");
	for(i=1;i<=40;i++)
	{
		if(i<=m+2)
		    L=pop(L);
		else
		printf("��ջ�ѿգ�����ջ��Ԫ��ʧ�ܣ�\n\n");
	}
	printf("��ջ�е���������Ԫ��Ϊ\n\n");
	print_stack(L);
	return 0;
}
