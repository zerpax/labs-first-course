#include <stdio.h>
#include <stdbool.h>

typedef struct Entry{
	int key;
	char value[50];
} Entry;

void Print(Entry* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i].key);
                printf("%s\n", a[i].value);
        }

}

bool Equal(char* a, char* b){
	for (int i = 0; i < 50; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}


char* Search(Entry *a, int size, int x) {
	int R = size;
	int L = -1;
	while (R - L > 1) {
		if (x > a[(R + L) / 2].key) {
			L = (R + L) / 2; 
		}
		else {
			R = (R + L) / 2;
		}
	}
	if (x == a[R].key) {
		return a[R].value;
	}
	else {
		printf("no such key");
		return "";
	}
}



void Sort(Entry* a, int size){
	if (size < 2) {
		return;
	}
	int pivot_index = size/2;
	Entry pivot = a[pivot_index];
	int right_size  = 0;
	
	for (int i = 0; i < size - right_size; i++) {
		while (a[i].key > pivot.key && i <= size - right_size - 1) {
		
			Entry temp = a[i];
			a[i] = a[size - right_size - 1];
			a[size - right_size - 1] = temp;
			
			if (size - right_size - 1 == pivot_index) {
				pivot_index = i;
			}

			right_size++;
		}
	}
	
	Entry temp = a[pivot_index];
        a[pivot_index] = a[size - right_size - 1];
	a[size - right_size - 1] = temp;

	Sort(a, size - right_size - 1);
	Sort(&a[size - right_size], right_size);
}


int main() {
	int n;
	scanf("%d", &n);
	Entry a[50];
	for (int i = 0; i < n; i++) {
		scanf("%d %[^\n]value", &a[i].key, a[i].value);
	}
	Print(a, n);

	Sort(a, n);
	
	printf("---------------------\n");
	Print(a, n);
	printf("---------------------\n");	
	
	int m;
       	scanf("%d", &m);	
	for (int i = 0; i < m; i++) {
		int key;
		scanf("%d", &key);
		printf("%s\n", Search(a, n, key));
	}
}
