#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

/*

C program to solve simple math expressions

Author: Jonas Freire
Github: jonnahfreire

*/


char *concat(char* str1, char* str2);
char* replaceResolvedExpression(char* exp, char* res, int operStartPos, int operEndPos);
int getOperStartPos(int operpos, char* exp);
int getOperEndPos(int operpos, char* exp);
void setNumberElement(char exp, char* n);
char* getResult(char* expression, char oper, int operPos);
void updateOperators(char* exp, int* oper[]);
void sanitize(char* temp, char* expression);
void eval(int pos, char op);
void wait(int time);
void clear();


int main() {
    clear();

    char temp[100];
    char expression[strlen(temp)];
    int i;

    for(i=0;i<30;i++)printf("-");
	printf("\nCalcule: ");
	scanf("%[ 0-9.,/*+-]s", temp);

	sanitize(temp, expression);

    int div  [3] = {};
    int times[3] = {};
    int plus [3] = {};
    int minus[3] = {};

    int* opers[5] = {div, times, plus, minus};

    updateOperators(expression, opers);

    if((opers[0][0] == 0) &&
       (opers[1][0] == 0) &&
       (opers[2][0] == 0) &&
       (opers[3][0] == 0)){

        printf("Por favor insira pelo menos uma expressao!\n");
        fflush(stdin);
        wait(2000);
        main();
    }

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

    for(i=0;i<30;i++)printf("-");
    printf("\n%s = %s\n\n\n", temp, expression);

    char resp;
    printf("Novo calculo? S/N: ");
    fflush(stdin);
    scanf("%c", &resp);
    fflush(stdin);

    if((resp == 's') || (resp == 'S')){
        main();
    } else {
        printf("Saindo...\n\n");
        wait(2000);
    }
    return 0;
 }


char* replaceResolvedExpression(char* exp, char* res, int operStartPos, int operEndPos){
    int i, e;
    char expLastPart[100]="";
    char newExp[100]="";
    char opers[] = {
    '.','0','1','2','3',
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

char *concat(char* str1, char* str2) {
    // Inserts str2 at the end of str1
    int len = strlen(str1) + strlen(str2);
    char st1[strlen(str1)]; strcpy(st1, str1);
    char st2[strlen(str2)]; strcpy(st2, str2);

    char *newstr = (char*)calloc(len, sizeof(char));
    if(strlen(str2) > 0) {
        strcpy(newstr, strcat(st1, st2));
        return newstr;
    }
    free(newstr);
    return str1;
}

int getOperStartPos(int operpos, char* exp){
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

int getOperEndPos(int operpos, char* exp){
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

void setNumberElement(char exp, char* n){
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

char* getResult(char* expression, char oper, int operPos){
    char num1[strlen(expression)]; memset(num1, '\0', strlen(expression));
    char num2[strlen(expression)]; memset(num2, '\0', strlen(expression));
    int i;

    int n1StartPos = getOperStartPos(operPos, expression);
    int n2StartPos = operPos + 1;

    for(i = n1StartPos; i < n2StartPos-1; i++){
        setNumberElement(expression[i], num1);
    }

    for(i = n2StartPos; i < strlen(expression); i++){
        if((expression[i] == 47)
        || (expression[i] == 45)
        || (expression[i] == 43)
        || (expression[i] == 42)
        || (expression[i] == '\0')
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

    if(oper == 47) res = n1 / n2;
    if(oper == 42) res = n1 * n2;
    if(oper == 43) res = n1 + n2;
    if(oper == 45) res = n1 - n2;

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

void updateOperators(char* exp, int* oper[]){
    int i, e;
    for(i = 0; i < strlen(exp); i++){
        char * source = exp;
        char * divPtr = strstr(source, "/");
        char * timesPtr = strstr(source, "*");
        char * plusPtr = strstr(source, "+");
        char * minusPtr = strstr(source, "-");
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

void sanitize(char* temp, char* expression){
    int i;
    char t[strlen(temp)];
    memset(t, '\0', strlen(temp));

    //takeoff spaces
    for(i = 0; i < strlen(temp); i++)
        if(temp[i] != 32) t[strlen(t)] = temp[i];
        else if(temp[i] == '\0')break;

    //takeoff commas
    for(i = 0; i < strlen(t); i++)
    if(t[i] == ',') t[i] = '.';

    strcpy(expression, t);
}

void clear() {
    #ifdef _WIN32
	    system("cls");
	#else
        #if __linux__
            system("clear");
        #endif
    #endif
}


void wait(int time) {
    #ifdef _WIN32
	    Sleep(time);
	#else
        #if __linux__
            sleep(time);
        #endif
    #endif
}
