PATH=cat.c -o s21_cat
CC=gcc
all: s21_cat

s21_cat:
	$(CC) $(PATH)

check:
	clang-format -n *.c

rebuild: clean all

clean:
	rm -rf s21_cat