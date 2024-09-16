#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char keywords[32][15] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"};

char mapper[10][20] = {"NIL", "Keyword", "Identifier", "Constant", "Operator", "Special character", "Space", "Semi-colon", "Bracket","Comma"};


int currentState = -1;

int len(char *str)
{
        int i = 0;
        for (; str[i]; i++)
                ;
        return i;
}

int isAlpha(char c)
{
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        {
                return 1;
        }
        return 0;
}

int isDigit(char c)
{
        if (c >= '0' && c <= '9')
        {
                return 1;
        }
        return 0;
}

int isOp(char c)
{
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>')
        {
                return 1;
        }
        return 0;
}

int isTrio(char c)
{
        if (c == '+' || c == '-' || c == '=')
        {
                return 1;
        }
        return 0;
}

int isKeyword(char *inputString, int start, int end)
{
        char buffer[100];
        int j = 0;
        for (int i = start; i <= end; i++)
        {
                buffer[j++] = inputString[i];
        }

        buffer[j] = '\0';

        for (int i = 0; i < 32; i++)
        {
                if (strcmp(keywords[i], buffer) == 0)
                {
                        return 1;
                }
        }
        return 0;
}
int isIdentifier(char *inputString, int start, int end)
{
        char buffer[100];
        int j = 0;
        for (int i = start; i <= end; i++)
        {
                buffer[j++] = inputString[i];
        }
        buffer[j] = '\0';

        if (!isAlpha(buffer[0]))
        {
                return 0;
        }
        for (int i = 1; i < len(buffer); i++)
        {
                if (!isAlpha(buffer[i]) && !isDigit(buffer[i]))
                {
                        return 0;
                }
        }
        return 1;
}
int isConstant(char *inputString, int start, int end)
{
        char buffer[100];
        int j = 0;
        for (int i = start; i <= end; i++)
        {
                buffer[j++] = inputString[i];
        }
        buffer[j] = '\0';

        for (int i = 0; i < len(buffer); i++)
        {
                if (!isDigit(buffer[i]))
                {
                        return 0;
                }
        }
        return 1;
}

int isOperator(char *inputString, int start, int end)
{
        if (start == end)
        {

                if (isOp(inputString[start]))
                {
                        return 1;
                }
                return 0;
        }
        else if (start + 1 == end)
        {
                if (isOp(inputString[start]) && inputString[start] == inputString[end])
                {
                        return 1;
                }
                else if (isOp(inputString[start]) && inputString[end] == '=')
                {
                        return 1;
                }
                return 0;
        }
        return 0;
}
int isBracket(char *inputString, int start, int end)
{
        if (start == end)
        {
                if (inputString[start] == '(' || inputString[start] == ')')
                {
                        return 1;
                }
        }
        return 0;
}

int returnState(char *inputString, int start, int end)
{
 	if (inputString[end] == ' ')
        {

                return 6;
        }
        else if (isKeyword(inputString, start, end))
        {
                return 1;
        }
        else if (isIdentifier(inputString, start, end))
        {
                return 2;
        }
        else if (isConstant(inputString, start, end))
        {
                return 3;
        }
        else if (isOperator(inputString, start, end))
        {
                return 4;
        }
        else if (start == end && inputString[start] == ';')
        {
                return 7;
        }
        else if(start==end && inputString[start]==','){
                return 9;
        }
        else if (isBracket(inputString, start, end))
        {
                return 8;
        }
        else
        {
                return 5;
        }
}
int stateDefn(char *inputString, int start, int end)
{
        int activeState = returnState(inputString, start, end);

        if (activeState != currentState)
        {
                return 0;
        }
        return 1;
}

char *getSubString(char *inputString, int start, int end, char *buffer)
{

        int j = 0;
        for (int i = start; i <= end; i++)
        {
                buffer[j++] = inputString[i];
        }
        return buffer;
}
void clean(char *buffer)
{
        for (int i = 0; buffer[i]; i++)
        {
                buffer[i] = '\0';
        }
}

void parseFunc(char *inputString)
{
        int start = 0, end = 0,semicolonCount=0,keyCount=0;
        char buffer[100];

        for(int i=0;i<len(inputString);i++){
                if(inputString[i]==';'){
                        semicolonCount++;
                }
        }
	while (end < len(inputString))
        {
                clean(buffer);
                if (currentState == -1)
                {
                        currentState = returnState(inputString, start, end);
                        end++;
                        continue;
                }

                else if (!stateDefn(inputString, start, end) && returnState(inputString, start, end) == 1)
                {
                        getSubString(inputString, start, end, buffer);
                        int activeState = returnState(inputString, start, end);
                        keyCount++;
                        if(semicolonCount==0){
                                printf("Invalid statement : Missing Semicolon\n");
                                return;
                        }
                        printf("The section : %s is %s \n", buffer, mapper[activeState]);
                        end++;
                        start = end;
                        currentState = -1;
                }
                else if (!stateDefn(inputString, start, end))
                {
                        getSubString(inputString, start, end - 1, buffer);
                        if(currentState==7){
                                semicolonCount++;
                        }
                        if (!(currentState == 6 || currentState == 5))
                        {
                                printf("The section : %s is %s \n", buffer, mapper[currentState]);
                        }
                        start = end;
                        currentState = -1;
                }
                else
                {
                        currentState = returnState(inputString, start, end);
 			end++;
                }
        }
        if (start < end)
        {
                if(currentState==7){
                        semicolonCount++;
                }
                getSubString(inputString, start, end, buffer);
                printf("The section : %s is %s \n", buffer, mapper[currentState]);
                currentState = -1;
        }
        if(keyCount>=1 && semicolonCount==0){
                printf("Invalid statement :  Missing semicolon\n");
        }
}

void trimNewline(char *str)
{
        int len = strlen(str);

        while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r'))
        {
                str[len - 1] = '\0';
                len--;
        }
}

int main()
{
        char inputString[100];
        int flag = 1, i = 1;
        do
        {
                printf("Enter an input string to parse through : ");
                fgets(inputString, sizeof(inputString), stdin);
                trimNewline(inputString);
                printf("%s\n", inputString);
                parseFunc(inputString);
                printf("Enter 1 to continue 0 to stop : ");
                //getchar();
		scanf("%d", &flag);
                getchar();
                i++;
        } while (flag);
}
