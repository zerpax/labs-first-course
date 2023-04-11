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

bool Equal(struct Tree* tree, struct Tree* comp_tree) {
        bool left = true, right = true;
        if (tree -> left != NULL && comp_tree -> left != NULL) {
                left = Equal(tree -> left, comp_tree -> left);
        }
        if (tree -> right != NULL && comp_tree -> right != NULL) {
                right = Equal(tree -> right, comp_tree -> right);
        }
        //printf("%c %c\n", tree -> value, comp_tree -> value);
        return (tree -> value == comp_tree -> value) & left & right;
}

void Delete(struct Tree* tree) {
	if (tree -> left != NULL) {
                Delete(tree -> left);
        }
        if (tree -> right != NULL) {
                Delete(tree -> right);
        }
	free(tree);
}

bool Search(struct Tree* comp_tree, struct Tree* tree){
	//TreePrint(tree -> left, 1);
	//TreePrint(comp_tree, 1);
	//printf("-------------------------------------\n");
	if (tree -> left != NULL && tree -> value != '+' && tree -> value != '-') {
	        if (Equal(tree -> left, comp_tree)) {
			//TreePrint(comp_tree, 1);
			//TreePrint(tree, 1);
			Delete(tree -> left);
			tree -> left = NULL;

			struct Tree* temp = tree -> right;
			tree -> value = temp -> value;
			tree -> right = temp -> right;
			tree -> left = temp -> left;
			free(temp);
			return true;
		
		}
		else if(Search(comp_tree, tree -> left)) {
			return true;
		}
	}
	if (tree -> right != NULL && tree -> value != '+' && tree -> value != '-') {
	//	TreePrint(comp_tree, 1);
		if (Equal(tree -> right, comp_tree)) {
			Delete(tree -> right);
			tree -> right = NULL;

			struct Tree* temp = tree -> left;
			tree -> value = temp -> value;
			tree -> right = temp -> right;
			tree -> left = temp -> left;
			free(temp);
			return true;
		}
		else if(Search(comp_tree, tree -> right)) {
				return true;
        	}
	}
	return false;

}

void Compare(struct Tree* tree, struct Tree* comp_tree) {
		
	//TreePrint(tree -> right, 1);
	//printf("%d, %c  ",tree -> left != NULL && tree -> value != '/', tree -> value);
	if (tree -> left != NULL && tree -> value != '+' && tree -> value != '-') {
                if (Search(tree -> left, comp_tree)) {
                        Delete(tree -> left);
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
        if (tree -> right != NULL && tree -> value != '+' && tree -> value != '-') {
                if (Search(tree -> right, comp_tree)) {
                        Delete(tree -> right);
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
	struct Tree* right = tree -> right;
	struct Tree* left = tree -> left;
	if (Search(right, left)) {
		right -> value = '1';
		free(right -> right);
		free(right -> left);
		right -> right = NULL;
		right -> left = NULL;
	}
	if (Search(left, right)) {
                left -> value = '1';
		free(left -> right);
		free(left -> left);
                left -> right = NULL;
                left -> left = NULL;
        }

	if (Equal(left, right)) {
		tree -> value = '1';
		tree -> right = NULL;
		tree -> left = NULL;
	}
	Compare(left, right);
}


void DivCheck(struct Tree* tree){
	if (tree -> left != NULL) {
		DivCheck(tree -> left);
	}
	if (tree -> value == '/') {
		Reduce(tree);
	}
	if (tree -> right != NULL) {
		DivCheck(tree -> right);
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
			while (stack -> top != NULL && Top(stack) != '(' && (Top(stack) == '*' || Top(stack) == '/')) {
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
	
	StackToTree(output, tree);
	TreePrint(tree, 1);
	printf("-------------------------------------\n");
	DivCheck(tree);
	TreePrint(tree, 1);
	//printf("%d", Equal(tree -> left, tree -> right));
}
