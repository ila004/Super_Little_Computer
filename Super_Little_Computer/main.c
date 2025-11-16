#include <stdlib.h>
#include <stdio.h>
#include "calc.h"
int main(void) {
	size_t l_len = 0;
	char* l = NULL;
	long long res = 0;
	while (getline(&l, &l_len, stdin) != -1) {
		int error = 0;
		int sign = 0, count = 0;
		char* str = l;
		res = operation_lowPriority(&str, &error);
		if(error != 0){
			continue;
		}
		if (res < 0) {
			sign = 1;
			res = -res;
		}
		long long n = res;
		while (n > 0) {
			n = n / 10;
			count++;
		}
		count = count + 1 + sign;
		char* s = malloc(sizeof(char) * count);
		if (!s) {
			fwrite("Error\n", 1, 6, stderr);
			continue;
		}
		s[count - 1] = '\0';
		for (int i = count - 2; i >= 0; i--) {
			if (res > 0) {
				s[i] = (res % 10) + '0';
				res /= 10;
			}
			else if ((sign == 1) && (i == 0)) {
				s[i] = '-';
			}
		}
		fwrite(s, 1, count - 1, stdout);
		fwrite("\n", 1, 1, stdout);
		free(s);
	}
	free(l);
	return 0;
}
