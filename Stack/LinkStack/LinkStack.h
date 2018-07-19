#ifndef LINKSTACK_H_ //�����ֹ����ظ�����ĺ��жϷ���
#define LINKSTACK_H_

typedef int Status;      
typedef int ElemType;

#define OK  1
#define ERROR 0

typedef struct Stack_Node
{
	ElemType data;
	struct Stack_Node *next;
}Stack_Node;



Stack_Node *Init_Link_Stack(); //��ʼ����ջ

Stack_Node *push(Stack_Node *top,ElemType e);  //ѹջ

Stack_Node *pop(Stack_Node *top);  //��ջ�е�Ԫ�ص���

void print_stack(Stack_Node *head); //��ջ��Ԫ����� 

#endif
