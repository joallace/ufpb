//Problem 1063 - Wrong answer (5%) 	

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char *stack;
    int index;
    int size;
}tStack;

tStack* newStack(int size){
    tStack* stck = (tStack*) malloc(sizeof(tStack));

    stck->stack = (char*) malloc(size * sizeof(char));
    stck->size = size;
    stck->index = -1;

    return stck;
}

void push(tStack *stck, char item){
    stck->stack[++(stck->index)] = item;
}

char pop(tStack* stck){
    if(stck->index > -1){
        return stck->stack[(stck->index--)];
    }
    else{
        return 0;
    }
}

char top(tStack* stck){
	return stck->stack[(stck->index)];
}

int main(){
    tStack* stck;
    int initialTrainSize, trainSize, i, j, c;
	char wagons[52], desiredOrder[52], answer[52], impossible;

    while(1){
        scanf("%d%*c", &initialTrainSize);
        trainSize = initialTrainSize;
        if(!trainSize)
        	return 0;

        stck = newStack(trainSize);
        
        fgets(wagons, 52, stdin);
        fgets(desiredOrder, 52, stdin);

        for(i = 0, c = 0, impossible = 0; i < initialTrainSize*2 && !impossible; i+=2){
        	if(top(stck) == desiredOrder[i]){
				pop(stck);
				answer[c++] = 'R';
                continue;
			}else if(!trainSize)
				impossible = 1;

            for(j = 0; j < initialTrainSize*2 && trainSize > 0; j+=2){
				if(wagons[j] == 0)
					continue;

                if(wagons[j] != desiredOrder[i]){
                	push(stck, wagons[j]);
                    answer[c++] = 'I';
                    wagons[j] = 0;
                    trainSize--;
                }
                else{
                    answer[c++] = 'I';
				    answer[c++] = 'R';
				    wagons[j] = 0;
				    trainSize--;
                    break;
                }
                
                if(trainSize == 0 && top(stck) != desiredOrder[i]){
		    		impossible = 1;
		    		break;
        		}
            }
        }
        answer[c] = '\0';
        printf("%s%s", answer, impossible?" Impossible\n":"\n");
    }
}
