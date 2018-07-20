#include "expressionEvaluation.h"
#include <ctype.h>
#include <string.h>

int isCorrectExpression(char *infixExpression)
{
	
	int flag = 1;                      //一个标记性变量，用来标记匹配结果以控制 循环及返回结果
	int flag1 = 1; 
	int i,t,j;
	int index;
	index=0;
	SqStack S;                         //定义一个栈，用于存放括号 
	Init_Stack(&S);
	char ch,e;	
	int infixExpressionLength;
	//首先去除表达式的空格
	infixExpressionLength = strlen(infixExpression);
	
	char median[infixExpressionLength];  //用于存放表达式中除空格外其他所有的字符
	memset(median,'\0',infixExpressionLength);
	for (i = 0, j = 0; infixExpression[i] != '\0' ;i++) 
	{
		if (isspace(infixExpression[i]))
		{
			if (isdigit(infixExpression[i-1]) && isdigit(infixExpression[i+1]))
			{
				printf("This expression is an illgeal expression(Error: digit+ space + digit)！\n\n");
			    return -1;
			}
			else
			{
				;
			}
		}
		else
		{
			median[j]=infixExpression[i];
			j++;
		}
		
	}
	median[j]='\0';    //切记有字符串结尾符号 ，否则可能会输出其他与表达式无关的东西 

		
	memset(infixExpression,'\0',infixExpressionLength);    //将带空格的 infixExpression清空 
	for (t = 0; median[t] != '\0'; t++)
	{
		infixExpression[t] = median[t];                //将除去空格的 median转为 infixExpression
	 }
	 infixExpression[t] = '\0';
	//以上去除空格
		
	 
	ch=infixExpression[index];
	index++;
	
	if('\0' == ch)
	{
		printf("This expression is an empty expression！\n\n");     //判断是否为空表达式 
		return -1;
	 } 
	 
	while (ch != '\0')
	{
		if (isdigit(ch) || '('==ch || ')'==ch || '+'==ch || '-'==ch || '*'==ch || '/'==ch )   //首先过滤掉非法字符，eg: a、b等英文字母 
		{
			//下面检查括号是否匹配 
			if ('('==ch )
			{
				push(&S,ch);
			}
			if (')'==ch )
			{
				if(!StackEmpty(&S) &&  '('== GetTop(&S))                      //如果栈不为空并且当前栈顶元素为"(" 
				{
					e=pop(&S);
					flag=1;
				}
				else 
				{
					flag=0;
				 } 
			}
			if (('+'==ch || '-'==ch || '*'==ch || '/'==ch ) )      
			{
				if (1==index)            //第一位为运算符的表达式是不正确的 
				{
					printf("This expression is an illgeal expression(Error: The first one is the operator)！\n\n");
					return -1;
				}
				else
				{
					//如果运算符的前一位和后一位均为数字，则表达式可能正确，否则之间判错，错误又分为两种：一，运算符 + 运算符  二，运算符 + 字符结束符号'\0' 
					if (infixExpression[index] == '+' || infixExpression[index] == '-' || infixExpression[index] == '*' || infixExpression[index] == '/' || infixExpression[index] == '\0')
					{
						flag1=0;
					}
					else
					{
						flag1=1;
					}
				}
			}
			
					
		}
		else
		{
			printf("This expression contains illegal characters!\n\n");
			return -1;
		}
		
		ch=infixExpression[index++];
	} 
	//下面判断表达式的正误并指出错在哪里 
	if(1 == flag1)
	{
		if((StackEmpty(&S)) && (1 == flag) )
		{
			return 1;
		}
		else
		if ((StackEmpty(&S)) && (0 == flag) )
		{
			printf("There are extra right parentheses!\n\n");
			return -1;
		 } 
		 else
		{
			printf("The brackets for this expression do not match!\n\n ");
		    return -1;
		}
	
	}
	else
	{
		printf("The numbers and operators of this expression do not match!\n\n");
		return -1;
	}
	
	
	return 1;
}




int infixToPostfix(char *infixExpression, char postfixExpression[])  //将中缀表达式转为后缀表达式 
{
	if (1 == isCorrectExpression(infixExpression))
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
						
						while(m)
						{
							while(m!='(')
							{
								e=pop(&S);
				      	 		postfixExpression[j++]=e; 
						 		m=GetTop(&S); 
								break;
							}
							if(m=='(')
							{
								break;
							}
						}
						if(!m)
						{
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
	}
	else 
	{
		return -1;
	}
	
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
