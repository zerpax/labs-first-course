#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

struct Stack_item{
	struct Stack_item* next;
	char value;
};


struct Stack {
	struct Stack_item* top;
	int size;
};

void Create(struct Stack* stack){
	stack -> top = NULL;
	stack -> size = 0;
}

void Push(struct Stack* stack, char value) {
	struct Stack_item* temp = (struct Stack_item*)malloc(sizeof(struct Stack_item));
	temp -> next = NULL;
	temp -> value = value;
	temp -> next = stack -> top;
	stack -> top = temp;
	stack -> size++;
}

void Pop(struct Stack* stack) {
	struct Stack_item* temp = stack -> top;
	stack -> top = stack -> top -> next;
	stack -> size--;
	free(temp);
}

char Top(struct Stack* stack){
	if (stack != NULL) {
		return stack -> top -> value;
	}
}


struct Tree {
	char value;
	struct Tree* right;
	struct Tree* left;
};

void StackToTree(struct Stack* stack, struct Tree* tree) {
	if (stack -> top != NULL) {
		tree -> value = Top(stack);
		Pop(stack);
		if (!isdigit(tree -> value)) {
			tree -> right = (struct Tree*)malloc(sizeof(struct Tree));
			tree -> left = (struct Tree*)malloc(sizeof(struct Tree));
			StackToTree(stack, tree -> right);
			StackToTree(stack, tree -> left);
		}
	}
}

void TreePrint(struct Tree *tree, int depth) {
	if (tree -> left != NULL) { 
		TreePrint(tree -> left, depth + 1);
	}
	printf("%*c%c\n", depth * 3, ' ', tree -> value);
	if (tree -> right != NULL) {
		TreePrint(tree -> right, depth + 1);	
	}
}	

bool Search(struct Tree* tree, char value){
	if (tree -> left != NULL) {
	        if (tree -> left -> value == value) {
			free(tree -> left);
			tree -> left = NULL;
			
			struct Tree* temp = tree -> right;
			tree -> value = temp -> value;
			tree -> right = temp -> right;
			tree -> left = temp -> left;
			free(temp);
			return true;
		}
		else {
			if(Search(tree -> left, value)) {
				return true;
			}
		}
	}
	if (tree -> right != NULL) {
		if (tree -> right -> value == value) {
			free(tree -> right);
			tree -> right = NULL;

			struct Tree* temp = tree -> left;
                        tree -> value = temp -> value;
                        tree -> right = temp -> right;
                        tree -> left = temp -> left;
                        free(temp);
			return true;
		}
		else { 
			if(Search(tree -> right, value)) {
				return true;
			}
			
        	}
	}
	return false;
}

void Compare(struct Tree* tree, struct Tree* comp_tree) {
	if (tree -> left != NULL) {
                if (isdigit(tree -> left -> value) && Search(comp_tree, tree -> left -> value)) {
                        free(tree -> left);
                        tree -> left = NULL;

                        struct Tree* temp = tree -> right;
                        tree -> value = temp -> value;
                        tree -> right = temp -> right;
                        tree -> left = temp -> left;
                        free(temp);
                        Compare(tree, comp_tree);
                }
                else {
                        Compare(tree -> left, comp_tree);
                }
        }
        if (tree -> right != NULL) {
                if (isdigit(tree -> right -> value) && Search(comp_tree, tree -> right -> value)) {
                        free(tree -> right);
                        tree -> right = NULL;

                        struct Tree* temp = tree -> left;
                        tree -> value = temp -> value;
                        tree -> right = temp -> right;
                        tree -> left = temp -> left;
                        free(temp);
                        Compare(tree, comp_tree);
                }
                else {
                        Compare(tree -> right, comp_tree);
                }
        }
}

void Reduce(struct Tree* tree) {
	struct Tree* left = tree -> left;
	struct Tree* right = tree -> right;
	Compare(left, right);
	if (isdigit(left -> value) && Search(right, left -> value)) {
		left -> value = '1';
	}
	if (isdigit(right -> value) && Search(left, right -> value)) {
		right -> value = '1';
	}
	if (isdigit(right -> value) && isdigit(left -> value) && right -> value == left -> value) {
		right -> value = '1';
		left -> value = '1';
	}
}



int main(){
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
	struct Stack* output = (struct Stack*)malloc(sizeof(struct Stack));
	struct Tree* tree = (struct Tree*)malloc(sizeof(struct Tree));

	Create(stack);
	Create(output);
	
	
	int c = getchar();

	while (c != EOF) {
		if (isdigit(c)) {
			Push(output, c);
		}
		else if (c == ')') {
			while (Top(stack) != '(') {
				Push(output, Top(stack));
				Pop(stack);
			}
			Pop(stack);
		}
		else if (c == '/' || c == '*') {
			Push(stack, c);
		}
		else if (c == '+' || c == '-') {
			while (Top(stack ) == '*' || Top(stack) == '/') {
				Push(output, Top(stack));
				Pop(stack);
			}
			Push(stack, c);
		}
		else if (c == '(') {
			Push(stack, c);
		}
		c = getchar();
	}
	while (stack -> top != NULL) {
		Push(output, Top(stack));
		Pop(stack);
	}
	StackPrint(output);
	StackToTree(output, tree);
	TreePrint(tree, 1);
	printf("-------------------------------------\n");
	Reduce(tree);
	TreePrint(tree, 1);
	
}
