game: main.c
	gcc -std=gnu99 $^ -o $@ -lm -lncurses
