#include <stdio.h>
#include <math.h>

long double MachineEpsilon(){
    long double e = 1.0l;
    while (1.0l + e * 0.5l > 1.0l) {
        e *= 0.5l;
    }
    return e;
}

long double Abs(long double x){
	return x >= 0 ? x : -1 * x;
}

long double D1(long double x){
	 return 0.6 * pow(3.0, x) - 2.3 * x - 3.0;
}

long double D2(long double x){
	return pow(M_E, x) + sqrt(1 + pow(M_E, 2 * x)) - 2;
}

long double I1(long double x){
	return sqrt(log(1 + x) + 3);
}

long double I2(long double x){
	return log(x) + 1.8;
}


long double N1(long double x){
	return x - (3 * log(x) * log(x) + 6 * log(x) - 5)/(6 * (log(x) + 1) /x);
}

long double N2(long double x){
	return 2 * x * sin(x) - cos(x);
}

void Dic1(){
	long double eps = MachineEpsilon();

	long double l = 2.0l, r = 3.0l;	
	long double x = (r + l) * 0.5l;
	while (r - l > 2 * eps) {	
		if (D1(l) * D1((l + r) * 0.5l) > 0) {
			l = (r + l) * 0.5l;
		}
		else
			r = (r + l) * 0.5l;
	}
	printf("0.6 * 3*x - 2.3x - 3 = 0: x = %Lf\n", (r + l) * 0.5l);
}

void Dic2(){
	long double eps = MachineEpsilon();

	long double l = -1.0l, r = 0.0l;	
	long double x = (r + l) * 0.5l;
	while (r - l > 2 * eps) {	
		if (D2(l) * D2((l + r) * 0.5l) > 0) {
			l = (r + l) * 0.5l;
		}
		else
			r = (r + l) * 0.5l;
	}
	printf("e^x + sqrt(1 + e^2x - 2 = 0 : x = %Lf\n", (r + l) * 0.5l);
}

void It1(){
	long double eps = MachineEpsilon();
	long double l = 2.0l, r = 3.0l;
	long double last = (r + l) / 2;
	long double x = I1(last);
	while (Abs(x - last) >= eps) {
		last = x;
		x = I1(last);
	}
	printf("x^2 - ln(1 + x) -3 = 0 : x = %Lf\n", x);
}

void It2(){
	long double eps = MachineEpsilon();
	long double l = 2.0l, r = 3.0l;
	long double last = (r + l) / 2;
	long double x = I2(last);
	while (Abs(x - last) >= eps) {
		last = x;
		x = I2(last);
	}
	printf("ln(x) - x + 1.8 = 0 : x = %Lf\n", x);
}

void Newt1(){
	long double eps = MachineEpsilon();
	long double l = 1.0l, r = 3.0l;
	long double last = (r + l) / 2;
	long double x = N1(last);
	while (Abs(x - last) >= eps) {
		last = x;
		x = N1(last);
	}
	printf("3ln(x)^2 + 6ln(x) -5 = 0 : x = %Lf\n", x);
}

void Newt2(){
	printf("2x*sin(x) - cos(x) = 0: метод Ньютона неприменим, так как не выполняется условие сходимости функции");
}
	
int main(){
	Dic1();
	Dic2();
	It1();
	It2();
	Newt1();
	Newt2();
}
