#include "expressionEvaluation.h"
#include <ctype.h>

int infixToPostfix(char *infixExpression, char postfixExpression[])  //����׺���ʽתΪ��׺���ʽ 
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
