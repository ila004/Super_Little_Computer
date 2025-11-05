#include "calc.h"
#include <stdlib.h>
#include <stdio.h>

long operation_lowPriority(char** s);
long parenthesis_highPriority(char** s);
long operation_highPriority(char** s);

void skip_spaces(char** s) {
	while (**s == ' ' || **s == '\t') {
		(*s)++;
	}
}

long parenthesis_highPriority(char** s) {
	skip_spaces(s);
	if (**s == '(') {
		(*s)++;
		skip_spaces(s);
		long x = operation_lowPriority(s);
		skip_spaces(s);
		if (**s != ')') {
			fwrite("Sintax Error\n", 1, 13, stdout);
			exit(1);
		}
		else { 
			(*s)++;
			return x;
		}
	}
	else if ((**s == '-') || (**s >= '0' && **s <= '9')) {
		int y = 0, sign = 0;
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
		exit(1);
	}
	return 1;
}
long operation_highPriority(char **s) {
	skip_spaces(s);
	long x = parenthesis_highPriority(s);
	for (;;) {
		skip_spaces(s);
		if (**s == '*') {
			(*s)++;
			skip_spaces(s);
			x = x * parenthesis_highPriority(s);
			skip_spaces(s);
		}
		if (**s == '/') {
			(*s)++;
			skip_spaces(s);
			if(parenthesis_highPriority(s) == 0) {
				fwrite("Math Error\n", 1, 11, stdout);
				exit(2);
			}
			x = x / parenthesis_highPriority(s);
			skip_spaces(s);
		}
		else {
			break;
		}
	}
	return x;
}
long operation_lowPriority(char** s) {
	skip_spaces(s);
	long x = operation_highPriority(s);
	for (;;) {
		skip_spaces(s);
		if (**s == '+') {
			(*s)++;
			skip_spaces(s);
			x = x + operation_highPriority(s);
			skip_spaces(s);
		}
		if (**s == '-') {
			(*s)++;
			skip_spaces(s);
			x = x - operation_highPriority(s);
			skip_spaces(s);
		}
		else {
			break;
		}
	}
	return x;
}