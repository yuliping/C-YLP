
#include "sequentialStack.h"

//Written by Yu Liping
//Date:2018/7/30

/* Interfaces for the 1st stack for char elements*/

/*  Initialize the sequential stack
 */

//字符型栈 
void InitStack(SqStack *s)
{
	s->top = -1;
 } 


/*  Release the memory of the sequential stack
 */
void DestroyStack(SqStack *s)
{
	s->top = -1;
}


/*  Check if the stack is empty.
    Return 1 to indicate the stack is empty.
    Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty(SqStack *s)
{
	if( -1 == s->top)
	{
		return 1;      //返回 1 代表栈空 
		printf("This stack is empty, it has no value.\n");
	}
	else
	{
		return 0;     //返回 0 代表栈不空 
	}
}


/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push(SqStack *s, ElemType e)
{
	if( MaxSize - 1 == s->top )
	{
		printf("This stack is full.\n");
		return 0;    //返回 0 代表栈满，不能继续 push 
	}
	else
	{
		s->top++;
		s->data[s->top] = e;
		return 1;    //返回 1 代表栈未满，可以继续 push 
	}
}


/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop(SqStack *s, ElemType *e)
{
	if ( 1 == StackEmpty(s) )
	{
		printf("This stack is empty, it has no value.\n");
		return 0;	//返回 0 代表栈已空，不能继续 pop
	}
	else
	{
		*e = s->data[s->top];
		s->top--;
		return 1;   //返回 1 代表栈未空，可以继续 pop
	}
}


/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop(SqStack *s, ElemType *e)
{
	if( 1 == StackEmpty(s) )
	{
		//printf("This stack is empty, it has no value.&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
		return 0;	//返回 0 代表栈已空，没有栈顶元素 
	}
	else
	{
		*e = s->data[s->top];
		return 1;   //返回 1 代表栈未空，可以取栈顶元素 		
	}
}


void display(SqStack *s)
{
	if ( 1 == StackEmpty(s) )
	{
		printf("This stack is empty, it has no value.\n");
	}
	else
	{
		printf("%d", s->data[s->top]);
		s->top--;
		printf("\n");
	}
} 


/* Interfaces for the 2nd stack for double elements*/

/*  Initialize the sequential stack
 */
 
//操作数栈 
void InitStack1(SqStack1 *s)
{
	s->top = -1;
}


/*  Release the memory of the sequential stack
 */
void DestroyStack1(SqStack1 *s)
{
	s->top = -1;
}


/*  Check if the stack is empty.
 Return 1 to indicate the stack is empty.
 Return 0 to indicate the stack is NOT empty.
 */
int StackEmpty1(SqStack1 *s)
{
	if( -1 == s->top)
	{
		return 1;      //返回 1 代表栈空 
	}
	else
	{
		return 0;     //返回 0 代表栈不空 
	}
}


/*  If the stack is NOT full, push e into it and return 1 to indicate a successful push.
    If the stack is full, merely return 0 to indicate an unsuccessful push.
 */
int Push1(SqStack1 *s, ElemType1 e)
{
	if( MaxSize - 1 == s->top )
	{
		printf("This stack is full.\n");
		return 0;    //返回 0 代表栈满，不能继续 push 
	}
	else
	{
		s->top++;
		s->data[s->top] = e;
		return 1;    //返回 1 代表栈未满，可以继续 push 
	}
}


/*  If the stack is NOT empty, pop the top of the stack into e and return 1 to indicate a successful pop.
    If the stack is empty, merely return 0 to indicate an unsuccessful pop.
 */
int Pop1(SqStack1 *s,ElemType1 *e)
{
	if ( 1 == StackEmpty1(s) )
	{
		printf("This stack is empty.\n");
		return 0;	//返回 0 代表栈已空，不能继续 pop
	}
	else
	{
		*e = s->data[s->top];
		s->top--;
		return 1;   //返回 1 代表栈未空，可以继续 pop
	}
}


/*  If the stack is NOT empty, assign the top of the stack to e and return 1 to indicate a successful gettop.
    If the stack is empty, merely return 0 to indicate an unsuccessful gettop.
 */
int GetTop1(SqStack1 *s,ElemType1 *e)
{
	if( 1 == StackEmpty1(s) )
	{
		printf("This stack is empty.\n");
		return 0;	//返回 0 代表栈已空，没有栈顶元素 
	}
	else
	{
		*e = s->data[s->top];
		return 1;   //返回 1 代表栈未空，可以取栈顶元素 		
	}
}
