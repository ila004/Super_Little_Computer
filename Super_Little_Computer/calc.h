#if !defined CALC_H
#define CALC_H
long long operation_lowPriority(char** s, int* error);
long long parenthesis_highPriority(char** s, int* error);
long long operation_highPriority(char** s, int* error);
void skip_spaces(char**s);

#endif //CALC_H
