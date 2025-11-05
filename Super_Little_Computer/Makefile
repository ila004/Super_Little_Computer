all: calculator

calculator: main.o calc.o
	gcc -Wall -Wextra -g -o calcolator main.o calc.o

main.o: main.c calc.h
	gcc -Wall -Wextra -g -c main.c

calc.o: calc.c calc.h
	gcc -Wall -Wextra -g -c calc.c

clean:
	rm -f main.o calc.o

fclean:
	rm -f calculator

re: fclean all

.PHONY: all clean fclean re