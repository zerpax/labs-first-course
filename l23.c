#include <stdio.h>
#include <stdlib.h>

struct Tree {
	int value;
	struct Tree* right;
	struct Tree* left;
};

void Print(struct Tree *tree, int depth) {
	if (tree -> left != NULL) { 
		Print(tree -> left, depth + 1);
	}
	printf("%*c%d\n", depth * 3, ' ', tree -> value);
	if (tree -> right != NULL) {
		Print(tree -> right, depth + 1);	
	}
}	

void Add(struct Tree *tree, int value) {
	if (value > tree -> value) {
		if (tree -> right == NULL) {
			tree -> right = (struct Tree*)malloc(sizeof(struct Tree));
			tree -> right -> value = value;
		}
		else {
			Add(tree -> right, value);
		}
	}
	if (value < tree -> value) {
		if (tree -> left == NULL) {
			tree -> left = (struct Tree*)malloc(sizeof(struct Tree));
			tree -> left -> value = value;
			}
		else {
			Add(tree -> left, value);
		}
	}
}

void Rm(struct Tree *tree, int value) {
	if (value > tree -> value) {
		Rm(tree -> right, value);
	}
	else if (value < tree -> value) {
		Rm(tree -> left, value);
	}
	else {
		if (tree -> right != NULL) {
			tree -> value = tree -> right -> value;
			if (tree -> right -> right != NULL || tree -> right -> left != NULL) {
				Rm(tree -> right, tree -> right -> value);
			}
			else {
				tree -> right = NULL;
				free(tree -> right);
			}
		}
		else if (tree -> left != NULL) {
			tree -> value = tree -> left -> value;
			if (tree -> left -> right != NULL || tree -> left -> left != NULL) {
				Rm(tree -> left, tree -> left -> value);	
			}
			else {
				tree -> left = NULL;
				free(tree -> left);
			}
		}
	}
}

int Depth(struct Tree *tree, int depth){
	int ld = depth, rd = depth;
	if (tree -> left != NULL) {
		ld = Depth(tree -> left, depth + 1);
	}
	if (tree -> right != NULL) {
		rd = Depth(tree -> right, depth + 1);
	}
	return rd > ld ? rd : ld;
}

int main(){
	struct Tree *tree = (struct Tree*)malloc(sizeof(struct Tree));
	tree -> value = 34;
	Add(tree, 43);
	Add(tree, 30);
	Add(tree, 33);
	Add(tree, 4);
	Add(tree, 5);
	Add(tree, 3);
	Print(tree, 1);
	int d = Depth(tree, 0);
	printf("%d\n", d);	
	Rm(tree, 5);
	Rm(tree,34);
	Print(tree, 1);
	d = Depth(tree, 0);
	printf("%d\n", d);	
	free(tree);
}
