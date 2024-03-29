// Luis Ivan

// Hill Cipher 

// This program converts plain text in to encrypted text
// when provided with a cipher key of "n" length.
// "n" can not be any larger than 9 or smaller than 2

/*
			 matrix multiplaction and hill
		   key	 cipher		math			  encrypt
		|d|e|f|	  |a| 	(d*a + e*b + f*c)%26   |m|
		|g|h|i|	* |b| = (g*a + h*b + i*c)%26 = |n|
		|j|k|l|	  |c| 	(j*a + k*b + l*c)%26   |o|
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char *argv[])
{
	
	FILE *eKeyFile = NULL;
	FILE *ptextFile = NULL;
	int *keyBuffer=NULL; 
	char *ptextBuffer=NULL;
	char *etextBuffer=NULL;
	char *etext=NULL;
	char temp;
	int e=0;
	int index,key,count,row,col,ecount;
	int i=0,j=0,k;
	
	int charCap = 10000;
	int capacity = 82;
	int size = 0;
	
	keyBuffer=malloc(sizeof(int)*capacity);
	ptextBuffer=malloc(sizeof(char)*charCap);
	

	// encryption key file will store a single positive integer,
	// n (1 < n < 10), number of rows and columns in matrix
	// "r" = open for reading 
	if ((eKeyFile = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Could not open %s in main()!\n", argv[1]);
		exit(0);
	}
	
	// character array of size 10000,
	// the text files no more than 9991 letters 
	if ((ptextFile = fopen(argv[2], "r")) == NULL)
	{
		fprintf(stderr, "Could not open %s in main()!\n", argv[2]);
		exit(0);
	}
	
	// stores the key	
	while (fscanf(eKeyFile, "%d" , keyBuffer+size)!=EOF)
	{ 
		
		key=keyBuffer[0];
			
		size++;
	}
	
	for(j=size; j<capacity; j++ )
	{
		keyBuffer[j]=-1;
    }
	
    i=0;
    
    // takes in every character and determines if letter
    // if letter is capital it is converted to lower case
    while (fscanf(ptextFile, "%c" , ptextBuffer+i)!=EOF)
    { 	
    	temp=ptextBuffer[i];
    	
    	// 65 - 90   A - Z
		// 97 - 122  a - z
		if(temp>=65&&temp<=90)
		{
			ptextBuffer[i]=temp+32;
			i++;
		}
    	
    	if(temp>=97&&temp<=123)
			i++;
		 
    }	
		
	index=i;
	
	// we have to make sure that the index is a factor
	// of key[0] if not we need to padd with x's ptextBuffer
	// index is how many letters taken in
	while(index%key!=0)
	{
		
		ptextBuffer[index]=0;
		ptextBuffer[index]='x';
		index++;
		
	}
	

	// creating the encrypted text buffer
	etext=malloc(sizeof(char)*index);
	
	// size of key array
	
	count=0;
	ecount=1;

	// this is supposed to do matrix multiplication Hill style
	while(count<index)
	{
		// rows of the matrix
		for(row=0;row< key;row++)
		{
			
			
			// columns of the matrix
			k=count;
			for(col=0;col< key;col++)
			{	
			
				if(ecount==(key*key+1))
					ecount=1;
						
				e=(int)e+((int)ptextBuffer[k++]-97)*(keyBuffer[ecount]);
			
				ecount++;
				
				if(ecount==(key*key+1))
					ecount=1;
						
			}
				
			// mod26 makes sure the text is from 0 to 25
			// which correlates to the letters of the alphabet 
			etext[row+count]=e%26+'a';
		
			e=0;
		}
		ecount=1;
		
		count=key+count;
			
	}
	
	// prints out the key
	printf("\nKey matrix:\n\n");
	
	for(i=1;i<size;i++)
	{
		printf("%d ", keyBuffer[i]);
		
			if(i%key==0)
				printf("\n");
	}
	
	printf("\n");
	printf("\nPlaintext:\n\n");
	
	// this one prints out the text
	for (i=0;i<index;i++)
	{
		
		printf("%c", ptextBuffer[i]);
		if(i%80==79)
			printf("\n");
	}
	
	printf("\n\n");
	
	printf("\nCiphertext:\n\n");
	
	
	// this one prints out encrypted text
	for (i=0;i<index;i++)
	{
		
		printf("%c", etext[i]);
		if(i%80==79)
			printf("\n");
	}
	
	printf("\n\n");
	
fclose(eKeyFile);
fclose(ptextFile);
free(keyBuffer);
free(ptextBuffer);
free(etext);
	
return 0; 
}