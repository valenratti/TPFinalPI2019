COMPILER=gcc
OUTPUT_FILE=subte
FILES=main.c getInfo.c subteADT.c queries.c
FLAGS=-pedantic -std=c99 -Wall -fsanitize=address
all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) $(FLAGS)
clean:
	rm $(OUTPUT_FILE)