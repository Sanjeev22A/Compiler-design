#include<stdio.h>
#include<stdlib.h>



int main(){
        char c;
        int flag=1;
        int switchbut=0;
        char control;
        char buffer;
        int i=0;
        do{
                printf("Enter an input:");
                fflush(stdin);
                if(i>0){
                        scanf("%c",&buffer);
                }
                scanf("%c",&c);
                fflush(stdout);
                if(c>='a' && c<='z'){
                                /*c=='a' || c=='b' || c=='c' || c=='d' || c=='e' || c=='f' || c=='g' || c=='h' || c=='i' || c=='j' || c=='k' || c=='l' || c=='m' || c=='n' || c=='o' || c=='p' || c=='q' || c=='r' || c=='s' || c=='t' || c=='u' || c=='v' || c=='w' || c=='x' || x=='y' || c=='z'){*/
                        switchbut=1;
                }
                else if( c>='A' && c<='Z'){
                                /*c=='A' || c=='B' || c=='C' || c=='D' || c=='E' || c=='F' || c=='H' || c=='I' || c=='J' || c=='K' || c=='L' || c=='M' || c=='N' || c=='O' || c=='P' || c=='Q' || c=='R' || c=='S' || c=='T' || c=='U' || c=='V' || c=='W' || c=='X' || x=='Y'  ||c=='Z'){*/
                        switchbut=2;
                }
                else if(c>='0' && c<='9'){
                        switchbut=3;
                }

                else if(c=='+' || c=='-' || c=='*' || c=='/' || c=='%'){
                        switchbut=5;
                }
                else if(c=='<' || c=='>' || c=='='){
                        switchbut=6;
                }
                else{
			switchbut=4;
                }

                switch(switchbut){
                        case 1:printf("Lowercase alphabet %c",c);break;
                        case 2:printf("Uppercase alphabet %c",c);break;
                        case 3:printf("digit %c",c);break;
                        case 4:printf("Special character :%c",c);break;
                        case 5:printf("Arithmetic character : %c",c);break;
                        case 6:printf("Relational character : %c",c);break;
                        default:printf("Invalid input");break;
                }
                printf("\n");
                fflush(stdin);
                printf("Enter Y to continue N to end:");
                scanf("%c",&control);
                scanf("%c",&control);

                if(control=='Y'){
                        flag=1;
                }
                else if(control=='N'){
                        flag=0;
                        break;
                }
                else{
                        printf("Invalid input loop ends\n");
                        break;
                }
                i++;
        }while(flag);
        return 0;
}
