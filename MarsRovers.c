#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dynstring.h"
#include "MR_functions.h"

#define INITSIZE 10

int main () {
	
	int x, y; char facing; char *comands; //variables related to creating Rover structure
	int i;
	int px,py; 
	char resp = '\0';
	int error = 0;
	
	do {
	printf ("Enter the upper-right coordinates of the plateau (must be integers): ");
	if ((error = scanf ("%d %d", &px, &py)) != 2) printf ("\nERROR: Input value must be a integer.\n\n");
	getchar ();
	} while (error != 2);
	
	rover = malloc (sizeof(struct MarsRover));
	
	while (resp != '\n'){ //loop for user input
		
		rover = realloc (rover, (s+1)*sizeof(struct MarsRover)); //dynamic memory allocation, changes for each new rover
		
		do { //forbids user to enter inconsistent values
			do {
			printf ("\n\nEnter coordinates x, y and the orientation (N, S, E or W) for Rover %d: ", s+1);
			if ((error = scanf ("%d %d %c", &x, &y, &facing))!=3) printf ("\nERROR: Input value of x and y must be a integers, and orientation must be a character.\n\n");
			getchar ();
		} while (error != 3);
			
			if ((error = rover_plateau_check (x, px, y, py) )!= 0) ERROR1; //checks if Rover position is inside the plateu
			if (facing == 'N' || facing == 'S' || facing == 'E' || facing == 'W' ); //checks if facing input is consistent
			else {
				ERROR2;
				error = -1;
			}
		} while (error != 0);
		
		do { //forbids user to enter inconsistent values
			comands = malloc (INITSIZE*sizeof(char));
			printf ("\n\nEnter command input for Rover %d: ", s+1);				
			dyngets (comands, INITSIZE); //reads variable size string (library "dynstring.h")
			
			if ((error = rover_comands_check (comands) )!= 0) ERROR3; //checks if Rover comands input are consistent
		} while (error!= 0);
		
		rover[s] = Rover_create (x, y, facing, comands); //create Rover 
		
		printf ("\n\nPress enter to execute or press any other key to enter another Rover\n");
		resp = getchar ();
		s++;				
	}
	
	printf ("\n**********************************************************\n");
	for (i=0; i<s; i++) { //compute Rover's input and print results
		
		rover[i] = rover_controller(rover[i], i, px, py);
		rover_result_print (rover[i], i);		
	}
	
	printf ("\n**********************************************************\n");
	
	for (i=0; i<s; i++) { //free allocated memory		
		rover_free (rover[i]);	
	}
	
	system ("PAUSE");
	
	
}
