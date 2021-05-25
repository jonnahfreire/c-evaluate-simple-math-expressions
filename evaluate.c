#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

Program to solve simple math expressions,
using the four basic operations.

Author: Jonas Freire

Github: jonnahfreire

*/


char *concat(char* str1, char* str2);
char* replaceResolvedExpression(char* exp, char* res, int operStartPos, int operEndPos);
int* getOperStartPos(int operpos, char* exp);
int* getOperEndPos(int operpos, char* exp);
void* setNumberElement(char* exp, char* n);
char* getResult(char* expression, char* oper, int operPos);
void* updateOperators(char* exp, int* oper[]);

int main() {
  char expression[100] = "";
  char operators[] = {'/','*','+','-'};
  
  printf("Calculate: ");
  scanf("%[.0123456789/*+-]s", expression);
  
  int div  [3] = {};
  int times[3] = {};
  int plus [3] = {};
  int minus[3] = {};
  int* opers[5] = {div, times, plus, minus};
  int i, e;

  updateOperators(expression, opers);

  void eval(int pos, char op){
      char res[100] = "";
      strcpy(res, getResult(expression, op, pos));

      // Copying new expression to expression
      strcpy(expression, replaceResolvedExpression(expression,
          res,
          getOperStartPos(pos, expression),
          getOperEndPos(pos, expression)));
      strcpy(res, "");

      updateOperators(expression, opers);
  }

  while((div[0]>0) || (times[0]>0)){
      while((div[0]>0) && ((div[1]<times[1]) && (div[1]>0) || (times[1] == 0))){
          eval(div[1], '/');
      }
      while((times[0]>0) && ((times[1]<div[1]) && (times[1]>0) || (div[1] == 0))){
          eval(times[1], '*');
      }
  }

  while((plus[0]>0) || (minus[0]>0)){
       while((plus[0]>0) && ((plus[1]<minus[1]) && (plus[1]>0) || (minus[1] == 0))){
          eval(plus[1], '+');
      }
      while((minus[0]>0) && ((minus[1]<plus[1]) && (minus[1]>0) || (plus[1] == 0))){
          eval(minus[1], '-');
      }
  }


  printf("Result: %s\n", (expression));
  system("pause");
  return 0;
 }


char *concat(char* str1, char* str2) {
  int len = strlen(str1) + strlen(str2);
  char st1[strlen(str1)]; strcpy(st1, str1);
  char st2[strlen(str2)]; strcpy(st2, str2);
  
  char *newstr = malloc(sizeof(char) * len);
  if(strlen(str2)>0) {
    strcpy(newstr, strcat(st1, st2));
    return newstr;
  }else{
    return str1;
  }
}


char* replaceResolvedExpression(char* exp, char* res, int operStartPos, int operEndPos){
    int i, e;
    char expLastPart[100]="";
    char newExp[100]="";
    char* newstr="";
    char opers[] = {'.',
    '0','1','2','3',
    '4','5','6','7','8',
    '9','/','*','+','-'};

    for(i = 0; i < strlen(exp); i++){
        for(e = 0; e < strlen(opers); e++){
             if(exp[i] == opers[e]){
                newExp[i] = exp[i];
             }
        }
    }

    //saving expression last part
    if(newExp[operEndPos+1] != '\0'){
        for(i = operEndPos+1; i < strlen(newExp); i++){
            for(e = 0; e < strlen(opers); e++){
                if(newExp[i] == opers[e]){
                    expLastPart[strlen(expLastPart)] = newExp[i];
                }
            }
        }
    }

    //clearing expression resolved
    if(newExp[operStartPos] != '\0'){
        for(i = operStartPos; i <= operEndPos; i++){
            newExp[i] = '\0';
        }
    }

    //adding resolved expression
    strcpy(newExp, concat(newExp, res));

    if(strlen(expLastPart) > 0) return concat(newExp, expLastPart);

    return concat(newExp, "");
}

int* getOperStartPos(int operpos, char* exp){
  int operStartPos, i;
  for(i = operpos-1; i >= 0; i--){
    if(exp[i] == '+'
       || exp[i] == '-'
       || exp[i] == '*'
       || exp[i] == '/'
       || exp[i] == '\0'
      ){
      break;
    }else{
      operStartPos = i;
    }
  }
  return operStartPos;
}

int* getOperEndPos(int operpos, char* exp){
  int operEndPos, i;
  for(i = operpos+1; i < strlen(exp); i++){
    if(exp[i] == '+'
       || exp[i] == '-'
       || exp[i] == '*'
       || exp[i] == '/'
       || exp[i] == '\0'
      ){
      break;
    }else{
      operEndPos = i;
    }
  }
  return operEndPos;
}

void* setNumberElement(char* exp, char* n){
    if(exp == '.')strcat(n, ".");
    if(exp == '0')strcat(n, "0");
    if(exp == '1')strcat(n, "1");
    if(exp == '2')strcat(n, "2");
    if(exp == '3')strcat(n, "3");
    if(exp == '4')strcat(n, "4");
    if(exp == '5')strcat(n, "5");
    if(exp == '6')strcat(n, "6");
    if(exp == '7')strcat(n, "7");
    if(exp == '8')strcat(n, "8");
    if(exp == '9')strcat(n, "9");
}

char* getResult(char* expression, char* oper, int operPos){
    int i;
    char num1[100]="";
    char num2[100]="";

    int n1StartPos = getOperStartPos(operPos, expression);
    int n2StartPos = operPos + 1;

    for(i = n1StartPos; i < n2StartPos-1; i++){
        setNumberElement(expression[i], num1);
    }

    for(i = n2StartPos; i < strlen(expression); i++){
        if(expression[i] == '+'
        || expression[i] == '-'
        || expression[i] == '*'
        || expression[i] == '/'
        || expression[i] == '\0'
        ){
            break;
        }else{
            setNumberElement(expression[i], num2);
        }
    }

    char* endPtr;
    float n1 = strtod(num1, &endPtr);
    float n2 = strtod(num2, &endPtr);
    float res;

    char stringRes[100];

    if(oper == '+') res = n1 + n2;
    if(oper == '-') res = n1 - n2;
    if(oper == '*') res = n1 * n2;
    if(oper == '/') res = n1 / n2;

    //Converting float to string
    sprintf(stringRes, "%.2f", res);

    if(stringRes[strlen(stringRes) - 3] == '.'){
        if(stringRes[strlen(stringRes) - 2] == '0' && stringRes[strlen(stringRes) - 1] == '0'){
            for( i = strlen(stringRes) - 3; i < strlen(stringRes); i++){
                stringRes[i] = '\0';
            }
        }
    }
    char* result = stringRes;
    return result;
}

void* updateOperators(char* exp, int* oper[]){
    int i, e;
    for(i = 0; i < strlen(exp); i++){
        char * source = exp;
        char * divPtr = strstr( source, "/" );
        char * timesPtr = strstr( source, "*" );
        char * plusPtr = strstr( source, "+" );
        char * minusPtr = strstr( source, "-" );
        char * opers[5] = {divPtr, timesPtr, plusPtr, minusPtr};
        for(e = 0; e < 4; e++){
            if (opers[e] != NULL){
              int index = opers[e] - source;

              if(e == 3) {
                if(index == 0){
                    oper[e][0] = 0;
                    oper[e][1] = 0;
                }else{
                    oper[e][0] = 1;
                    oper[e][1] = index;
                }
                break;
              }
              oper[e][0] = 1;
              oper[e][1] = index;
            }else{
                oper[e][0] = 0;
                oper[e][1] = 0;
            }
        }
    }
}
