#ifndef EXPRESSIONEVALUATION_H_ //加入防止多次重复定义的宏判断符号
#define EXPRESSIONEVALUATION_H_

#include <stdio.h>
#include <stdlib.h>
#include "sequentialStack.h"

int isCorrectExpression(char *infixExpression);
int infixToPostfix(char *infixExpression, char postfixExpression[]);   //将中缀表达式转为后缀表达式 
int computeValueFromPostfix(char *postfixExpression, double *value);   //利用后缀表达式求值





#endif
