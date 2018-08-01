#include "expressionEvaluation.h"
#include <ctype.h>
#include <string.h>
//Written by Yu Liping
//Date:2018/7/30
int isCorrectExpression(char *infixExpression)
{
    int flag = 1;                      //һ������Ա������������ƥ�����Կ��� ѭ�������ؽ��
	int flag1 = 1;  
	int i,t,j,m,n,y,leadSpace,index = 0;
	SqStack S;                         //����һ���ַ���ջ�����ڴ������ 
	InitStack(&S);
	char ch,e, CurrElem;			
	char median[strlen(infixExpression)];  //���ڴ�ű��ʽ�г��ո����������е��ַ�
	memset(median,'\0',strlen(infixExpression));
	for(leadSpace = 0; isspace(infixExpression[leadSpace]); leadSpace++	);  //�ڽ��в���֮ǰ����������λ�Ŀո�������
	if(infixExpression[leadSpace]=='+'||infixExpression[leadSpace]=='-')    //���������һԪ������������λ 
    {
   		if(isspace(infixExpression[leadSpace+1])) 
		{
			printf("A space follows a unary plus. \n");
			return -1;
		}
    }
    for(t = leadSpace; infixExpression[t] != '\0'; t++)
    {
    		if('-' == infixExpression[t] || '+' == infixExpression[t])
    		{
    			
    			for(n = t-1; isspace(infixExpression[n]); n--	);
    			if(('(' == infixExpression[n]) && (isspace(infixExpression[t+1])))
    			{
    				printf("A space follows a unary plus. \n");
			        return -1;
				}
			}
	}
    
    for(m = leadSpace, y = leadSpace;infixExpression[y] != '\0' ;y++) 
    {	   
	   if( (!isspace(infixExpression[y])) && (y != 0))   //�����ո�֮�� m �� y ͬʱ�ߣ�һ�������ո� m ֹͣǰ�� ,��Ȼ��ȥ��λ�ǿո����� 
	   {
		   m++;
	   }
	   else
	   {
		  ;
	   }
	   if( (y != 0) && (isspace(infixExpression[y])) && (!isspace(infixExpression[y+1]) ) )   
	   {
		   if((isdigit(infixExpression[y+1])) && (isdigit(infixExpression[m-1])) )
		   {
			  printf("Too many operands. \n");
		      return -1;
	       }
	 	  else
		  {
			  m = y;     
		  }		
	   }
    }
   
	for (i = 0, j = 0; infixExpression[i] != '\0' ;i++) 
	{
		if (isspace(infixExpression[i]))
		{
			;
		}
		else
		{
			median[j]=infixExpression[i];
			j++;
		}				
	}
	median[j]='\0';    //�м����ַ�����β���� ��������ܻ������������ʽ�޹صĶ��� 		
	memset(infixExpression,'\0',strlen(infixExpression));    //�����ո�� infixExpression��� 
	strcpy(infixExpression,median);
	ch=infixExpression[index++];
	if('\0' == ch)
	{
		printf("The input is EMPTY. \n");     //�ж��Ƿ�Ϊ�ձ��ʽ 
		return -1;
	 }  
	while (ch != '\0')
	{
		if (isdigit(ch) || '('==ch || ')'==ch || '+'==ch || '-'==ch || '*'==ch || '/'==ch )   //���ȹ��˵��Ƿ��ַ���eg: a��b��Ӣ����ĸ 
		{
			if ('('==ch )   //�����������Ƿ�ƥ�� 
			{
				Push(&S,ch);
			}
			if (')'==ch )
			{
				GetTop(&S, &CurrElem);
				if(!StackEmpty(&S) &&  '('== CurrElem)                      //���ջ��Ϊ�ղ��ҵ�ǰջ��Ԫ��Ϊ"(" 
				{
					Pop(&S, &e);   //eΪ��ǰջ��Ԫ�� 
					flag=1;
				}
				else 
				{
					flag=0;
				 } 
			}
			if (('+'==ch || '-'==ch || '*'==ch || '/'==ch ) )      
			{
				if ( ('+' == infixExpression[index]) || ('-' == infixExpression[index]) || ('*' == infixExpression[index]) || ('/' == infixExpression[index]) )            //��һλΪ����������ҵڶ�λҲΪ����� 
				{
					printf("Operator %c immediately follows another operator in the expression. \n", infixExpression[index]);
					return -1;
				}
				else
				{
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
			printf("This expression contains illegal characters: %c. \n\n", ch);
			return -1;
		}		
		ch=infixExpression[index++];
	} 
	if(1 == flag1)                            //��flag1 = 1���� �������������ƥ�� 
	{
		if((StackEmpty(&S)) && (1 == flag) )  //�������ջΪ�ղ���flag = 1 ��������ƥ��ɹ� 
		{
			return 1;
		}
		else
		if ((StackEmpty(&S)) && (0 == flag) )
		{
			printf("Wrong expression. No matched '(' before ')'. \n");
			return -1;
		 } 
		 else
		{
			printf("The brackets for this expression do not match. \n ");
		    return -1;
		}	
	}
	else
	{
		printf("Some operator without operand in the expression. \n");
		return -1;
	}
	return 1; 
} 

int infixToPostfix(char *infixExpression, char postfixExpression[])  //����׺���ʽתΪ��׺���ʽ 
{
	if (1 == isCorrectExpression(infixExpression))
	{
		SqStack S;             //����һ���ַ���ջ�����ڴ�Ų�����
		InitStack(&S);         //��ʼ��ջ
		char ch;
		ElemType e,m;
		int i=0;
		int j=0;
		ch=infixExpression[i++];
		while(ch != '\0')                  //����ɨ�� infixExpression�б��ʽ��ÿ���ַ� 
		{
			switch(ch)
			{					
				case '(' :
						   if(!Push(&S,ch))    return -1;
						    break;
				case ')' :
					       if(GetTop(&S, &m))    // m Ϊ��ǰջ��Ԫ�� 
					       {
					       	    while(!StackEmpty(&S))  //�� m ���Ƿǿ�Ԫ��ʱ������û������ '(' ʱ��������Ԫ�ص����� 
					            {
					       	        while(m != '(') 
					       	        {
					       	            if( !Pop(&S,&e))   return -1;//����ǰջ��Ԫ��  e ������ 
					       	            	postfixExpression[j++]=e; 
					       	    	        if( !GetTop(&S, &m))
								            {
									            printf("This stack is empty. \n");
								                return -1;
								            }
							        }
								   break;							    
						       }
						   }
						   else
						   {
						   	    printf("This stack is empty. \n");
								return -1;
						   }
					  	    if(!Pop(&S,&e))  return -1;
					        break;					
				case '+' :
						   if( 0 == i - 1 )    // i - 1����ǰ������ֵ 
					       {
						        if( !Push(&S, '@' ))     return -1;	   	  	
						   }
						   else
						   if( ('(' == infixExpression[i-2]) && isdigit(infixExpression[i]))   //��� '+'�ĺ��������֣�����ǰ�治�����֣��ʹ�������һԪ����� 
						   {
						   	    if( !Push(&S, '@' ))     return -1;
						   }
						   else
						   {
								 GetTop(&S, &m);
						        while(0 == StackEmpty(&S)&& m!= '(')  //�����ǰ����������ȼ�����ջ������������ȼ� ����ջ�������������������ǰ�����ѹջ
						       {
						   	        if(!Pop(&S,&e))  return -1;
				      	            postfixExpression[j++]=e;
				      	            GetTop(&S, &m);
						       }
						        if( !Push(&S,ch))     return -1; //����ǰ�����ѹջ 		    				           
						   }
						   break;						    						   					
				case '-' :
						   if( 0 == i - 1 )
					       {
						      if( !Push(&S, '$' ))  return -1;    //����ջ������ô�죿   	  	
						   }
						   else
						   if( ('(' == infixExpression[i-2]) && isdigit(infixExpression[i]))   //��� '+'�ĺ��������֣�����ǰ�治�����֣��ʹ�������һԪ����� 
						   {
						   	    if( !Push(&S, '$' ))  return -1;
						   }
						   else
						   {
						   	    GetTop(&S, &m);
						        while(!StackEmpty(&S) && m!= '(')  //�����ǰ����������ȼ�����ջ������������ȼ� ����ջ�������������������ǰ�����ѹջ
						        {
						   	        if(!Pop(&S,&e))  return -1;
				      	            postfixExpression[j++]=e;
				      	            GetTop(&S, &m);
						        }
						        if(!Push(&S,ch) )   return -1;  //����ǰ�����ѹջ     
						   }
						   break;
				case '*' :					
				case '/' :
					       GetTop(&S, &m);
						  while(!StackEmpty(&S)  && (m == '/' || m == '*' || m == '$' || m == '@'))  
					      {
					      	 if(!Pop(&S,&e))  return -1;
				      	     postfixExpression[j++]=e;
				      	     GetTop(&S, &m);
						  }	
					      if(!Push(&S,ch) )   return -1;      //����ǰ�����ѹջ 
					      break; 
				default :
					      while (isdigit(ch))	
					      {
					      	postfixExpression[j++]=ch; 
		    	            ch = infixExpression[i++];
						  }
						  i--;
						  postfixExpression[j++]=' ';		 //Ϊ���������������֣�������������֮��ӷ��� # 
			}
			ch = infixExpression[i++];
		}
		while(!StackEmpty(&S))
		{
			if(!Pop(&S,&e))  return -1;
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
	SqStack1 S;                      //���������ջ 
	InitStack1(&S);                 //��ʼ��������ջ 
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
			if( !Push1(&S,*value))    return -1;        //���������������ֽ�ջ			
		}
		else
		{
			switch(postfixExpression[i])
			{
				case '+':
					     if(!Pop1(&S, &x))    return -1;
					     if(!Pop1(&S, &y))    return -1;
					     y = x + y;
					     if(!Push1(&S, y))    return -1;
					     break;
				case '-' :
					     if(!Pop1(&S, &x))    return -1;
					     if(!Pop1(&S, &y))    return -1;
					     y = y - x;
					     if(!Push1(&S, y))    return -1;
					     break;
				case '*' :
					     if(!Pop1(&S, &x))    return -1;
					     if(!Pop1(&S, &y))    return -1;
					     y = x * y;
					     if(!Push1(&S, y))    return -1;
					     break;
				case '/' :
					     if(!Pop1(&S, &x))    return -1;
					     if(!Pop1(&S, &y))    return -1;
					     if( x != 0.0)
					     {
					     	y = y / x;
						 }
					     else
					     {
					     	printf("error: zero divisor.\n");
					     	return -1;
						 }
					     if(!Push1(&S, y))    return -1;
					     break;
				case '$' :
					     if(!Pop1(&S, &x))    return -1;
					     y = -x ;
					     if(!Push1(&S, y))    return -1;
					     break;					
				case '@' :
					     if(!Pop1(&S, &x))    return -1;
					     y = x ;
					     if(!Push1(&S, y))    return -1;
					     break;
			}
			i++;
		 } 
	}
	if (!StackEmpty1(&S))
	{
		if(!Pop1(&S, value))    return -1;
		if (StackEmpty1(&S))
		{
			return 1;
		}
		else
		{
			printf("This stack is empty. \n"); 
			return -1;
		}
	}
	return 1;
}
