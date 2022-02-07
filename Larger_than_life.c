#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Matrix-Print Function
//void mprint(double matrix[x_size][y_size]){
//
//	for (int i = 0; i < x_size; i++){
//
//		for (int j = 0; j < y_size; j++){
//
//			printf("%f ", matrix[i][j]);
//
//		}
//
//		printf("\n");
//	}
//
//}


int main(){

	FILE *f = fopen("Game_Saver.txt", "w");

	int window, cycles, iterator, init, x, y;
	int x_board;
	int y_board;

	double birth, survive_1, survive_2;
	
	printf("Select x board size:\n");
	scanf("%d", &x_board);
	printf("Select y board size:\n");
	scanf("%d", &y_board);
	printf("Select initialization population:\n");
	scanf("%d", &init);
	printf("Select cycle number:\n");
	scanf("%d", &cycles);
	printf("Select your preferred window size:\n");
	scanf("%d", &window);
	printf("Select your preferred birth rule:\n");
	scanf("%lf", &birth);
	printf("Select your preferred first survive rule:\n");
	scanf("%lf", &survive_1);
	printf("Select your preferred second survive rule:\n");
	scanf("%lf", &survive_2);
	

	int x_size = x_board + (2 * (window - 2));
	int y_size = x_board + (2 * (window - 2));
	
	double universe[x_size][y_size];

	for (int i = 0; i<x_size; i++){

		for (int j = 0; j<y_size; j++){

			universe[i][j] = 0.0;
		}
	}

	iterator = 0;
	
	srand(time(NULL));

	//Initialize the universe
	while (iterator < init){

		x = (window - 2) + random() % x_board;
		y = (window - 2) + random() % y_board;

		if (universe[x][y]  == 0.0){

			universe[x][y] += 1.0;

			iterator += 1;

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

	
		for (int m =0; m<window; m++){

			for (int n =0; n<window; n++){

				for (int i = 0; i < x_board; i++){

					for (int j=0; j < y_board; j++){

						if (m == (window-2) && n == (window-2)){
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

		for (int i = 0; i < x_board; i++){

			for (int j = 0; j < y_board; j++){

				universe[i+(window-2)][j+(window-2)] = 0.0;

				if (summation[i][j] == birth){

					universe[i+(window-2)][j+(window-2)] += 1.0;
				}
				if (summation[i][j] == 10.0 + survive_1 || summation[i][j] == 10.0 + survive_2){
					universe[i+(window-2)][j+(window-2)] += 1.0;
				}

			}

		}

		for (int i = (window - 2); i < x_size - (window - 2); i++){

			for (int j = (window - 2); j < y_size - (window - 2); j++){

				fprintf(f, "%f ", universe[i][j]);

			}

		}
		fprintf(f, "\n");


	}

	fclose(f);
								
	return 0;
}
