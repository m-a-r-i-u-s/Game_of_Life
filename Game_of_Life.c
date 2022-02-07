#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int x_size = 50;
const int y_size = 50;

const double cycles = 5.0;

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60


//Print a progress bar for the main loop
void printProgress(double percentage) {
    //Source: https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}

//Matrix-Print Function
void mprint(double matrix[x_size][y_size]){

	for (int i = 0; i < x_size; i++){

		for (int j = 0; j < y_size; j++){

			printf("%f ", matrix[i][j]);

		}

		printf("\n");
	}

}

//Modulo
int mod(int a, int b) {

	int c ;

	if ( a < 0 ) c = a % b + b ;
	else if ( a > b ) c = a % b;
	else if ( a == b) c = 0;

	return c ;

}


int main(){

	FILE *f = fopen("Game_Saver.txt", "w");

	long int universe[x_size][y_size];

	double iterator;

	int init = 1000;

	double perc;

	srand(time(NULL));

	//Initialize the universe
	for (int i = 0; i < x_size; i++){
		for (int j = 0; j < y_size; j++){

			int coin = random() % 2;

			if (coin == 1 && init > 0) {
				universe[i][j] = 1 ;
				init -= 1 ;
			}
			else universe[i][j] = 0 ;
		
		}
	}

	long int sum;
	
	iterator = 0.0;

	double summation[x_size][y_size];
	
	//Main loop -> Iterate to time
	while (iterator <= cycles){

		//Calculate and display percentages
		perc = iterator / cycles;
		printProgress(perc);

		for (int i = 0; i < x_size; i++){
			for (int j = 0; j < y_size; j++) {

				//Check neighbours
				sum = 0;
				
				for (int m = -1; m <= 1; m++){
					for (int n = -1; n <= 1; n++){
						if (m == 0 & n == 0) {}
					        else sum += universe[mod(i+m, x_size)][mod(j+n, y_size)] ;
					}
				}

				printf("%ld ", sum);

				if (sum == 3 || sum == 2)  universe[i][j] = 1 ; 
				else if (sum < 2 || sum > 3) universe[i][j] = 0 ; 
				
				fprintf(f, "%ld ", universe[i][j]);

			}
		}

	
		fprintf(f, "\n");
		
		iterator += 1.0;


	}
	
	printf("\n");

	fclose(f);
								
	return 0;
}
