all: hanoi

hanoi: hanoi.o primlib.o
	gcc -fsanitize=address -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o: 
	gcc -fsanitize=address -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

primlib.o: primlib.c primlib.h

hanoi.o: hanoi.c primlib.h

clean:
	-rm primlib.o hanoi.o hanoi
