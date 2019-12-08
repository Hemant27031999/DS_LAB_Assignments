#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


/**  @brief main method will encrypt the file data in inputfile.txt and will write the encrypted data in outfile.txt
* @params n
* @params a
* @params b
* @params name of inputfile
* @return 0
*/
int main(int argc, char const *argv[])
{
	int n = atoi(argv[1]);
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);

	FILE *fp;
    char textstring[10000];
 
    fp = fopen(argv[4], "r");
    if (fp == NULL){
        printf("Could not open file %s",argv[4]);
    }

    int index = 0;
    char ch;
    while( (ch = getc(fp)) != EOF) {
	  textstring[index] = ch;
	  index++;
	 }

    fclose(fp);

    char copy[10000];
    strcpy(copy, textstring);
    char* str = copy;

	unsigned int len = strlen(str);
	if(len%n != 0){
		for(int i = len; i<(len+(n-len%n)); i++){
			str[i]='$';
		}
	}
	len = strlen(str);

	int j[len];
	for(int i=0;i<len;i++){
		j[i] = (a*(i%n)+b)%n;
	}	char out[10000];

	for (int i = 0; i < len; i++)
	{
		out[i] = str[j[i]+(i/n)*n];
	}

	FILE *fptr;
    fptr = fopen("outputfile.txt","w");

    if(fptr == NULL)
    {
      printf("Error!");   
      exit(1);             
    }

    fprintf(fptr,"%s",out);
    printf("The encrypted string has been written in the outputfile.txt file.\n");
    fclose(fptr);
    printf("Your encrypted string is : \n%s\n", out);

	return 0;
}