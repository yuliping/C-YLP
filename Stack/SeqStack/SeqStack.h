#ifndef SEQSTACK_H_
#define SEQSTACK_H_

#define STACKOFSIZE     6     //栈初始空间大小 
#define STACKINCREMENT 10  // 存储空间分配增量 
#define OK  1
#define ERROR 0

typedef int Status;      
typedef int ElemType;

typedef struct
{
	ElemType *bottom;      //栈不存在时值为NULL 
	ElemType *top;         //栈顶指针 
	int stacksize;
 }SqStack;
 
 Status Init_Stack(SqStack *S); //初始化栈
 
 Status StackTraverse(SqStack *S,Status(*visit)(ElemType)); 
 
 Status visit(ElemType c);
 
 Status push(SqStack *S,ElemType e);
 
 ElemType pop(SqStack *S);
 
  

#endif
