#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


struct Node
{
	int store;
	int high;
	int index;
	struct Node* next;
};

/**  @brief the input array */
int **a;
/**  @brief Maximal Square Array */
int **filled;
/**  @brief length of Maximal Square Array */
int lngh;
/**  @brief head pointer pointing to the first node of tree */
struct Node* first = NULL;
/**  @brief last pointer pointing to the last node of tree */
struct Node* last = NULL;
/**  @brief index which tells weather linked list has any node or not  */
int init=1;

/**  @brief next_pow_2 calculates the next power of 2 after the given number
* @params n the required number
* @return next power of 2
*/
int next_pow_2(int n){
	if(!(n & (n-1)))
		return n;
	else{
		int count = 0;
		while(n != 0){
			n = n>>1;
			count++;
		}
		return 1<<count;
	}
}

/**  @brief check method is the method that will search the array and looks if all values are same or not
* @params x1 initial x index
* @params y1 initial y index
* @params x2 final x index
* @params y2 final y index
* @params value 
* @params level of tree
*/
void check(int x1, int y1, int x2, int y2, int* value, int level){

	int swch = 1;
	for(int i=x1; i<=x2; i++){
		for(int j=y1; j<=y2; j++){
			if(!a[i][j] == a[x1][y1]){
				swch = 0;
				break;
			}
		}
	}

	if(swch){
		for(int i=x1; i<=x2; i++){
			for(int j=y1; j<=y2; j++){
					filled[i][j] = *value;
			}
		}
		struct Node* node = (struct Node*) malloc(sizeof(struct Node));
		node->high = level;
		node->index = *value;
		node->store = a[x1][y1];
		if(init){
			first = node;
			last = node;
			init = 0;
		}
		else{
			last->next = node;
			last = node;
		}
		*value = *value+1;
	}

	else{
		check(x1, y1, (x1+x2)/2, (y1+y2)/2, value, level+1);
		check(x1, (y1+y2)/2+1, (x2+x1)/2, y2, value, level+1);
		check((x1+x2)/2+1, y1, x2, (y1+y2)/2, value, level+1);
		check((x1+x2)/2+1, (y1+y2)/2+1, x2, y2, value, level+1);
	}
}


/**  @brief main method read the input file 
* @return 0
*/
int main()
{
	FILE *fp;
 
    fp = fopen("L2_P2_inputsample.txt", "r");
    if (fp == NULL){
        printf("Could not open file L2_P2_inputsample.txt\n");
    }
    char* getValue;
    char str1[1000];
    fgets(str1, 1000 , fp);
	int count = 0;
	if(strtok(str1, " ")){
		count++;
	}
	while(strtok(NULL, " ")){
		count++;
	}
	fclose(fp);

	fp = fopen("L2_P2_inputsample.txt", "r");
    if (fp == NULL){
        printf("Could not open file L2_P2_inputsample.txt\n");
    }
	char str[1000];
    fgets(str, 1000 , fp);

    int pow_two = next_pow_2(count);
	lngh = pow_two;

	a = (int **) malloc ((pow_two) * sizeof(int*));
    for(int i = 0; i < pow_two; i++)
        a[i] = (int *) malloc((pow_two) * sizeof(int));

    filled = (int **) malloc ((pow_two) * sizeof(int*));
    for(int i = 0; i < pow_two; i++)
        filled[i] = (int *) malloc((pow_two) * sizeof(int));

	int diff = pow_two-count;
	for (int i = 0; i < pow_two; i++){
		if(i>=diff){
			getValue = strtok(str, " ");
		}
		for (int j = 0; j < pow_two; j++){
			if (i<diff || j>(count-1)){
					a[i][j]=0;
					// printf("%d ", a[i][j]);
				}
			else{
				a[i][j] = atoi(getValue);
				getValue = strtok(NULL, " ");
			}
		}

		if(i>=diff){
			fgets(str, 1000 , fp);
		}

	}

    fclose(fp);

    int value = 1;
    int level=0;
    check(0, 0, lngh-1, lngh-1, &value, level);

    int onoff = 1;
    int oprn;
    struct Node* current = first;
    while(onoff){

    	printf("\nEnter the index of operation you want to perform :\nTo print the Maximal square array : 1\nTo print the tree nodes : 2\nExit the program : 0\nEnter the index : ");
	    scanf("%d", &oprn);
	    switch(oprn){
	    	case 1:
			    printf("\n________________________  Maximal Square Array  ________________________\n\n");
			    for(int i=0; i<lngh; i++){
						for(int j=0; j<lngh; j++){
								printf("%02d ", filled[i][j]);
						}
						printf("\n");
					}
					printf("________________________________________________________________________\n");
				break;
			case 2:
				printf("\n________________________  Tree Nodes  ________________________\n\n");
				if(current){
					do{
						printf("(%02d, %d, %d)\n", current->index, current->store, current->high);
						current = current->next;
					}while(current!=NULL);
				}
				printf("_______________________________________________________________\n");
				break;

			case 0:
				exit(0);
				break;
			default:
				printf("\n_______________________________________________________________________\n");
				printf("\n!!!!!!!!!!!!!!!  Enter a valid index please  !!!!!!!!!!!!!!!\n");
				printf("_______________________________________________________________________\n");
		}
	}
	return 0;
}