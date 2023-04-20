#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main() {
	char c;
	char num[10];
	int dig = 0;
	int elem;

	int row = 1, col = 1;
	int matrix[1000];
	
	matrix[0] = 0;
	int count = 0;

	c = getchar();
	while (c != EOF) {
		if (isdigit(c)) {
			num[dig] = c;
			dig++;
		}
		if (c == ' ' || c == '\n') {
			elem = atoi(num);
			//printf("%d ", elem);
			if (elem != 0) {
				if (matrix[count] == 0) {
					count++;
					matrix[count] = row;
				}
				count++;
				matrix[count] = col;
				count++;
				matrix[count] = elem;
			}
			dig = 0;
			col++;
		}
		if (c == '\n') {	
				count++;
				matrix[count] = 0;		
			col = 1;
			row++;
		}
		c = getchar();
	}
	matrix[count] = 0;

	for (int i = 0; i < count; i++) {
		printf("%d ", matrix[i]);
		if (matrix[i] == 0) {
			printf("\n");
		}
	}
	printf("\n");
	
	int trans[1000];
	trans[0] = 0;
	int tr_count = 0;
	int size = row;
	row = -1;
	for (int i = 0; i < size; i++) {
		for (int j = count - 1; j >= 0; j -= 2) {

			

			if (matrix[j] == 0) {
				if (j != count - 1) {
					row = matrix[j + 1];
					//printf("%d %d ", row, col);
					int k = j + 2;
				
					while (matrix[k] != 0) {
						col = matrix[k];
						if (size - col == i) {
							if (trans[tr_count] == 0) {
								tr_count++;
								trans[tr_count] = i - 1;
							}
							tr_count++;
							trans[tr_count] = size - row - 1;
							tr_count++;
							trans[tr_count] = matrix[k + 1];
						}
						k += 2;
					}
				}
				while (matrix[j - 1] == 0) {
					j--;
				}
			}
		}
		



		/*for (int j = 0; j < count; j += 2) {
			col = matrix[j];
			if (matrix[j] == 0) {
				while (matrix[j + 1] == 0) {
						j++;
					}
					row = matrix[j + 1];
			}
			
			else if (size - col == i) {
				if (trans[tr_count] == 0) {
					tr_count++;
					trans[tr_count] = i - 1;
				}
				tr_count++;
				trans[tr_count] = size - row - 1;
				tr_count++;
				trans[tr_count] = matrix[j + 1];
			}

		}*/
		if (trans[tr_count] != 0) {
			tr_count++;
			trans[tr_count] = 0;
		}
	}
	tr_count++;
	trans[tr_count] = 0;
	tr_count++;
	trans[tr_count] = 0;
	for (int i = 0; i < tr_count; i++) {
                printf("%d ", trans[i]);
		if (trans[i] == 0) {
			printf("\n");
		}
        }

}
