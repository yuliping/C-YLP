#ifndef SEQUENTIALSTACK_H_ //�����ֹ����ظ�����ĺ��жϷ���
#define SEQUENTIALSTACK_H_ 


#define STACKOFSIZE     100    //ջ��ʼ�ռ��С 
#define STACKINCREMENT 10  // �洢�ռ�������� 
#define OK  1
#define ERROR 0

typedef int Status;      
typedef double ElemType;

typedef struct
{
	ElemType *bottom;      //ջ������ʱֵΪNULL 
	ElemType *top;         //ջ��ָ�� 
	int stacksize;
 }SqStack;
 
 int StackEmpty(SqStack *S);
 
 int GetTop(SqStack *S);
 
 Status Init_Stack(SqStack *S); //��ʼ��ջ
 
 Status StackTraverse(SqStack *S,Status(*visit)(ElemType)); 
 
 Status visit(ElemType c);
 
 Status push(SqStack *S,ElemType e);
 
 ElemType pop(SqStack *S);



#endif
