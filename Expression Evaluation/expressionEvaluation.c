#include "expressionEvaluation.h"
#include <ctype.h>

int infixToPostfix(char *infixExpression, char postfixExpression[])  //将中缀表达式转为后缀表达式 
{
	SqStack S;                         //定义一个栈，用于存放操作符 
	char ch,e,m;
	Init_Stack(&S);
	int i=0;
	int j=0;
	ch=infixExpression[i];
	i++;
	while(ch != '\0')                  //依次扫描 infixExpression中表达式的每个字符 
	{
		switch(ch)
		{
			case '(' :                 //遇到(，将其压栈 
				      push(&S,ch);
				      break;
			case ')' :
						m=GetTop(&S); 
						
						while(m){
							while(m!='('){
								e=pop(&S);
				      	 		postfixExpression[j++]=e; 
						 		m=GetTop(&S); 
								break;
							}
							if(m=='('){
								break;
							}
						}
						if(!m){
							return 0;
						}
					  	 pop(&S);     //将(弹出 
					  break;
		    case '+' : 
		    case '-' :
		    	      while(!StackEmpty(&S) &&(m=GetTop(&S)) && m!= '(')  //如果当前运算符的优先级低于栈顶运算符的优先级 ，则将栈顶运算符弹出，并将当前运算符压栈
					  {
					  	e=pop(&S);
				      	postfixExpression[j++]=e;  	
					   } 
					  push(&S,ch);      //将当前运算符压栈 
					  break;
			case '*' :
			case '/' :
			          while(!StackEmpty(&S) && (m=GetTop(&S)) && m== '/' || m== '*')  
					  //如果当前运算符为  '*' 或者 '/'，先将同级的运算符弹出，然后将当前运算符压栈 
					  {
					  	e=pop(&S);
				      	postfixExpression[j++]=e;  	
					   } 
					  push(&S,ch);      //将当前运算符压栈 
					  break;
		    case ' ':
		    	      break;
		    default :
			         while (isdigit(ch))	
					 {
					 	postfixExpression[j++]=ch; 
		    	        ch = infixExpression[i++];
					 	
					 }      		    
		    	      i--;
		    	      postfixExpression[j++]=' ';
		    	
		}
		ch = infixExpression[i++];		
	}	
	while(!StackEmpty(&S))
		{
			e=pop(&S);
			if(e == '(')
			{
				return 0;
			}
			postfixExpression[j++]=e;  	
		}
	postfixExpression[j] = '\0';
	return 1;
	
 } 
 
 
 
int computeValueFromPostfix(char *postfixExpression, double *value)  ////利用后缀表达式求值
{
	SqStack S;                      //定义操作数栈 
	Init_Stack(&S);                 //初始化操作数栈 
	int i=0;
	double x,y;
	while (postfixExpression[i] != '\0')            //扫描后缀表达式的每个字符 
	{
		if (postfixExpression[i] != ' ' && isdigit(postfixExpression[i]))
		{
			*value=0.0;
			while (postfixExpression[i] != ' ' )
			{
				*value = 10* (*value) + postfixExpression[i++] - '0';
			}
			i++;
			push(&S,*value);         //将经过处理后的数字进栈			
		}
		else
		{
			double *temp=(double*)malloc(sizeof(double));
			switch(postfixExpression[i])
			{
				case '+':
					     x = pop(&S);
					     *temp = pop(&S);
					     *temp = x + *temp;
					     push(&S, *temp);
					     break;
				case '-' :
					     x = pop(&S);
					     *temp = pop(&S);
					     *temp = *temp - x;
					     push(&S,*temp);
					     break;
				case '*' :
					     x = pop(&S);
					     *temp = pop(&S);
					     *temp = x * *temp;
					     push(&S,*temp);
					     break;
				case '/' :
					     x = pop(&S);
					     *temp = pop(&S);
					     *temp = *temp / x;
					     push(&S,*temp);
					     break;
			}
			i++;
		 } 
	}
	if (!StackEmpty(&S))
	{
		*value = pop(&S);
		if (StackEmpty(&S))
		{
			return 1;
		}
		else
		{
			printf("栈已空\n"); 
			return -1;
		}
	}
	return 1;
}
