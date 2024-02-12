CC=gcc
FLAGS=-Wall -Werror -Wextra
all: s21_grep


s21_grep:
	$(CC) $(FLAGS) grep.c -o s21_cat

check:
	clang-format -i *.c *.h

clean:
	rm -rf s21_grep

rebuild: clean all