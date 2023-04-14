#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "person.h"


int check(char (*airports)[50], int size, char* value) {
	bool flag;
	for (int i = 0; i < size; i++) {
		flag = true;
		for (int j = 0; j < 50; j++) {
			if (airports[i][j] != value[j]) {
				flag = false;
			}
		}
		if (flag) {
			return i;		
		}
	}
	return -1;
}


int main(int argc, char* argv[]) {
	person p;
	FILE *in = fopen(argv[1], "rb");

	if (argv[2][1] == 'p') {
		int size = 0;	
		char airports[400][50];
		float weights[400];
		int sizes[400];
		int ind;

		while (fread(&p, sizeof(p), 1, in) == 1) {
			ind = check(airports, size, p.destination);
			if (ind == -1) {
				memcpy(airports[size], p.destination, sizeof(p.destination));
				weights[size] += p.weight;
				sizes[size] = 1;				
				size++;
			}
			else {
				weights[ind] += p.weight;
				sizes[ind]++;		
			}	
		}

		for (int i = 0; i < size; i++) {
			weights[i] /= sizes[i];	
		}


		fseek(in, 0, SEEK_SET);
		
		int arg = atoi(argv[3]);
		

		while (fread(&p, sizeof(p), 1, in) == 1) {
			ind = check(airports, size, p.destination);
			if (weights[ind] >= 0 && p.weight < weights[ind] + arg && p.weight > weights[ind] - arg) {
				for (int i = 0; i < 50; i++) {
					printf("%c", p.name[i]);
				}
				printf(":");
				for (int i = 0; i < 50; i++) {
					printf("%c", p.name[i]);
				}
				printf("\n");
				weights[ind] = -1;		
			}
		}
	}
	if (argv[2][1] == 'f') {
		while (fread(&p, sizeof(p), 1, in) == 1) {
			printf("%s %s %s %d %d %s %s %d %d\n", p.name, p.surname, p.initials, p.luggage, p.weight, p.destination, p.time, p.layovers, p.children);		
		}
	}
}
