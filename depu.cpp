#include<stdio.h>
#include<stdlib.h>

int f(int a, int * pnt){
	printf("%d %d", a, *pnt);
	a += 5;
	*pnt += 4;
	printf("%d", a);
	return a;
}

int main(){
	
	int x = 57;
	int y = 99;
	char vet[12] = "abcdefghij";
	
	printf("%d %d", x, f(x, &x));
	
		
	printf("%d %d %s", x, y, vet);
	
}
