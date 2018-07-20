#include <stdio.h>
#include <stdlib.h>
#include "sequentialStack.h"

int count = 0; 

int StackEmpty(SqStack *S)
{
	if (S->bottom == S->top)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


 int GetTop(SqStack *S)
 {
 	int e;
 	if(S->bottom == S->top)
 	{
 		printf("The stack is empty！\n");
 		return 0;
	 }
	 else
	 {
	 	e=*(S->top-1);
	 	return e;
	 }
 }
Status Init_Stack(SqStack *S)
{
	S->bottom=(ElemType *)malloc(STACKOFSIZE*sizeof(ElemType));
	if(!S->bottom)
	{
        return ERROR;
    }
    S->top=S->bottom;      //栈空时，栈顶和栈底指针相同
	S->stacksize=STACKOFSIZE;
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
		printf("The original storage space %d is insufficient, redistribute the storage space %d times, current storage space is %d。", S->stacksize,count,S->stacksize+STACKINCREMENT); 
		printf("\n");
		S->bottom=(ElemType *)realloc(S->bottom,(S->stacksize+STACKINCREMENT)*sizeof(ElemType));    //栈满，增加存储空间 
		if(!S->bottom)
		{
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
		return ERROR;
	}
	S->top--;
	ElemType e=*(S->top);
	return e; 
}

