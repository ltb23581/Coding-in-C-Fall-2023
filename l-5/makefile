NAME = cat
FLAGS = -Wall -pedantic-errors

cl: cat.o
	gcc -o $(NAME) cat.o

cat.o: cat.c
	gcc -c $(FLAGS) cat.c

run: cl
	./$(NAME)

clean:
	rm -f $(NAME) *.o

