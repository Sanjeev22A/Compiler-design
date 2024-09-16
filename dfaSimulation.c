#include<stdio.h>
#include<stdlib.h>

int transitions[100][100];

int in(int *array,int size,int val){
        for(int i=0;i<size;i++){
                if(array[i]==val){
                        return 1;
                }
        }
        return 0;
}

void initializeStateArray(int *stateArray,int noOfStates){
        for(int i=0;i<noOfStates;i++){
                stateArray[i]=i;
        }
}

void initializeTransitions(int noOfStates,int noOfInputs){
        for(int i=0;i<100;i++){
                for(int j=0;j<100;j++){
                        transitions[i][j]=-1;
                }
        }
        for(int i=0;i<noOfStates;i++){
                for(int j=0;j<noOfInputs;j++){
                        printf("Enter the transition from %d on input %d : ",i,j);
                        scanf("%d",&transitions[i][j]);
                }
        }
}

void checker(int noOfStates,int startState,int *finalStates,int noOfFinalStates){
        printf("Enter the string to check : ");
        char string[100];

        getchar();
        scanf("%s",string);
        int currentState=startState;
 	for(int i=0;string[i];i++){
                if(currentState==-1){
                        printf("%s is not recognised by the dfa\n",string);
                        return;
                }
                int currentInput=string[i]-'0';
                //printf("currentInput :%d  state : %d \n",currentInput,currentState);
                currentState=transitions[currentState][currentInput];
        }
        if(in(finalStates,noOfFinalStates,currentState)){
                printf("%s is recognised by the dfa\n",string);
                return;
        }
        printf("%s is not recognised by the dfa\n",string);
        return;
}

int main(){
        int noOfStates;
        int noOfInputs;
        printf("Enter the number of states : ");
        scanf("%d",&noOfStates);
        printf("Enter the number of inputs (0-1 means 2 inputs): ");
        scanf("%d",&noOfInputs);
        int *stateArray=(int *)malloc(sizeof(int)*noOfStates);
        int *inputArray=(int *)malloc(sizeof(int)*noOfInputs);

        //initializing the state array
        initializeStateArray(stateArray,noOfStates);

        int startState;
        printf("Enter start state : ");
        scanf("%d",&startState);

        int noOfFinalStates;
        printf("Enter number of final states : ");
        scanf("%d",&noOfFinalStates);

        int *finalStates=(int *)malloc(sizeof(int)*noOfFinalStates);
        for(int i=0;i<noOfFinalStates;i++){
                printf("Enter a final state : ");
		scanf("%d",&finalStates[i]);
        }

        initializeTransitions(noOfStates,noOfInputs);
        int flag;
        do{
        checker(noOfStates,startState,finalStates,noOfFinalStates);
        printf("E nter 1 to continue 0 to exit :");
        scanf("%d",&flag);
        }while(flag);
        free(stateArray);
        free(inputArray);
        free(finalStates);
        return 0;

}
