#include <stdio.h>
#include <stdbool.h>

int max(int a, int b){
    if(a > b) return a;
    else return b;
}

int min(int a, int b){
    if(a < b) return a;
    else return b;
}

int abs(int a){
    if(a >= 0) return a;
    else return -1 * a;
}

int sign(int a){
    if(a > 0) return 1;
    if(a == 0) return 0;
    if(a < 0) return -1;
}

int modulo(int a, int b){
    if (a % b == 0) return a / b;
    else if (a * b > 0) return a % b;
    else return a - (a/b-1) * b;
    }

int main(){
    int i = 20, j = 0, l = 11;
    bool check = false;

    for(int k = 0; k < 50; k++){
        if(i >= -10 && j >= 0 && j <= -i+10){
            printf("Hit\n steps:%d i=%d j=%d l=%d\n", k, i, j, l);
            check = true;
            break;
        }

        i = modulo((i - k)*max(j, l) + (j - k)*min(i, l) + (l - k)*max(i, j), 23);
        j = modulo(-((i - k)*min(j, l) + (j-k)+max(i, l) + (l - k)*min(i, j)), 27);  
        l = abs(i + j - l - k)*sign(i - j + l - k);
    }
    if(!check){
        if(i >= -10 && j >= 0 && j <= -i+10){
                printf("Hit\n steps:%d i=%d j=%d l=%d\n", 50, i, j, l);
                check = true;
            }
    }

    if(!check) printf("Miss\n steps:%d i=%d j=%d l=%d\n", 51, i, j, l);
}