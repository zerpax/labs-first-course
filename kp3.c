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
	long double e = MachineEpsilon();
	for (double x = START; x <= END; x += STEP) {
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
		double bi = (1 + x) * exp(-1*x);
		printf("%Lf %f %d\n", taylor, bi, it);
	}
}


