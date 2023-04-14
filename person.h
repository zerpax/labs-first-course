#ifndef __person_h__
#define __person_h__
typedef struct {
	char name[50];
	char surname[50];
	char initials[2];
	int luggage;
	int weight;
	char destination[50];
	char time[6];
	int layovers;
	int children;
} person;
#endif
