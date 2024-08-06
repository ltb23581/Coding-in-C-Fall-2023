HEAD_NAME = head
WC_NAME = wc
FLAGS = -Wall -pedantic-errors

all: $(HEAD_NAME) $(WC_NAME)

$(HEAD_NAME): $(HEAD_NAME).c
	gcc -o $(HEAD_NAME) $(FLAGS) $(HEAD_NAME).c

$(WC_NAME): $(WC_NAME).c
	gcc -o $(WC_NAME) $(FLAGS) $(WC_NAME).c

run_head: $(HEAD_NAME)
	./$(HEAD_NAME) -c 7 file1.txt -

run_wc: $(WC_NAME)
	./$(WC_NAME) -c -lw file1.txt - file2.txt

clean:
	rm -f $(HEAD_NAME) $(WC_NAME)
