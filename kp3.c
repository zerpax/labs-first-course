//(1+x)e^-x
//[0, 1]
#include <stdio.h>
#include <math.h>

#define START 0.0
#define END 1.0
#define STEP 0.01

long double MachineEpsilon() {
    long double e = 1.0l;
    while (1.0l + e * 0.5l > 1.0l) {
        e *= 0.5l;
    }
    return e;
}

long double Abs(long double a){
	return a < 0 ? -1 * a : a; 
}

int main(){

	for (int i = 0; i < 76; ++i) {
		printf("-");
	}
	printf("\n");
	printf("| x");
	for (int i = 0; i < 5; ++i) {
		printf(" ");
	}
	printf("| част. сумма ряда");
	for (int i = 0; i < 7; ++i) {
		printf(" ");
	}
	printf("| значение функции");
	for (int i = 0; i < 7; ++i) {
	       printf(" ");
	}
	printf("| число итераций |\n");
	for (int i = 0; i < 76; ++i) {
		printf("-");
	}
	printf("\n");

	long double e = MachineEpsilon();
	for (long double x = START; x <= END; x += STEP) {
		long double taylor = 0;
		long double xn = x;
		long double fact = 1;
		int sign = 1;
		long double elem = 1;
		int it = 0;
		for (int n = 2; n < 100 && Abs(elem) > e; ++n) {
			taylor += elem;
			xn *= x;
			fact *= n+1;
			sign *= -1;
			elem = sign * xn * (n - 1) / fact;
			it++;
		}
		long double bi = (1 + x) * exp(-1 * x);
		printf("| %.3Lf | %.20Lf | %.20Lf | %d", x, taylor, bi, it);
		for (int i = log10(it); i < 14; ++i) {
			printf(" ");
		}
		printf("|\n");
	}
	for (int i = 0; i < 76; ++i) {
		printf("-");
	}
}


