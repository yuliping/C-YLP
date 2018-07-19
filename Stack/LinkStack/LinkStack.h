#ifndef LINKSTACK_H_ //加入防止多次重复定义的宏判断符号
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



Stack_Node *Init_Link_Stack(); //初始化链栈

Stack_Node *push(Stack_Node *top,ElemType e);  //压栈

Stack_Node *pop(Stack_Node *top);  //将栈中的元素弹出

void print_stack(Stack_Node *head); //将栈中元素输出 

#endif
