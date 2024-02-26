CC=gcc
FLAGS=-Wall -Werror -Wextra

all: s21_cat

s21_cat:
	$(CC) $(FLAGS) cat.c -o s21_cat

check:
	clang-format -i *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

cat_test: s21_cat
	bash cat_test.sh

clean:
	rm -rf s21_cat
	rm -rf s21_cat.log
	rm -rf cat.log

rebuild: clean all