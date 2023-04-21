#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void Print (int *matrix, int count, int size) {
	int row, col;
	int prow = 1, pcol = 1;
	for (int i = 0; i < count; i+=2) {
		if (matrix[i] == 0) {
			while (matrix[i + 1] == 0) {
					i++;
			}
			row = matrix[i + 1];
		}
		else {
			col = matrix[i];
			//printf("|%d, %d|", row, col);
			while (prow != row || pcol != col) {

				printf("0 ");
				pcol++;
				if (pcol == size) {
					printf("\n");
					pcol = 1;
					prow++;
				}
				
			}
			printf("%d ", matrix[i + 1]);
			if (pcol == size) {
					printf("\n");
			}
			pcol++;
			if (pcol == size) {
				printf("\n");
				pcol = 1;
				prow++;
			}
		}
	}

	while (prow != size) {
		printf("0 ");
		pcol++;
		if (pcol == size) {
			printf("\n");
			pcol = 1;
			prow++;
		}
	}
}

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
		if (c == ' ') {
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
				if (matrix[count] != 0) {
					count++;
					matrix[count] = 0;
				}		
			col = 1;
			row++;
		}
		c = getchar();
	}
	matrix[count] = 0;
	count++;
	matrix[count] = 0;

	for (int i = 0; i <= count; i++) {
		printf("%d ", matrix[i]);
		if (matrix[i] == 0) {
			printf("\n");
		}
	}
	printf("-----------------------------------\n");
	Print(matrix, count, row);
	printf("\n-----------------------------------\n");

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
								trans[tr_count] = i;
							}
							tr_count++;
							trans[tr_count] = size - row;
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
	printf("-----------------------------------\n");
	Print(trans, tr_count, size);
}
