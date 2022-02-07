#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int x_size = 10;
const int y_size = 10;

const int x_board = 8;
const int y_board = 8;

const int cycles = 100;

//Matrix-Print Function
void mprint(double matrix[x_size][y_size]){

	for (int i = 0; i < x_size; i++){

		for (int j = 0; j < y_size; j++){

			printf("%f ", matrix[i][j]);

		}

		printf("\n");
	}

}


int main(){

	FILE *f = fopen("Game_Saver.txt", "w");

	double universe[x_size][y_size];

	for (int i = 0; i<x_size; i++){

		for (int j = 0; j<y_size; j++){

			universe[i][j] = 0.0;
		}
	}

	int iterator, init;

	int x, y;

	iterator = 0;
	init = 40;
	
	srand(time(NULL));

	//Initialize the universe
	while (iterator < init){

		x = 1 + random() % x_board;
		y = 1 + random() % y_board;

		if (universe[x][y]  == 0.0){

			universe[x][y] += 1.0;

			iterator += 1;

		}

		if (x == x_board-1 && y == y_board-1){

			universe[0][0] += 1.0; 

		}

		if (x == x_board-1 && y != y_board-1){

			universe[0][y] += 1.0; 

		}

		if (y == y_board-1 && x != x_board-1){

			universe[x][0] += 1.0; 

		}

		if (x == 1 && y == 1){

			universe[x_size-1][y_size-1] += 1.0; 

		}

		if (x == 1 && y != 1){

			universe[x_size-1][y] += 1.0; 

		}

		if (y == 1 && x != 1){

			universe[x][y_size-1] += 1.0; 

		}




	}

	double alpha = 10;
	
	iterator = 0;

	double summation[x_board][y_board];

	while (iterator < cycles){
	
		for (int i = 0; i<x_board; i++){

			for (int j = 0; j<y_board; j++){

				summation[i][j] = 0.0;
			}
		}

	
		for (int m =0; m<3; m++){

			for (int n =0; n<3; n++){

				for (int i = 0; i < x_board; i++){

					for (int j=0; j < y_board; j++){

						if (m == 1 && n == 1){
							summation[i][j] += universe[i+m][j+n]*10.0;
						}

						else {
							summation[i][j] += universe[i+m][j+n];
						}

					}
				}
			}
		}

		iterator += 1;

		for (int i = 0; i <= x_board; i++){

			for (int j = 0; j <= y_board; j++){

				universe[i+1][j+1] = 0.0;

				if (summation[i][j] == 3.0){

					universe[i+1][j+1] += 1.0;
				}
				if (summation[i][j] == 12.0 || summation[i][j] == 13.0){
					universe[i+1][j+1] += 1.0;
				}


				if (i == x_board && j == y_board){

					universe[0][0] = universe[i][j]; 

				}

				if (i == x_board && j != y_board){

					universe[0][j] = universe[i][j] ;

				}

				if (j == y_board && i != x_board){

					universe[i][0] = universe[i][j]; 

				}

				if (i == 1 && j == 1){

					universe[x_size-1][y_size-1] = universe[i][j]; 

				}

				else if (i == 1 && j != 1){

					universe[x_size-1][j] = universe[i][j]; 

				}

				else if (j == 1 && i != 1){

					universe[i][y_size-1] = universe[i][j]; 

				}

					}

				}

		for (int i = 1; i < x_size-1; i++){

			for (int j = 1; j < y_size-1; j++){

				fprintf(f, "%f ", universe[i][j]);

			}

		}
		fprintf(f, "\n");


	}

	fclose(f);
								
	return 0;
}
