#include "calc.h"
#include <stdlib.h>
#include <stdio.h>

long long operation_lowPriority(char** s, int* error);
long long parenthesis_highPriority(char** s, int* error);
long long operation_highPriority(char** s, int* error);

void skip_spaces(char** s) {
	while (**s == ' ' || **s == '\t') {
		(*s)++;
	}
}

long long parenthesis_highPriority(char** s, int* error) {
	if(*error != 0){
		return 0;
	}
	skip_spaces(s);
	if (**s == '(') {
		(*s)++;
		skip_spaces(s);
		long long x = operation_lowPriority(s, error);
		if(*error != 0){
			return 0;
		}
		skip_spaces(s);
		if (**s != ')') {
			fwrite("Sintax Error\n", 1, 13, stdout);
			*error = 1;
			return 0;
		}
		else{
			(*s)++;
			return x;
		}
	}
	else if ((**s == '-') || (**s >= '0' && **s <= '9')) {
		long long y = 0;
		int sign = 0;
		char* t = *s;
		if (*t == '-') {
			sign = 1;
			t++;
		}
		while (*t >= '0' && *t <= '9') {
			y = y * 10 + (*t - '0');
			t++;
		}
		*s = t;
		if(sign == 1){
			return -y;
		}
		else {
			return y;
		}
	}
	else {
		fwrite("Sintax Error\n", 1, 13, stdout);
		*error = 1;
		return 0;
	}
	return 0;
}
long long operation_highPriority(char **s, int* error) {
	if(*error != 0){
		return 0;
	}
	skip_spaces(s);
	long long x = parenthesis_highPriority(s, error);
	if(*error != 0){
		return 0;
	}
	for (;;) {
		skip_spaces(s);
		if (**s == '*') {
			(*s)++;
			skip_spaces(s);
			long long y = parenthesis_highPriority(s, error);
			if(*error != 0){
				return 0;
			}
			x = x * y;
			skip_spaces(s);
		}
		if (**s == '/') {
			(*s)++;
			skip_spaces(s);
			long long k = parenthesis_highPriority(s, error);
			if(*error != 0){
				return 0;
			}
			if(k == 0) {
				fwrite("Math Error\n", 1, 11, stdout);
				*error = 1;
				return 0;
			}
			x = x / k;
			skip_spaces(s);
		}
		else {
			break;
		}
	}
	return x;
}
long long operation_lowPriority(char** s, int* error) {
	if(*error != 0){
			return 0;
	}
	skip_spaces(s);
	long long x = operation_highPriority(s, error);
	if(*error != 0){
			return 0;
	}
	for (;;) {
		skip_spaces(s);
		if (**s == '+') {
			(*s)++;
			skip_spaces(s);
			long long y = operation_highPriority(s, error);
			if(*error != 0){
				return 0;
			}
			x = x + y;
			skip_spaces(s);
		}
		if (**s == '-') {
			(*s)++;
			skip_spaces(s);
			long long k = operation_highPriority(s, error);
			if(*error != 0){
				return 0;
			}
			x = x - k;
			skip_spaces(s);
		}
		else {
			break;
		}
	}
	return x;

}
