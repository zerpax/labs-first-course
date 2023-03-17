#include <stdio.h>
#include <stdlib.h>

struct List {
	int value;
	struct List *right;
	struct List *left;
};

void Add(struct List *list, int value) {
	if (list -> right != NULL) {
		Add(list -> right, value);
	}
	else {
		list -> right = (struct List*)malloc(sizeof(struct List));
		list -> right -> value = value;
		list -> right -> left = list;
	}
}

void Print(struct List *list){
	printf("%d ", list -> value);
	if (list -> right != NULL){
		Print(list -> right);
	}
}

void Sort(struct List *list) {
	struct List *copy = list;
	while ((copy -> left != NULL) && (copy -> value < copy -> left -> value)) {
		int temp = copy -> value;
		copy -> value = copy -> left -> value;
		copy -> left -> value = temp;
		copy = copy -> left;
	}
	if (list -> right != NULL) {
		Sort(list -> right);
	}
}

int main() {
	struct List *list = (struct List*)malloc(sizeof(struct List));
	list -> value = 8;
	Add(list, 4);
	Add(list, 9);
	Add(list, 1);
	Add(list, -1);
	Sort(list);
	Print(list);
	
	free(list);
}
