#include <stdio.h>

int main(){
	char c = getchar();
	int m[7][7];
	int row = 0, col = 0, num = 0;
	while (c != EOF) {
		if (c == ' ') {
			m[row][col] = num;
			++col;
			num = 0;
		} else if (c == '\n') {
			m[row][col] = num;
			if (col == row) {
				for (int i = 0; i <= row * 2; ++i) {
					for (int j = i < row ? i : row; j >= 0 && j >= i - row; --j) {
						if (i % 2 == 0) {
							printf("%d ", m[row - (i - j)][j]);					
						} else {
							printf("%d ", m[row - j][i - j]);
						}
					}
				}
				row =-1;
				printf("\n");
			}	
			++row;
			col = 0;
			num = 0;
		} else {
			num = num * 10 + ((int)c - 48);
		}
		c = getchar();
	}
}
