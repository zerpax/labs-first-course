#include <stdio.h>

int main(){
	char c = getchar();
	int m[8][8];
	int row = 0, col = 0, num = 0;
	while (c != EOF) {
		if (c == ' ') {
			m[row][col] = num;
			++col;
			num = 0;
		} else if (c == '\n') {
			m[row][col] = num;
			if (col == row) {
				++row;
				for (int i = 0; i < row; ++i) { 		
					for (int j = 0; j < row; ++j) {
						printf("%d ", m[(i+j+1)%row][j]);
					}
					printf("\n");
				}
				row = -1;	
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
