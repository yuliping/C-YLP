#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"

int count = 0;

Status Init_Stack(SqStack *S)
{
	S->bottom=(ElemType *)malloc(STACKOFSIZE*sizeof(ElemType));
	if(!S->bottom)
	{
        printf("��ʼ��ջʱ���洢�ռ����ʧ�ܣ�\n\n");
        return ERROR;
    }
    S->top=S->bottom;      //ջ��ʱ��ջ����ջ��ָ����ͬ
	S->stacksize=STACKOFSIZE;
	printf("��ʼ��ջ�ɹ���\n\n");
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
		printf("ԭ�洢�ռ�%d���㣬��%d�����·���洢�ռ䣬��ǰ�洢�ռ�Ϊ%d��", S->stacksize,count,S->stacksize+STACKINCREMENT); 
		printf("\n");
		S->bottom=(ElemType *)realloc(S->bottom,(S->stacksize+STACKINCREMENT)*sizeof(ElemType));    //ջ�������Ӵ洢�ռ� 
		if(!S->bottom)
		{
			printf("\t��ʼ��ջʱ���洢�ռ����ʧ�ܣ�\n\n");
			return ERROR;
		}
		S->top = S->bottom+S->stacksize-1;    //�޸�ջ��λ�� 
		S->stacksize+=STACKINCREMENT;     //�޸�ջ�ĳ��� 
	}
	*S->top=e;
	S->top++;
	return OK;	
}


ElemType pop(SqStack *S)
{
	if(S->top==S->bottom)
	{
		printf("ջ�ѿգ�����ջ��Ԫ��ʧ�ܣ�\n\n");
		return ERROR;
	}
	S->top--;
	ElemType e=*(S->top);
	return e; 
}

