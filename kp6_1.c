#include <stdio.h>
#include <string.h>
#include "person.h"



int readperson(person *p) {
	return scanf("%[^;];%[^;];%[^;];%d;%d;%[^;];%[^;];%d;%d\n", p -> name, p -> surname, p -> initials, &p -> luggage, &p -> weight, p -> destination, p -> time, &p -> layovers, &p -> children) == 9;
}

int main(int argc, char* argv[]) {
	person p;
	FILE *out = fopen(argv[1], "wb");
	if (!out) {
		perror("Can't open file");
	return 2;
	}
	
	while (readperson(&p)) {
		fwrite(&p, sizeof(p), 1, out);
	}
	return 0;
}
