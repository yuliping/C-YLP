#include "expressionEvaluation.h"
#include <ctype.h>
#include <string.h>
//Written by Yu Liping
//Date:2018/7/30
int isCorrectExpression(char *infixExpression)
{
    int flag = 1;                      //一个标记性变量，用来标记匹配结果以控制 循环及返回结果
	int flag1 = 1;  
	int i,t,j,m,n,y,leadSpace,index = 0;
	SqStack S;                         //定义一个字符型栈，用于存放括号 
	InitStack(&S);
	char ch,e, CurrElem;			
	char median[strlen(infixExpression)];  //用于存放表达式中除空格外其他所有的字符
	memset(median,'\0',strlen(infixExpression));
	for(leadSpace = 0; isspace(infixExpression[leadSpace]); leadSpace++	);  //在进行操作之前，将居于首位的空格给处理掉
	if(infixExpression[leadSpace]=='+'||infixExpression[leadSpace]=='-')    //这种情况是一元操作符居于首位 
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
	   if( (!isspace(infixExpression[y])) && (y != 0))   //遇到空格之间 m 和 y 同时走，一旦遇到空格 m 停止前进 ,当然除去首位是空格的情况 
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
	median[j]='\0';    //切记有字符串结尾符号 ，否则可能会输出其他与表达式无关的东西 		
	memset(infixExpression,'\0',strlen(infixExpression));    //将带空格的 infixExpression清空 
	strcpy(infixExpression,median);
	ch=infixExpression[index++];
	if('\0' == ch)
	{
		printf("The input is EMPTY. \n");     //判断是否为空表达式 
		return -1;
	 }  
	while (ch != '\0')
	{
		if (isdigit(ch) || '('==ch || ')'==ch || '+'==ch || '-'==ch || '*'==ch || '/'==ch )   //首先过滤掉非法字符，eg: a、b等英文字母 
		{
			if ('('==ch )   //下面检查括号是否匹配 
			{
				Push(&S,ch);
			}
			if (')'==ch )
			{
				GetTop(&S, &CurrElem);
				if(!StackEmpty(&S) &&  '('== CurrElem)                      //如果栈不为空并且当前栈顶元素为"(" 
				{
					Pop(&S, &e);   //e为当前栈顶元素 
					flag=1;
				}
				else 
				{
					flag=0;
				 } 
			}
			if (('+'==ch || '-'==ch || '*'==ch || '/'==ch ) )      
			{
				if ( ('+' == infixExpression[index]) || ('-' == infixExpression[index]) || ('*' == infixExpression[index]) || ('/' == infixExpression[index]) )            //第一位为运算符，并且第二位也为运算符 
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
	if(1 == flag1)                            //若flag1 = 1代表 操作数和运算符匹配 
	{
		if((StackEmpty(&S)) && (1 == flag) )  //如果括号栈为空并且flag = 1 代表括号匹配成功 
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

int infixToPostfix(char *infixExpression, char postfixExpression[])  //将中缀表达式转为后缀表达式 
{
	if (1 == isCorrectExpression(infixExpression))
	{
		SqStack S;             //定义一个字符型栈，用于存放操作符
		InitStack(&S);         //初始化栈
		char ch;
		ElemType e,m;
		int i=0;
		int j=0;
		ch=infixExpression[i++];
		while(ch != '\0')                  //依次扫描 infixExpression中表达式的每个字符 
		{
			switch(ch)
			{					
				case '(' :
						   if(!Push(&S,ch))    return -1;
						    break;
				case ')' :
					       if(GetTop(&S, &m))    // m 为当前栈顶元素 
					       {
					       	    while(!StackEmpty(&S))  //当 m 不是非空元素时，并且没有遇到 '(' 时，把里面元素弹出来 
					            {
					       	        while(m != '(') 
					       	        {
					       	            if( !Pop(&S,&e))   return -1;//将当前栈顶元素  e 弹出来 
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
						   if( 0 == i - 1 )    // i - 1代表当前的索引值 
					       {
						        if( !Push(&S, '@' ))     return -1;	   	  	
						   }
						   else
						   if( ('(' == infixExpression[i-2]) && isdigit(infixExpression[i]))   //如果 '+'的后面是数字，但是前面不是数字，就代表它是一元运算符 
						   {
						   	    if( !Push(&S, '@' ))     return -1;
						   }
						   else
						   {
								 GetTop(&S, &m);
						        while(0 == StackEmpty(&S)&& m!= '(')  //如果当前运算符的优先级低于栈顶运算符的优先级 ，则将栈顶运算符弹出，并将当前运算符压栈
						       {
						   	        if(!Pop(&S,&e))  return -1;
				      	            postfixExpression[j++]=e;
				      	            GetTop(&S, &m);
						       }
						        if( !Push(&S,ch))     return -1; //将当前运算符压栈 		    				           
						   }
						   break;						    						   					
				case '-' :
						   if( 0 == i - 1 )
					       {
						      if( !Push(&S, '$' ))  return -1;    //考虑栈满了怎么办？   	  	
						   }
						   else
						   if( ('(' == infixExpression[i-2]) && isdigit(infixExpression[i]))   //如果 '+'的后面是数字，但是前面不是数字，就代表它是一元运算符 
						   {
						   	    if( !Push(&S, '$' ))  return -1;
						   }
						   else
						   {
						   	    GetTop(&S, &m);
						        while(!StackEmpty(&S) && m!= '(')  //如果当前运算符的优先级低于栈顶运算符的优先级 ，则将栈顶运算符弹出，并将当前运算符压栈
						        {
						   	        if(!Pop(&S,&e))  return -1;
				      	            postfixExpression[j++]=e;
				      	            GetTop(&S, &m);
						        }
						        if(!Push(&S,ch) )   return -1;  //将当前运算符压栈     
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
					      if(!Push(&S,ch) )   return -1;      //将当前运算符压栈 
					      break; 
				default :
					      while (isdigit(ch))	
					      {
					      	postfixExpression[j++]=ch; 
		    	            ch = infixExpression[i++];
						  }
						  i--;
						  postfixExpression[j++]=' ';		 //为了区别数字与数字，将数字与数字之间加符号 # 
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
 
int computeValueFromPostfix(char *postfixExpression, double *value)  ////利用后缀表达式求值
{
	SqStack1 S;                      //定义操作数栈 
	InitStack1(&S);                 //初始化操作数栈 
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
			if( !Push1(&S,*value))    return -1;        //将经过处理后的数字进栈			
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
