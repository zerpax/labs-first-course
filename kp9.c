#include <stdio.h>
#include <stdbool.h>

typedef struct Entry{
	int key[4];
	char value[50];
} Entry;

void Print(Entry* a, int n) {
	for (int i = 0; i < n; i++) {
                for (int j = 0; j < 4; j++) {
                        printf("%d ", a[i].key[j]);
                }
		//printf("%d ", a[i].key);
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

bool Qgt (int* a, int* b) {
	for (int i = 0; i < 4; i++) {
		if (a[i] > b[i]) {
			return true;
		}
		if (a[i] < b[i]) {
			return false;
		}
	}
	return false;
}

bool Qeq(int* a, int* b) {
        for (int i = 0; i < 4 ; i++) {
                if (a[i] != b[i]) {
                        return false;
                }
        }
        return true;
}



char* Search(Entry *a, int size, int* x) {
	int R = size;
	int L = -1;
	while (R - L > 1) {
		//printf("%d %d\n", R, L);
		if (Qgt(x, a[(R + L) / 2].key)) {
			L = (R + L) / 2; 
		}
		else {
			R = (R + L) / 2;
		}
	}
	if (Qeq(x, a[R].key)) {
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
		while (Qgt(a[i].key, pivot.key)/*a[i].key > pivot.key*/ && i <= size - right_size - 1) {
		
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
		//scanf("%d %[^\n]value", &a[i].key, a[i].value);
		scanf("%d %d %d %d %[^\n]value", &a[i].key[0], &a[i].key[1], &a[i].key[2], &a[i].key[3], a[i].value);
	}
	Print(a, n);

	Sort(a, n);
	
	printf("---------------------\n");
	Print(a, n);
	printf("---------------------\n");	
	
	int m;
       	scanf("%d", &m);	
	for (int i = 0; i < m; i++) {
		int key[4];
		scanf("%d %d %d %d", &key[0], &key[1], &key[2], &key[3]);
		printf("%s\n", Search(a, n, key));
	}
}
