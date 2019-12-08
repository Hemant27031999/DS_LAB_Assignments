#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


/**  @brief main method will compare the input and decryptedOutput file and will print out the equivalance
* @return 0
*/
int main()
{
	FILE *fp;
    char inputString[10000];
 
    fp = fopen("inputfile.txt", "r");
    if (fp == NULL){
        printf("Could not open file %s","inputfile.txt");
    }

    int index = 0;
    char ch;
    while( (ch = getc(fp)) != EOF) {
	  inputString[index] = ch;
	  index++;
	 }

    fclose(fp);

    char outputString[10000];
 
    fp = fopen("decryptedOutputfile.txt", "r");
    if (fp == NULL){
        printf("Could not open file %s","decryptedOutputfile.txt");
    }

    index = 0;
    while( (ch = getc(fp)) != EOF) {
	  outputString[index] = ch;
	  index++;
	 }

    fclose(fp);

	int len = strlen(inputString);
	int count=0;
	for (int i = 0; i < len; i++)
	{
		if(inputString[i] != outputString[i]){
			count++;
		}
	}
	printf("\n------------------Comparing two files--------------------\n");

	if(count == 0){
    	printf("Your equivalance is 0. GOOD WORK !!!\n");
    }
    else{
    	printf("Your equivalance is %d. CHECK YOUR CODE AGAIN !!!\n",count);
    }

	return 0;
}