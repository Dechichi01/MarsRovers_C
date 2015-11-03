/*defining different possible errors*/
#define ERROR0 printf ("\nERROR: Input values type is inconsistent with expected value.\n\n"); getchar()
#define ERROR1 printf ("\nERROR: Rover coordinates make it outside of the plateau.\n")
#define ERROR2 printf ("\nERROR: Rover orientation must be N, S, E, W.\n")
#define ERROR3 printf ("\nERROR: Rover commands must be 'L', 'R', or 'M'.\n")
#define ERROR4 printf ("\nERROR: Comand input %d of Rover %d sends it outside of the plateau. Rover %d stopped.\n", i+1, n+1, n+1)
#define ERROR5 printf ("\nERROR: Comand %d of Rover %d sends it to colide with Rover %d. Rover %d controller stopped.\n", i+1, n+1, error, n+1)

struct MarsRover { //struct to represent a Rover
	int xi,yi;
	int xf, yf;
	char facing_i, facing_f;
	char *comands;
	
};

struct MarsRover **rover; //global pointer to structure
int s = 0; //holds the number of Rovers input at main

struct MarsRover *Rover_create (int x, int y, char facing, char *comands){//initialize a rover with input information from the user
	
	struct MarsRover *rover = malloc (sizeof(struct MarsRover));
	
	rover->xi= x; rover->xf = x;
	rover->yi= y; rover->yf = y;
	rover->facing_i = facing; rover->facing_f = facing;
	rover->comands = strdup(comands);
	
	return rover;
	
	
}

void rover_free (struct MarsRover *rover){//free allocated memory
	free (rover->comands);
	free (rover);
}


void rover_result_print (struct MarsRover *rover, int i){//print result state (x y orientation) of a Rover
	printf ("\n\n");
	
	printf ("Result position and orientation for Rover %d: %d %d %c", i+1, rover->xf, rover->yf, rover->facing_f);
	
	printf ("\n\n");
}

int rover_plateau_check (int x, int xmax, int y, int ymax){//check if rover is inside the plateau
	int error = 0;
	
	if (x > xmax || x < 0 || y > ymax || y < 0) error = -1;
	
	return error;
}

int rover_comands_check (char *comands){ //chefk if comands input for Rover are consistent
	int i=0, error = 0;
	
	while (comands[i] != '\0'){
		if (comands[i] == 'L' || comands[i] == 'R' || comands[i] == 'M') ;
		else error = -1;
		i++;
	}
	
	return error;
}

int rover_pos_check (int x, int y, int n) { //check relative position between a Rover and all others
	int j, error = 0;
	
	for (j=0;j<n; j++){
		if ((x == rover[j]->xf && y == rover[j]->yf) ){
			error = j+1;
		}
	}
	return error;
	
}
struct MarsRover *rover_controller (struct MarsRover *rover, int n, int px, int py){ //control Rover movements
	int i=0, error = 0;
	
	while ((error = rover_pos_check (rover->xf, rover->yf, n)) != 0) {
		printf ("\nERROR: Initial position of Rover %d is coinciding with final position of Rover %d.", n+1, error);
		do{
			printf ("\nPlease enter another initial position (x y) for Rover %d: ", n+1);
			if ( (error = scanf ("%d %d", &rover->xi, &rover->yi) ) != 2){ ERROR0;	}
			} while (error != 2);
		rover->xf = rover->xi ; rover->yf = rover->yi;
	}
	
	while (rover->comands[i] != '\0'){ //execute until end of "comands" string
		switch (rover->comands[i]){
			
			case 'M':
				switch (rover->facing_f){
					case 'N':
						if ((error = rover_plateau_check (rover->xf, px, rover->yf + 1, py) )!= 0) {//checks if comand will lead the Rover out of the plateau. Ends the movement if so.
							ERROR4;
							break;
						}
						else if ((error = rover_pos_check (rover->xf, rover->yf + 1, n) ) != 0) {//checks if comand will lead the Rover to colide with another Rover. Ends the movement if so.
							ERROR5;
							break;
						}
						rover->yf++;
						break;
						
					case 'E':
						if ((error = rover_plateau_check (rover->xf + 1, px, rover->yf, py) )!= 0) { //same idea of case 'N'
							ERROR4;
							break;
						}
						else if ((error = rover_pos_check (rover->xf +1, rover->yf, n) )!= 0) {
							ERROR5;
							break;
						}
						rover->xf++;
						break;
					
					case 'S':
						if ((error = rover_plateau_check (rover->xf, px, rover->yf - 1, py) )!= 0) { //same idea of case 'N'
							ERROR4;
							break;
						}
						else if ((error = rover_pos_check (rover->xf, rover->yf - 1, n) )!= 0) {
							ERROR5;
							break;
						}
						rover->yf--;
						break;
						
					case 'W':
						if ((error = rover_plateau_check (rover->xf - 1, px, rover->yf, py) )!= 0) { //same idea of case 'N'
							ERROR4;
							break;
						}
						else if ((error = rover_pos_check (rover->xf - 1, rover->yf, n) )!= 0) {
							ERROR5;
							break;
						}
						rover->xf--;
						break;
						
					}
				break;
			
			default: //if not 'M' than we can only have 'L' or 'R'.				
				switch (rover->facing_f){
					case 'N': //rotates rover
						if (rover->comands[i] == 'L') rover->facing_f = 'W';
						else rover->facing_f = 'E';
						break;
						
					case 'E': //rotates rover
						if (rover->comands[i] == 'L') rover->facing_f = 'N';
						else rover->facing_f = 'S';
						break;
					
					case 'S': //rotates rover
						if (rover->comands[i] == 'L') rover->facing_f = 'E';
						else rover->facing_f = 'W';
						break;
						
					case 'W': //rotates rover
						if (rover->comands[i] == 'L') rover->facing_f = 'S';
						else rover->facing_f = 'N';
						break;
							}
							
						break;				
			}
			
			if (error != 0) break; //if any error happened during computing the Rover execution will end before finishing
			i++;
		}
	
	return (rover);
}
