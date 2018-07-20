#include "expressionEvaluation.h"
#include <ctype.h>
#include <string.h>

int isCorrectExpression(char *infixExpression)
{
	
	int flag = 1;                      //һ������Ա������������ƥ�����Կ��� ѭ�������ؽ��
	int flag1 = 1; 
	int i,t,j;
	int index;
	index=0;
	SqStack S;                         //����һ��ջ�����ڴ������ 
	Init_Stack(&S);
	char ch,e;	
	int infixExpressionLength;
	//����ȥ�����ʽ�Ŀո�
	infixExpressionLength = strlen(infixExpression);
	
	char median[infixExpressionLength];  //���ڴ�ű��ʽ�г��ո����������е��ַ�
	memset(median,'\0',infixExpressionLength);
	for (i = 0, j = 0; infixExpression[i] != '\0' ;i++) 
	{
		if (isspace(infixExpression[i]))
		{
			if (isdigit(infixExpression[i-1]) && isdigit(infixExpression[i+1]))
			{
				printf("This expression is an illgeal expression(Error: digit+ space + digit)��\n\n");
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
	median[j]='\0';    //�м����ַ�����β���� ��������ܻ������������ʽ�޹صĶ��� 

		
	memset(infixExpression,'\0',infixExpressionLength);    //�����ո�� infixExpression��� 
	for (t = 0; median[t] != '\0'; t++)
	{
		infixExpression[t] = median[t];                //����ȥ�ո�� medianתΪ infixExpression
	 }
	 infixExpression[t] = '\0';
	//����ȥ���ո�
		
	 
	ch=infixExpression[index];
	index++;
	
	if('\0' == ch)
	{
		printf("This expression is an empty expression��\n\n");     //�ж��Ƿ�Ϊ�ձ��ʽ 
		return -1;
	 } 
	 
	while (ch != '\0')
	{
		if (isdigit(ch) || '('==ch || ')'==ch || '+'==ch || '-'==ch || '*'==ch || '/'==ch )   //���ȹ��˵��Ƿ��ַ���eg: a��b��Ӣ����ĸ 
		{
			//�����������Ƿ�ƥ�� 
			if ('('==ch )
			{
				push(&S,ch);
			}
			if (')'==ch )
			{
				if(!StackEmpty(&S) &&  '('== GetTop(&S))                      //���ջ��Ϊ�ղ��ҵ�ǰջ��Ԫ��Ϊ"(" 
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
				if (1==index)            //��һλΪ������ı��ʽ�ǲ���ȷ�� 
				{
					printf("This expression is an illgeal expression(Error: The first one is the operator)��\n\n");
					return -1;
				}
				else
				{
					//����������ǰһλ�ͺ�һλ��Ϊ���֣�����ʽ������ȷ������֮���д������ַ�Ϊ���֣�һ������� + �����  ��������� + �ַ���������'\0' 
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
	//�����жϱ��ʽ������ָ���������� 
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




int infixToPostfix(char *infixExpression, char postfixExpression[])  //����׺���ʽתΪ��׺���ʽ 
{
	if (1 == isCorrectExpression(infixExpression))
	{
		SqStack S;                         //����һ��ջ�����ڴ�Ų����� 
	char ch,e,m;
	Init_Stack(&S);
	int i=0;
	int j=0;
	ch=infixExpression[i];
	i++;
	 
	while(ch != '\0')                  //����ɨ�� infixExpression�б��ʽ��ÿ���ַ� 
	{
		switch(ch)
		{
			case '(' :                 //����(������ѹջ 
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
					  	 pop(&S);     //��(���� 
					  break;
		    case '+' : 
		    case '-' :
		    	      while(!StackEmpty(&S) &&(m=GetTop(&S)) && m!= '(')  //�����ǰ����������ȼ�����ջ������������ȼ� ����ջ�������������������ǰ�����ѹջ
					  {
					  	e=pop(&S);
				      	postfixExpression[j++]=e;  	
					   } 
					  push(&S,ch);      //����ǰ�����ѹջ 
					  break;
			case '*' :
			case '/' :
			          while(!StackEmpty(&S) && (m=GetTop(&S)) && m== '/' || m== '*')  
					  //�����ǰ�����Ϊ  '*' ���� '/'���Ƚ�ͬ���������������Ȼ�󽫵�ǰ�����ѹջ 
					  {
					  	e=pop(&S);
				      	postfixExpression[j++]=e;  	
					   } 
					  push(&S,ch);      //����ǰ�����ѹջ 
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
 
 
 
int computeValueFromPostfix(char *postfixExpression, double *value)  ////���ú�׺���ʽ��ֵ
{
	SqStack S;                      //���������ջ 
	Init_Stack(&S);                 //��ʼ��������ջ 
	int i=0;
	double x,y;
	while (postfixExpression[i] != '\0')            //ɨ���׺���ʽ��ÿ���ַ� 
	{
		if (postfixExpression[i] != ' ' && isdigit(postfixExpression[i]))
		{
			*value=0.0;
			while (postfixExpression[i] != ' ' )
			{
				*value = 10* (*value) + postfixExpression[i++] - '0';
			}
			i++;
			push(&S,*value);         //���������������ֽ�ջ			
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
			printf("ջ�ѿ�\n"); 
			return -1;
		}
	}
	return 1;
}
