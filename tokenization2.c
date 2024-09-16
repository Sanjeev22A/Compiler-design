#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char keywords[32][10]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};

int isKeyword(char *str){
        for(int i=0;i<32;i++){
                if(strcmp(keywords[i],str)==0){
                        return 1;
                }

        }
        return 0;
}

int len(char *str){
        int i=0;
        while(str[i]){
                i++;
        }
        return i;
}

int isDigit(char c){
        if(c>='0' && c<='9'){
                return 1;
        }
        return 0;
}

int isConstant(char *str){
        for(int i=0;str[i];i++){
                if(!isDigit(str[i])){
                                return 0;
                }

        }
        return 1;
}
int isCharacter(char c){
        if(c>='a' && c<='z'){
                return 1;
        }
        if(c>='A' && c<='Z'){
                return 1;
        }
        if(c=='_'){
                return 1;
        }
        return 0;
}

int isIdentifier(char *str){
        if(len(str)>0 && isCharacter(str[0])){
                for(int i=0;i<str[i];i++){
                        if(!isDigit(str[i]) && !isCharacter(str[i])){
                                return 0;
                        }
                }
                return 1;
        }
        return 0;

}

int isDoubleEqual(char *str){
        if(strcmp(str,"==")==0 ){
                return 1;
        }
        return 0;
}

int isIncrement(char *str){
        if(strcmp(str,"++")==0 || strcmp(str,"--")==0){
                return 1;
        }
        return 0;
}
int isEqual(char *str){
        if(strcmp(str,"=")==0){
                return 1;
        }
        return 0;
}
int isArithmetic(char *str){
        if(strcmp(str,"+")==0 || strcmp(str,"-")==0 || strcmp(str,"*")==0 || strcmp(str,"/")==0 || strcmp(str,"%")==0){
                return 1;
        }
        return 0;
}

int isRelational(char *str){
        if(strcmp(str,"<")==0 || strcmp(str,">")==0 || strcmp(str,"<=")==0 || strcmp(str,">=")==0){
                return 1;
        }
        return 0;
}

void memoryWipe(char *buffer){
        for(int i=0;buffer[i];i++){
                buffer[i]='\0';
        }
}

int isStringLiteral(char *str){
        if(len(str) >1 && str[0]=='"' && str[len(str)-1]=='"'){
                return 1;
        }
        return 0;
}
int brackets(char *str){
        char brac[8][2]={"(",")","[","]","{","}"};
        for(int i=0;i<8;i++){
                if(strcmp(str,brac[i])==0){
                        return 1;
                }
        }
        return 0;
}

int isArrayRep(char *str){
        char brac[2][2]={"[","]"};
        char buffer1[100],buffer2[100];
        int i=0,j=0,k=0;
        for(i=0; str[i]&&str[i]!='[';i++){
                buffer1[j++]=str[i];

        }
        buffer1[j]='\0';
        if(str[i]!='['){
                return 0;

        }
        i++;
        for(;str[i]&&str[i]!=']';i++){
                buffer2[k++]=str[i];
        }
        buffer2[k]='\0';
        printf("buffer1 :%s\n",buffer1);
        printf("buffer2 :%s\n",buffer2);
        if(str[i]!=']'){
                return 0;
        }

        printf("%d\n",isConstant(buffer2));
        return isIdentifier(buffer1) && (isIdentifier(buffer2) || isConstant(buffer2));
}
void parser(char *inputString){
        char buffer[100];
        int j=0;
        memoryWipe(buffer);
        int encounteredQuote=0;
        for(int i=0;inputString[i];i++){
                if(!encounteredQuote && inputString[i]==' ' || inputString[i]==';'){
                        if(j==0){
                                j=0;
                                //memoryWipe(buffer);
                        }
                        else{
                             if(isStringLiteral(buffer)){
                                     printf("%s is string literal\n",buffer);
                             }
                             else if(isArrayRep(buffer)){
                                     printf("%s is an array representation\n",buffer);
                             }
                             else if(brackets(buffer)){
                                     printf("%s is a bracket\n",buffer);
                             }
                             else if(isKeyword(buffer)){
                                printf("%s is keyword\n",buffer);
                             }
                             else if(isConstant(buffer)){
                                 printf("%s is constant\n",buffer);
                             }
                             else if(isIdentifier(buffer)){
                                printf("%s is identifier\n",buffer);
                             }
                             else if(isEqual(buffer)){
                                     printf("%s is equal\n",buffer);
                             }
                             else if(isArithmetic(buffer)){
                                     printf("%s is arithmetic operator\n",buffer);
                             }
                             else if(isDoubleEqual(buffer)){
                                     printf("%s is checking operator\n",buffer);
                             }
                             else if(isRelational(buffer)){
 				printf("%s is relational operator\n",buffer);
                             }
                             else if(isIncrement(buffer)){
                                     printf("%s is incremental/decremental operator\n",buffer);
                             }
                             else{
                                     printf("%s is invalid character\n",buffer);
                             }
                             j=0;
                             memoryWipe(buffer);

                        }


                }
                else{
                        if(inputString[i]=='"'){
                                encounteredQuote++;
                                encounteredQuote%=2;
                        }
                        buffer[j++]=inputString[i];
                }

        }

}





int main(){
        int flag=0;
        char str[100];
        int i=0;
        do{
                printf("Enter a statement to parse  :  ");
                if(i!=0){
                        getchar();
                }
		memoryWipe(str);
                fgets(str,sizeof(str),stdin);
                printf("%s",str);

                //getchar();
                parser(str);
                printf("\n");
                printf("Enter 1 to continue 0 to exit  :  ");
                //
                //getchar();
                scanf("%d",&flag);
                //getchar();
                printf("\n");
                i++;
        }while(flag);

        return 0;
}
