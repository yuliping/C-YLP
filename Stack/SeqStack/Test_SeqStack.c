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
	printf("823进栈后：");
	push(&S,823);
	printf("\n\n");
	StackTraverse(&S,visit);
	m=pop(&S);
	printf("出栈的元素是：%d\n\n",m);
	printf("将栈顶元素弹出后,栈中所有的元素：\n\n");	
	StackTraverse(&S,visit);
	return 0;
}
