#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"

int main() 
{
	SqStack S;
	ElemType e,m;
	Init_Stack(&S);
	m=pop(&S);
	push(&S,8);push(&S,9);
	int n=100;
	while(n){
		push(&S,n+10);
		n--;
	}				
	printf("\n");
	StackTraverse(&S,visit);
	printf("823��ջ��");
	push(&S,823);
	printf("\n\n");
	StackTraverse(&S,visit);
	m=pop(&S);
	printf("��ջ��Ԫ���ǣ�%d\n\n",m);
	printf("��ջ��Ԫ�ص�����,ջ�����е�Ԫ�أ�\n\n");	
	StackTraverse(&S,visit);
	return 0;
}
