#ifndef EXPRESSIONEVALUATION_H_ //�����ֹ����ظ�����ĺ��жϷ���
#define EXPRESSIONEVALUATION_H_

#include <stdio.h>
#include <stdlib.h>
//#include "expressionEvaluation.h"
#include "sequentialStack.h"
int infixToPostfix(char *infixExpression, char postfixExpression[]);   //����׺���ʽתΪ��׺���ʽ 
int computeValueFromPostfix(char *postfixExpression, double *value);   //���ú�׺���ʽ��ֵ




#endif
