#include "expressionEvaluation.h"
#include <ctype.h>      //isdigit and isspace 
#include <string.h>     //strlen
#include<limits.h>      //INT_MAX

int isCorrectExpression(char *infixExpression);
int isUnaryOperator(char *expression, char c, int index);
int infixToPostfix(char *infixExpression, char postfixExpression[])  
//This function is to convert the infix expression to a postfix expression.
{
	if (1 == isCorrectExpression(infixExpression))
	{
		SqStack S;       //Define a character stack for storing operators.
		InitStack(&S);         
		char ch;
		ElemType e,m;
		int i=0, j=0;
		ch=infixExpression[i++];
		while(ch != '\0')      //Scan each character of the expression in infixExpression in turn.
		{
			switch(ch)
			{					
				case '(' :
						   if(!Push(&S,ch))    return -1;
						    break;
				case ')' :
					       if(GetTop(&S, &m))    //m is the current top element of the stack 
					       {
					       	    while(!StackEmpty(&S))  
								/*m is not a non-empty element, and does not encounter '(', 
								pop up the elements in the stack.*/
					            {
					       	        while(m != '(') 
					       	        {
					       	            if( !Pop(&S,&e))   return -1;     //Pop the current top element e.
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
					  	    if(!Pop(&S,&e))  return -1;  // Pop the '('.
					        break;					
				case '+' :
						   if(isUnaryOperator(infixExpression, ch, i-1))  
						   //Determines whether '+' is a unary operator
						   {
						   	    if( !Push(&S, '@' ))     return -1;	
						   }
						   else
						   {
								 GetTop(&S, &m);
						        while(0 == StackEmpty(&S)&& m!= '(')  
								/*If the current operator has a lower priority than the top-of-stack operator, 
								the top-of-stack operator is popped and the current operator is pushed onto the stack.*/
						       {
						   	        if(!Pop(&S,&e))  return -1;
				      	            postfixExpression[j++]=e;
				      	            GetTop(&S, &m);
						       }
						        if( !Push(&S,ch))     return -1;  		    				           
						   }
						   break;						    						   					
				case '-' :
						   if(isUnaryOperator(infixExpression, ch, i-1))
						   //Determines whether '-' is a unary operator
						   {
						   	    if( !Push(&S, '$' ))  return -1;
						   }
						   else
						   {
						   	    GetTop(&S, &m);
						        while(!StackEmpty(&S) && m!= '(')  
								/*If the current operator has a lower priority than the top-of-stack operator, 
								the top-of-stack operator is popped and the current operator is pushed onto the stack.*/
						        {
						   	        if(!Pop(&S,&e))  return -1;
				      	            postfixExpression[j++]=e;
				      	            GetTop(&S, &m);
						        }
						        if(!Push(&S,ch) )   return -1;      
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
					      if(!Push(&S,ch) )   return -1;      
					      break; 
				default :
					      while (isdigit(ch))
						  //It can output multiple digits	
					      {
					      	postfixExpression[j++]=ch; 
		    	            ch = infixExpression[i++];
						  }
						  i--;
						  postfixExpression[j++]='#';	//Add a space between the number and the number.
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
 
int computeValueFromPostfix(char *postfixExpression, double *value)  
//Use the suffix expression to find the value of the expression
{
	SqStack1 S;     //Defining an operand stack 
	InitStack1(&S); // Initialize the operand stack              
	int i=0;
	double x,y;
	while (postfixExpression[i] != '\0')    //Scan each character of the suffix expression 
	{
		if (postfixExpression[i] != ' ' && isdigit(postfixExpression[i]))
		{
			*value=0.0;
			while (postfixExpression[i] != '#' )
			{
				*value = 10* (*value) + postfixExpression[i++] - '0';
			}
			i++;
			if( !Push1(&S,*value))    return -1;        //Push the processed digits onto the stack			
		}
		else
		{
			switch(postfixExpression[i])
			{
				case '+': 
				//If the binary operator '+' is encountered, two elements are popped from the operand stack
					     if(!Pop1(&S, &x))    
						 {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     if(!Pop1(&S, &y))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     y = x + y;
					     if(!Push1(&S, y))    return -1;
					     break;
				case '-' : 
				//If the binary operator '-' is encountered, two elements are popped from the operand stack
					     if(!Pop1(&S, &x))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     if(!Pop1(&S, &y))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     y = y - x;
					     if(!Push1(&S, y))    return -1;
					     break;
				case '*' :
				//If the binary operator '*' is encountered, two elements are popped from the operand stack
					     if(!Pop1(&S, &x))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     if(!Pop1(&S, &y))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     y = x * y;
					     if(!Push1(&S, y))    return -1;
					     break;
				case '/' :
				//If the binary operator '/' is encountered, two elements are popped from the operand stack
					     if(!Pop1(&S, &x))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     if(!Pop1(&S, &y))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     if( x != 0.0)
					     {
					     	y = y / x;
						 }
					     else
					     {
					     	printf("Wrong expression!! Zero divisor. \n");
					     	return -1;
						 }
					     if(!Push1(&S, y))    return -1;
					     break;
				case '$' :
				//If the unary operator '$' is encountered, an element are popped from the operand stack
					     if(!Pop1(&S, &x))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
					     y = -x ;
					     if(!Push1(&S, y))    return -1;
					     break;					
				case '@' :
				//If the unary operator '@' is encountered, an element are popped from the operand stack
					     if(!Pop1(&S, &x))
					     {
						 	printf("An operator is missing. \n ");
							return -1;
						 }
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

int isUnaryOperator(char *expression, char c, int index)  
/*Determine whether the character '+' or '-' at the ith position of 
the expression is a unary operator or a binary.*/
{
	if(('+' == c) || ('-' == c)) 
	{
		if((0 == index) || (('(' == expression[index-1]) && isdigit(expression[index+1])) 
		|| ('(' == expression[index-1] && '(' == expression[index+1] )) //eg:  + , (-4) , (-(+5))  + or - is unary. 
	   {
		    return 1;
	   } 
	}
	return 0;
}

int clearFirstSpace(char *expression, int *leadSpace)     
//This function is to remove the first space
{
	for( *leadSpace = 0; isspace(expression[ *leadSpace]); (*leadSpace)++);
	return 0;
}

int removeExpressionSpace(char *expression, char *expressionOfRemovingSpace) 
//Remove Spaces from the expression
{	
	int i,j;
	int leadSpace;
	clearFirstSpace(expression, &leadSpace);
	for (i = leadSpace, j = 0; expression[i] != '\0'; i++)
	{
		if (!isspace(expression[i]))
		{
			expressionOfRemovingSpace[j] = expression[i];
			j++;
		}
	}
	expressionOfRemovingSpace[j] = '\0';	
	return 0;
}

int isLegalOperator(char c)
//Determines if the operator is valid
{
	if('+' == c || '-' == c || '*' == c || '/' == c)
	{
		return 1;
	}
	return 0;
}

int isLegalCharacter(char c) 
//Determine if it is a legitimate input
{
    if ( isdigit(c)|| isspace(c)|| isLegalOperator(c)|| '(' == c || ')' == c) 
	{
        return 1;
    }
    return 0;
}

int isCorrectExpression(char *infixExpression)
/* Determine if the input expression is legal
 1.First filter out illegal characters. eg: English alphabet
 2.If the current character is an operator
   (1)Unary operator '+' or '-'
     Possible error type:
         ¢ÙA space follows '+' or '-'.
         ¢Ú'+' or '-' is at the end of the expression.
         ¢Û')' follows '+' or '-'.        
   (2)Binary operator '+', '-', '*', '/'
     Possible error type: 
         ¢Ù'+', '-', '*'or '/' is at the top of the expression.
         ¢Ú'+', '-', '*'or '/' is at the end of the expression.
         ¢Û'+', '-', '*'or '/' follows '+', '-', '*'or '/'.
         ¢Ü')' follows '+', '-', '*'or '/'.
3.If the current character is an digit
      Possible error type: 
         ¢ÙThere are Spaces between Numbers.
         ¢Ú'(' follows digits.
4.If the current character is '('
      Possible error type:
         ¢ÙBinary operator '*' or '/' follows '('.
         ¢Ú')'  follows '('. 
5.If the current character is ')'
      Possible error type:
         ¢Ù'('  follows ')'
         ¢ÚThe stack of braces is empty, it represents the stack have not the '('.
		 ¢ÛDigit follows ')'. 
6.The stack of braces is not empty
      Possible error type:
         ¢ÙMissing '(' in expression.     
*/
{
	int t, m, n, y, leadSpace, index = 0;
	clearFirstSpace(infixExpression, &leadSpace);
	char ch,e, CurrElem;
	int COUNT = INT_MAX;
	char expressionOfRemovingSpace[100];
	char errorRecord[100];
	SqStack S;                         //Define a character stack for storing braces.
	InitStack(&S);
	if('\0' == infixExpression[leadSpace])
	{
		printf("Wrong expression!! No operands in the expression! \n");     
		return -1;
	}
	if((infixExpression[leadSpace]=='+') && (isspace(infixExpression[leadSpace+1])))  
	//The unary operator is at the top of the expression if it ignores spaces.
	{
		if(leadSpace < COUNT)  
		{
			COUNT = leadSpace; 
			sprintf(errorRecord,"Wrong expression!! A space follows a unary plus. ");
		}
	} 
	if((isspace(infixExpression[leadSpace+1])) && ('-' == infixExpression[leadSpace])) 
	//The unary operator is at the top of the expression if it ignores spaces.
	{
		if(leadSpace < COUNT)  
		{
			COUNT = leadSpace;
			sprintf(errorRecord,"Wrong expression!!A space follows a unary minus.");
		}
	}
	for(t = leadSpace; infixExpression[t] != '\0'; t++)   
	//The unary operator is in the middle of the expression.
    {
    	if('-' == infixExpression[t] || '+' == infixExpression[t])
    	{		
    		for(n = t-1; isspace(infixExpression[n]); n--	);
    		if(('(' == infixExpression[n]) && (isspace(infixExpression[t+1])) && ('+' == infixExpression[t]))   //(   +  9)
    		{
			    if( (t+1) < COUNT)
				{
					COUNT = t+1;   
				    strcpy(errorRecord,"Wrong expression!!A space follows a unary plus.");
				}      
			}
			if(('(' == infixExpression[n]) && (isspace(infixExpression[t+1])) && ('-' == infixExpression[t]))   //(    - 7)
    		{
    			if(t < COUNT)
    			{
    				COUNT = t;
    				strcpy(errorRecord,"Wrong expression!!A space follows a unary minus.");
				}         
			}
		}
	}  
	for(m = leadSpace, y = leadSpace;infixExpression[y] != '\0' ;y++) 
	//Determine if there is a space between the operands.
	{
		if( !isspace(infixExpression[y]))     
	    {
		   m++;
	    }
	    if( (isspace(infixExpression[y])) && (!isspace(infixExpression[y+1]) ) )   
	    {
		   if((isdigit(infixExpression[y+1])) && (isdigit(infixExpression[m-1])) )   // eg: 8321  9432
		   {
			  if( (y+1) < COUNT) 
			  {
			  	COUNT = y+1;    
			  	sprintf(errorRecord, "Wrong expression!! No operator between two operands. ");
			  }
	       }
	 	   else
		   {
			  m = y;     
		   }		
	    }
	}
	removeExpressionSpace(infixExpression, expressionOfRemovingSpace);
	memset(infixExpression,'\0',strlen(infixExpression));  
	strcpy(infixExpression, expressionOfRemovingSpace);
	ch = infixExpression[index++];
	while('\0' != ch)
	{
		if(!isLegalCharacter(ch))   
		//First filter out illegal characters. eg: English alphabet
		{
			if((index-1 >=0) && ((index- 1) < COUNT))     
			{
				 COUNT = index- 1;
				 sprintf(errorRecord,"Wrong expression!!Illegal character '%c' in the expression. \n", ch);
			}
		}
		if(isLegalOperator(ch))   
		//Determine if it is a legal operator
		{
			if('+' == ch || '-' == ch)
			{
				if('\0' == infixExpression[index]) 
				{
					if((index >=0) && (index < COUNT))
					{
						COUNT = index;   
					    sprintf(errorRecord,"Wrong expression!! No operand after the last '%c' in the expression. \n", ch);
					    break;
					}
				}
			}
			if('*' == ch || '/' == ch)
			{
				if((index - 1) == 0)
				{
					if((index >=0) && (index < COUNT))
					{
						COUNT = index;   // eg: *
					    sprintf(errorRecord,"Wrong expression!! No operand before the first '%c' in the expression.  \n", ch);
					    break;
					}
				}
				if('\0' == infixExpression[index]) 
				{
					if((index >=0) && (index < COUNT))
					{
						COUNT = index;   // eg: 9 *  
					    sprintf(errorRecord,"Wrong expression!! No operand after the last '%c' in the expression.  \n", ch);
					    break;
					}
				}
			}
			if(isLegalOperator(infixExpression[index])) //eg: +*         
			{
				if((index >=0) && (index < COUNT))     
				{
					 COUNT = index;
					 sprintf(errorRecord,"Wrong expression!!Operator '%c' immediately follows  '%c' in the expression. \n", infixExpression[index], ch);
					 break;
				}
			}
			if(')' == infixExpression[index])
			{
				if((index >=0) && (index < COUNT))       
				{
					COUNT = index;   //eg : *), +) 
					sprintf(errorRecord,"Wrong expression!!No operand between '%c' and '%c' in the expression. \n", ch, infixExpression[index]);
					break;
				}
			} 
			if(!isUnaryOperator(infixExpression, ch, index-1))  
			{
				if(0 == index-1)
				{
					if((index - 1 >=0) && ((index-1) < COUNT))     
					{
						 COUNT = index -1;
						 sprintf(errorRecord,"Wrong expression!!No operand before the first '%c' in the expression. \n", ch);
						 break;
					}
				}
			} 
		}
		if(isdigit(ch))   //eg:8()
		{
			while(isdigit(infixExpression[index])) index++;
			if('(' == infixExpression[index])
			{
				if((index >=0) && (index < COUNT)) 
				{
					COUNT = index;    
					sprintf(errorRecord,"Wrong expression!! No operator between a number and  '%c' in the expression. ",infixExpression[index]);
					break;
				}
			}	
		}
		if('(' == ch)  
		{
			if('*' == infixExpression[index] || '/' == infixExpression[index])   //(*9)
			{
				if((index >=0) && (index < COUNT))
				{
					COUNT = index;   //eg: (* 
					sprintf(errorRecord,"Wrong expression!! No operand between '%c' and '%c' in the expression. ",ch, infixExpression[index]);
					break;
				}
			}
			if(')' == infixExpression[index])  //eg:()
			{
				if((index >=0) && (index < COUNT))
				{
					COUNT = index;
					sprintf(errorRecord,"Wrong expression!! No operand between '%c' and '%c' in the expression. ", ch, infixExpression[index]);
					break;
				}
			}
			if(!Push(&S,ch))    return -1;    
		}
		if(')' == ch)
		{
			if(StackEmpty(&S))
			{
				if((index >=0) && (index < COUNT))
				{
					COUNT = index;
					sprintf(errorRecord,"Wrong expression!! No matched '(' before '%c' in the expression. \n",ch);
				}
				break;
			}
			if('(' == infixExpression[index])
			{
				if((index >=0) && (index < COUNT) && ((index - 1) != 0))
				{
					COUNT = index;
					sprintf(errorRecord,"Wrong expression!!No operator between '%c' and '%c' in the expression. \n ",ch, infixExpression[index]);
				}
				break;
			}
			
			GetTop(&S, &CurrElem);
			if(!StackEmpty(&S))                      
			{
				if(!Pop(&S, &e))   return -1;      
			}
			else
			{
				if((index - 1 >=0) && ((index-1) < COUNT))
				{
					COUNT = index -1;
					sprintf(errorRecord,"Wrong expression!!No matched '(' before '%c' in the expression. \n",ch);
				}   
				break;
			} 
			if(isdigit(infixExpression[index]))   //(+3)*9   
			{ 
				if((index >=0) && (index < COUNT))
				{
					COUNT = index;					
					sprintf(errorRecord,"Wrong expression!!No operator between '%c' and number in the expression. ",ch);
				}
				break;
			}
		}
		ch=infixExpression[index++];
	}
	if(!StackEmpty(&S)) 
	{
		if((index >=0) && (index < COUNT))
		{
			COUNT = index;
			sprintf(errorRecord,"Wrong expression!!No matched ')' after '(' in the expression. \n");
		}
	
	}
	if(COUNT < INT_MAX)  
	{
		printf("%s\n",errorRecord);
		return -1;
	}
	else
	{
		return 1;
	}			
	return 1;
}
