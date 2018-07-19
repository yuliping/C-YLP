#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"

int count = 0;

Status Init_Stack(SqStack *S)
{
	S->bottom=(ElemType *)malloc(STACKOFSIZE*sizeof(ElemType));
	if(!S->bottom)
	{
        printf("初始化栈时，存储空间分配失败！\n\n");
        return ERROR;
    }
    S->top=S->bottom;      //栈空时，栈顶和栈底指针相同
	S->stacksize=STACKOFSIZE;
	printf("初始化栈成功！\n\n");
	return OK;
}

Status StackTraverse(SqStack *S,Status(*visit)(ElemType))
{
	ElemType *b=S->bottom;
	ElemType *t=S->top;
	while(t>b)
	  visit(*b++);
	printf("\n");
	return OK;
}

Status visit(ElemType c)
{
	printf("%d\t",c);
	return OK;
}



Status push(SqStack *S,ElemType e)
{
	if(S->top-S->bottom >= S->stacksize-1)
	{		
		count++;
		printf("原存储空间%d不足，第%d次重新分配存储空间，当前存储空间为%d。", S->stacksize,count,S->stacksize+STACKINCREMENT); 
		printf("\n");
		S->bottom=(ElemType *)realloc(S->bottom,(S->stacksize+STACKINCREMENT)*sizeof(ElemType));    //栈满，增加存储空间 
		if(!S->bottom)
		{
			printf("\t初始化栈时，存储空间分配失败！\n\n");
			return ERROR;
		}
		S->top = S->bottom+S->stacksize-1;    //修改栈顶位置 
		S->stacksize+=STACKINCREMENT;     //修改栈的长度 
	}
	*S->top=e;
	S->top++;
	return OK;	
}


ElemType pop(SqStack *S)
{
	if(S->top==S->bottom)
	{
		printf("栈已空，弹出栈顶元素失败！\n\n");
		return ERROR;
	}
	S->top--;
	ElemType e=*(S->top);
	return e; 
}

