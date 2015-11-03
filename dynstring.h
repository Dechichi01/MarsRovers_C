#include <stdio.h>
#include <stdlib.h>

#define DELTASIZE 5


char cleanstr (char *string, int a, int b){ //clean string
	int i;
	
	for (i = a; i<=b; i++){
				string[i] = '\0';
	}
	
	return (*string);
}


char dyngets (char *buffer, int initsize){ //reads input string of variable size
	char ch, *temp;
	int i=0, curs = initsize;
	
	getchar();
	
	cleanstr (buffer, 0, curs);
		
	while ( (ch=getchar())!= '\n') { //loop until user hits enter
		if (i >= curs){ //input is happening on the end of string
			curs = curs + DELTASIZE; //increase string cursor			
			if ((temp = realloc (buffer, curs*sizeof(char))) == NULL){ //failed to allocate memory, will return partial line
				printf ("\ndyngets (): Failed to allocate memory, returning partial line.\n");
				buffer[i] = '\0';
				return (*buffer);				
			}
			buffer = temp; //memory allocation sucessfull, transfering information to buffer
			cleanstr (buffer, curs-DELTASIZE, curs); //clean new memory positions
			buffer[i] = ch;
		}
		else {
			buffer[i] = ch;		
		}
		i++;
	}
	
	return (*buffer);
}
