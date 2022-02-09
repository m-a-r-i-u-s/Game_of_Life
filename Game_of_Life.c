#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int x_size = 100;
const int y_size = 100;

const double cycles = 5000.0;

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


//Modulo
int mod(int a, int b) {

	if ( a < 0 ) return a % b + b ;
	else  return a % b;


}


int main(){

	FILE *f = fopen("Game_Saver.txt", "w");

	long int universe[x_size][y_size];
	long int parallel_universe[x_size][y_size];

	double iterator;

	int init = 5000;

	double perc;

	srand(time(NULL));

	//Initialize the universe
	for (int i = 0; i < x_size; i++){
		for (int j = 0; j < y_size; j++){

			int coin = 1 + random() % 100;

			if (coin <= 50 && init > 0) {
				universe[i][j] = 1 ;
				init -= 1 ;
			}
			else universe[i][j] = 0 ;

                        //printf("%ld ", universe[i][j]);
		
		}
                //printf("\n");
	}


	printf("\n");

	long int sum;
	
	iterator = 0.0;

	double summation[x_size][y_size];

	//Main loop -> Iterate to time
	while (iterator < cycles){

		//Calculate and display percentages
		perc = iterator / (cycles - 1);
		printProgress(perc);

		for (int i = 0; i < x_size; i++) {
			for (int j = 0; j < y_size; j++) {
				
                                fprintf(f, "%ld ", universe[i][j]);

                                parallel_universe[i][j] = 0 ;

				//Check neighbours
				sum = 0;
				
				for (int m = -1; m <= 1; m++) {
					for (int n = -1; n <= 1; n++) {
						if (m == 0 & n == 0) ;
                                                else sum += universe[mod(i+m, x_size)][mod(j+n, y_size)] ;
                                        }
				}

                                if (universe[i][j] == 1){
				        if (sum > 3 || sum < 2) parallel_universe[i][j] = 0 ;
                                        else parallel_universe[i][j] = 1 ;
                                }
                                else{
				        if (sum == 3) parallel_universe[i][j] = 1 ;
                                        else parallel_universe[i][j] = 0 ;
                                }
				
			}
		}

		fprintf(f, "\n");

		for (int i = 0; i < x_size; i++) {
			for (int j = 0; j < y_size; j++) {
                                universe[i][j] = parallel_universe[i][j] ;
                        }
                }
                
	
		
		iterator += 1.0;


	}
	
	printf("\n");

	fclose(f);
								
	return 0;
}
