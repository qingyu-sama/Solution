#include <stdio.h>

int main() {
	int i = 1;
	if (1 == 1 || (i = 2) == 2) printf("%d", i);
}