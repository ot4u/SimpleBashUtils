CC=gcc
FLAGS=-Wall -Werror -Wextra
all: s21_grep


s21_grep:
	$(CC) $(FLAGS) grep.c -o s21_grep

grep_test:
	bash grep_test.sh

check:
	clang-format -i *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf s21_grep
	rm -rf test/grep.log
	rm -rf test/s21_grep
	rm -rf test/s21_grep.log
	
rebuild: clean all