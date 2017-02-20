// Luis Ivan
// Luisivan001@knights.ucf.edu
//
// Hill Cipher

// This program basically converts plain text in to encrypted text
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

#define DEBUG 0



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
	
	//keyBuffer = malloc(sizeof(char)*1000);
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
	
	// punctuation, numbers, special characters, and whitespace
	if ((ptextFile = fopen(argv[2], "r")) == NULL)
	{
		fprintf(stderr, "Could not open %s in main()!\n", argv[2]);
		exit(0);
	}
	
	// lets make this a matrix
	// stores the key	
	while (fscanf(eKeyFile, "%d" , keyBuffer+size)!=EOF)
	{ 
		
		key=keyBuffer[0];

		printf("%d ", keyBuffer[size]);
		
		if(size%key==0)
			printf("\n");
			
		size++;
	}
	
	for(j=size; j<capacity; j++ )
	{
		keyBuffer[j]=-1;
    }
	
	
	if(DEBUG>20)
    {
	
		// these prints let me know how large of a key 
		// that we are using
		printf("\n*** the size: %d ***\n\n", size);
		
		// this one tells me the limit
		printf("size: %d\ncapacity: %d\n\n", size, capacity);
    
    	printf("\n*** the size: %d ***\n\n", size);
	
		printf("size: %d\ncapacity: %d\n\n", size, capacity);
    	
   		if(DEBUG>20)
    	{
	
   			for(i=0; i<capacity; i++ )
			{
				printf("\n*** double check: %d ***\n", keyBuffer[i]);
			}
    	}
    
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

	// this is too double check the last char in the buffer
	// a non letter could have slipped in
	if (temp<97||temp>123)
	{
		ptextBuffer[index]=0;
		ptextBuffer[index]='x';
		index++;
	}
	
	
	// we have to make sure that the index is a factor
	// of key[0] if not we need to padd with x's ptextBuffer
	// index is how many letters taken in
	while(index%key!=0)
	{
		
		ptextBuffer[index]=0;
		ptextBuffer[index]='x';
		index++;
		
	}
	
	if(DEBUG>10)
	{
		printf("\n*** the index: %d ***\n\n", index);
		printf("\n*** the index: %d ***\n\n", index%key);
	}
	
	
	// creating the encrypted text buffer
	etext=malloc(sizeof(char)*index);
	
	// size of key array
	
	count=0;
	ecount=1;
	
	if(DEBUG>10)
	{
		
		printf("\n*** the key: %d ***\n\n", key);
	}
	
	
	// this is supposed to do matrix multiplication Hill style
	while(count<index)
	{
		// rows
		for(row=0;row< key;row++)
		{
			
			
			// columns
			k=count;
			for(col=0;col< key;col++)
			{	
			
				if(ecount==(key*key+1))
					ecount=1;
					
					
					
				// e is just a variable
				// ecount goes as far as the end of the key matrix
				// maybe the problem is a compiling error
				/* such as multiplication causing weird char
				if(ecount!=(key*key+1))
				{
					
					if(count==14)
					{
						printf("\n*** outside ***\n");
						printf("\ncount: %d\n\ne: %d \n",count,e);
						// printf("ecount: %d \n", ecount);
						printf("ptext: %d keyBuffer %d\n",ptextBuffer[k],keyBuffer[ecount]);

					}
				*/	
					e=(int)e+((int)ptextBuffer[k++]-97)*(keyBuffer[ecount]);
				

				
				
				ecount++;
				
				if(ecount==(key*key+1))
					ecount=1;
					
				
			}
			
			
			//mod26
			etext[row+count]=e%26+'a';
			
		/*
			if(count==14&&row==1)
			{
				printf("\ncount: %d\n\ne: %d \n",count,e);
				printf("etext: %d\n",etext[row+count]);
				printf("ptext: %d keyBuffer %d\n",ptextBuffer[k],keyBuffer[ecount]);
				printf("\necount: %d k: %d \n\n",ecount,k);
				
			}
		*/
		
			e=0;
		}
		ecount=1;
		
		
		count=key+count;
		
		
	}
	
	
	
	// this one prints out the text
	for (i=0;i<index;i++)
	{
		
		printf("%c", ptextBuffer[i]);
		if(i%40==39)
			printf("\n");
	}
	
	printf("\n\n");
	
	
	
	// this one prints out encrypted text
	for (i=0;i<index;i++)
	{
		
		printf("%c", etext[i]);
		if(i%40==39)
			printf("\n");
	}
	
	printf("\n\n");
	
	
	
	// this is the ptext in decimal
	printf("this is the ptext in decimal\n\n");
	for (i=0;i<index;i++)
	{
		
		printf("%d ", ptextBuffer[i]-'a');
		if(i%13==12)
			printf("\n");
	}
	
	printf("\n\n");
	
	/**/
	// this is the number representation of encrypted text
	printf("this is the etext in decimal\n\n");
	for (i=0;i<index;i++)
	{
		
		printf("%d ", etext[i]);
		if(i%13==12)
			printf("\n");
	}
	
	printf("\n\n");
	
	
	
return 0; 
}