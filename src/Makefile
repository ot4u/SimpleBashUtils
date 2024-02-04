PATH=cat/cat.c cat/cat_functions.c -o cat/s21_cat
FLAGS=gcc
all: s21_cat

s21_cat:
	$(FLAGS) $(PATH)
rebuild: clean all

start:
	cat/./s21_cat
clean:
	rm -rf cat/s21_cat