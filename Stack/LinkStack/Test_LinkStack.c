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
	printf("将%d个元素压栈后的结果：\n\n",count1);
	print_stack(L);
	printf("\n\n");
	for(i=1;i<=40;i++)
	{
		if(i<=m+2)
		    L=pop(L);
		else
		printf("链栈已空，弹出栈顶元素失败！\n\n");
	}
	printf("链栈中的最终所有元素为\n\n");
	print_stack(L);
	return 0;
}
