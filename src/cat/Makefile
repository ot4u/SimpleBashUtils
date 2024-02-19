CC=gcc
FLAGS=-Wall -Werror -Wextra
all: s21_cat

s21_cat:
	$(CC) $(FLAGS) cat.c -o s21_cat

check:
	clang-format -i *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

cat_test:
	bash cat_test.sh

clean:
	rm -rf s21_cat
	rm -rf test/s21_cat
	rm -rf test/cat_res
	rm -rf test/s21_res

rebuild: clean all