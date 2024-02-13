CC=gcc
FLAGS=-Wall -Werror -Wextra
all: s21_cat


s21_cat:
	$(CC) $(FLAGS) cat.c -o s21_cat

check:
	clang-format -i *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf s21_cat

rebuild: clean all