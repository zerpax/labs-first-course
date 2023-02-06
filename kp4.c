#include <stdio.h>
#include <math.h>

long double MachineEpsilon() {
    long double e = 1.0l;
    while (1.0l + e * 0.5l > 1.0l) {
        e *= 0.5l;
    }
    return e;
}

long double Abs(long double x){
	return x >= 0 ? x : -1 * x;
}

long double d1(long double x){
	 return 0.6 * pow(3.0, x) - 2.3 * x - 3.0;
}

long double d2(long double x){
	return pow(M_E, x) + sqrt(1 + pow(M_E, 2 * x)) - 2;
}

long double i1(long double x){
	return sqrt(log(1 + x) + 3);
}

long double i2(long double x){
	return log(x) + 1.8;
}


long double n1(long double x){
	return x - (3 * log(x) * log(x) + 6 * log(x) - 5)/(6 * (log(x) + 1) /x);
}


void dic1(){
	long double eps = MachineEpsilon();

	long double l = 2.0l, r = 3.0l;	
	long double x = (r + l) * 0.5l;
	while (r - l > 2 * eps) {	
		if (d1(l) * d1((l + r) * 0.5l) > 0) {
			l = (r + l) * 0.5l;
		}
		else
			r = (r + l) * 0.5l;
	}
	printf("0.6 * 3*x - 2.3x - 3 = 0: x = %Lf\n", (r + l) * 0.5l);
}

void dic2(){
	long double eps = MachineEpsilon();

	long double l = -1.0l, r = 0.0l;	
	long double x = (r + l) * 0.5l;
	while (r - l > 2 * eps) {	
		if (d2(l) * d2((l + r) * 0.5l) > 0) {
			l = (r + l) * 0.5l;
		}
		else
			r = (r + l) * 0.5l;
	}
	printf("e^x + sqrt(1 + e^2x - 2 = 0 : x = %Lf\n", (r + l) * 0.5l);
}

void it1(){
	long double eps = MachineEpsilon();
	long double l = 2.0l, r = 3.0l;
	long double last = (r + l) / 2;
	long double x = i1(last);
	while (Abs(x - last) >= eps) {
		last = x;
		x = i1(last);
	}
	printf("x^2 - ln(1 + x) -3 = 0 : x = %Lf\n", x);
}

void it2(){
	long double eps = MachineEpsilon();
	long double l = 2.0l, r = 3.0l;
	long double last = (r + l) / 2;
	long double x = i2(last);
	while (Abs(x - last) >= eps) {
		last = x;
		x = i2(last);
	}
	printf("ln(x) - x + 1.8 = 0 : x = %Lf\n", x);
}

void newt1(){
	long double eps = MachineEpsilon();
	long double l = 1.0l, r = 3.0l;
	long double last = (r + l) / 2;
	long double x = n1(last);
	while (Abs(x - last) >= eps) {
		last = x;
		x = n1(last);
	}
	printf("3ln(x)^2 + 6ln(x) -5 = 0 : x = %Lf\n", x);
}

void newt2(){
	printf("2x*sin(x) - cos(x) = 0: метод Ньютона не применим, так как не выполняется условие сходимости на данном отрезке");
}
	
int main(){
	dic1();
	dic2();
	it1();
	it2();
	newt1();
	newt2();
}
