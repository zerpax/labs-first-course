#include <stdio.h>

enum elements{barrier = 0, pog = 1, lul = 2, kek = 3};

typedef struct List {
	enum elements list[50];
} List;

List Init() {
	List list;
	list.list[0] = barrier;
	return list;
}

int Size(List list) {
	int ind = 0;
	while (list.list[ind] != barrier) {
		ind++;
	}
	return ind;
}

void Print(List list) {
	int i = 0;
	while (list.list[i] != barrier) {
		printf("%d ", list.list[i]);
		i++;
	}
	printf("%d\n", list.list[i]);
}

int Abs(int a) {
	return a > 0 ? a : -a;
}

void Insert(List *list, int pos, enum elements value) {
	int size = Size(*list);
	if (Abs(pos) > size){
		return;
	}
	else {
		if (pos < 0) {
			pos = size - pos;
		}
		int ind = pos;
		while ((*list).list[ind] != barrier) {
			enum elements temp = (*list).list[ind];
			(*list).list[ind] = value;
			value = temp;
			ind++;
		}
		(*list).list[ind] = value;
	}
}

void Delete(List *list, int pos) {
	int size = Size(*list);
        if (pos > size - 1){
                return;
        }
        else {
                int ind = size-1;
		enum elements value = (*list).list[size];
                while (ind != pos) {
                        enum elements temp = (*list).list[ind];
			(*list).list[ind] = value;
			value = temp;
                        ind--;
                }
                (*list).list[ind] = value;
        }

}

void Funk(List* list, enum elements value, int num) {
	int size = Size(*list);
	if (size < num) {
		for (int i = size; i < num; i++) {
			(*list).list[i] = value;
		}
		(*list).list[num + 1] = barrier;
	}
}

int main() {
	List list = Init();
	Insert(&list, 0, pog);
	Insert(&list, 0, pog);
	Print(list);
	Delete(&list, 0);
	Print(list);
	Funk(&list, kek, 10);
	Print(list);
}
