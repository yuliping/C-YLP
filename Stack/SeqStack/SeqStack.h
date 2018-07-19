#ifndef SEQSTACK_H_
#define SEQSTACK_H_

#define STACKOFSIZE     6     //ջ��ʼ�ռ��С 
#define STACKINCREMENT 10  // �洢�ռ�������� 
#define OK  1
#define ERROR 0

typedef int Status;      
typedef int ElemType;

typedef struct
{
	ElemType *bottom;      //ջ������ʱֵΪNULL 
	ElemType *top;         //ջ��ָ�� 
	int stacksize;
 }SqStack;
 
 Status Init_Stack(SqStack *S); //��ʼ��ջ
 
 Status StackTraverse(SqStack *S,Status(*visit)(ElemType)); 
 
 Status visit(ElemType c);
 
 Status push(SqStack *S,ElemType e);
 
 ElemType pop(SqStack *S);
 
  

#endif
