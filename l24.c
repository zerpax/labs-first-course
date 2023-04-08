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
	//bool type; //0 - operator 1 - integer
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

void Add_num(struct Tree *tree, int value) {
	if (value > tree -> value) {
		if (tree -> right == NULL) {
			tree -> right = (struct Tree*)malloc(sizeof(struct Tree));
			tree -> right -> value = value;
		}
		else {
			Add_num(tree -> right, value);
		}
	}

}

void Add_char(struct Tree *tree, char value) {
        if (value > tree -> value) {
                if (tree -> right == NULL) {
                        tree -> right = (struct Tree*)malloc(sizeof(struct Tree));
                        tree -> right -> value = value;
                }
                else {
                        Add_char(tree -> right, value);
                }        struct Tree* right;

        }

}


void Delete(struct Tree *tree, int value) {
	if (tree -> right != NULL) {
		tree -> value = tree -> right -> value;
		if (tree -> right -> right != NULL || tree -> right -> left != NULL) {
			Delete(tree -> right, tree -> right -> value);
		}
		else {
			tree -> right = NULL;
			free(tree -> right);
		}
	}
	else if (tree -> left != NULL) {
		tree -> value = tree -> left -> value;
		if (tree -> left -> right != NULL || tree -> left -> left != NULL) {
			Delete(tree -> left, tree -> left -> value);	
		}
		else {
			tree -> left = NULL;
			free(tree -> left);
		}
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
			return Search(tree -> left, value);
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
			return Search(tree -> right, value);
        	}
	}

}

void Compare(struct Tree* tree, struct Tree* comp_tree) {
	if (tree -> left != NULL) {
                if (Search(comp_tree, tree -> left -> value)) {
                        free(tree -> left);
                        tree -> left = NULL;

                        struct Tree* temp = tree -> right;
                        tree -> value = temp -> value;
                        tree -> right = temp -> right;
                        tree -> left = temp -> left;
                        free(temp);
                }
                else {
                        Compare(tree -> left, comp_tree);
                }
        }


        if (tree -> right != NULL) {
                if (Search(comp_tree, tree -> right -> value)) {
                        free(tree -> right);
                        tree -> right = NULL;

                        struct Tree* temp = tree -> left;
                        tree -> value = temp -> value;
                        tree -> right = temp -> right;
                        tree -> left = temp -> left;
                        free(temp);
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
	/*	
	while(output -> top != NULL){
		printf("%c", Top(output));
		Pop(output);
	}
	*/
	StackToTree(output, tree);
	Reduce(tree);
	TreePrint(tree, 1);
	//TreePrint(tree, 1);
	//Stack_print(output);	
	
	//printf("%c",stack -> value);
	
}
