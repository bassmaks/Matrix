CFILES = $(wildcard s21*.c)
OBJ = $(patsubst %.c, %.o, $(CFILES))
TARGET = s21_matrix
CHECK:=$(shell pkg-config --cflags --libs check)
FLAG_COV = --coverage
CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
S21_MATRIX=-L. s21_matrix.a
DEBUG =-g
CTESTFLAGS=-lcheck -lm -lpthread 
TEST = tests.c
LIBRARY = s21_matrix.a


all: clean $(LIBRARY) test gcov_report

# $(TARGET): s21_matrix.o
# 	$(CC) s21_matrix.o -o $(TARGET)

# s21_matrix.o : s21_matrix.c
# 	$(CC) $(DEBUG) -c s21_matrix.c

$(LIBRARY): s21_matrix.h $(CFILES)
	$(CC) $(FLAGS) -c $(CFILES)
	ar rc $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)
	rm -f $(OBJ)

clean:
	rm -rf *.o *.a test *.gcda *.gcno *.info coverage

style:
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h

checkstyle:
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h

de: $(TARGET)
		
gcov_report: $(LIBRARY)
	$(CC) $(FLAG_COV) $(FLAGS) $(CTESTFLAGS) $(TEST) s21*.c -o test $(CHECK) $(S21_MATRIX)
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o coverage test.info
	open coverage/index.html 

test: $(LIBRARY)
	$(CC) $(FLAG_COV) $(FLAGS) $(CTESTFLAGS) $(TEST) s21*.c -o test $(CHECK) $(S21_MATRIX)
	./test