#include <stdio.h>
#include <stdlib.h>

int Pow(int a, int b) {
	int res = 1;
	for (int i = 0; i < b; i++) {
		res *= a;
	}
	return res;
}

long long Shift(long long n) {
    long long w = 1, z = 1;
    int zeros = 0, digs = 0;
    while (n % w != n) {
	    w *= 10;
	    digs++;
	    if (n % (z*10) == 0) {
		    z *= 10;	
    		    zeros++;
	    }
    }	
    long long half = Pow(10, (digs - zeros) / 2);
    n = (n - n % (z * half) + (n / z % half));
    return n;
}



int main() {
	long long n = 0;
	int sign = 1;	
	char c;
	c = getchar();
	if (c == '-') {
		sign = -1;
		c = getchar();
	}
	while (c != EOF) {
		if (c == '\n') {
			n = Shift(n);
			n *= sign;
			printf("%lld\n", n);
			n = 0;
		} else if (c == '-') {
			sign = -1;
		} else {
			n *= 10;
			n += (int)(c - '0');
		} 
		c = getchar();
	}
}	
