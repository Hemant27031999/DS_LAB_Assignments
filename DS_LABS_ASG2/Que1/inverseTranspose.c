#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


/**  @brief modInverse calculate modulo inverse of a given number
* @params n
* @params a
* @return moduloinverse of a
*/
int modInverse(int a, int n) 
{ 
    a = a%n; 
    for (int x=1; x<n; x++) 
       if ((a*x) % n == 1) 
          return x; 
}


/**  @brief main method will decrypt the file data in outputfile.txt and will write the decrypted data in decryptedOutfile.txt
* @params n
* @params a
* @params b
* @return 0
*/
int main(int argc, char const *argv[])
{
	int n = atoi(argv[1]);
	int a = atoi(argv[2]);
	int b = atoi(argv[3]);

	int a_new, b_new;
	a_new = modInverse(a, n);
	b_new = n - (a_new * b)%n;

	FILE *fp;
    char textstring[10000];
 
    fp = fopen("outputfile.txt", "r");
    if (fp == NULL){
        printf("Could not open file outputfile\n");
    }

    int index = 0;
    char ch;
    while( (ch = getc(fp)) != EOF) {
	  textstring[index] = ch;
	  index++;
	 }

    fclose(fp);

    char* str = textstring;

	unsigned int len = strlen(str);
	char out[10000];

	for (int i = 0; i < len; i++)
	{
		out[i] = str[(a_new*(i%n)+b_new)%n + (i/n)*n];
	}

	for (int i = 0; i < len; i++)
	{
		if(out[i]=='$'){
			out[i]='\0';
		}
	}

	FILE *fptr;
    fptr = fopen("decryptedOutputfile.txt","w");

    if(fptr == NULL)
    {
      printf("Error!");   
      exit(1);             
    }

    fprintf(fptr,"%s",out);
    printf("Your decrypted string is : \n%s\n", out);
    printf("The decrypted string has been written in the decryptedOutputfile.txt file.\n");
    fclose(fptr);

	return 0;
}
