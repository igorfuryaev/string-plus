CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
DEPS = s21_string.h
SOURCE = $(wildcard s21_*.c)
OBJ = $(patsubst %.c, %.o, $(SOURCE))
LIB = s21_string.a
TEST = test
GCOV = gcov_report
TEST_FUNC = $(SOURCE)
#TEST_FUNC = s21_insert.c s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memmove.c s21_memset.c s21_sprintf.c s21_strcat.c s21_strchr.c s21_strcmp.c s21_strcpy.c s21_strcspn.c s21_strlen.c s21_strncat.c s21_strncmp.c s21_strncpy.c s21_strpbrk.c s21_strrchr.c s21_strspn.c s21_strstr.c s21_strtok.c s21_to_lower.c s21_to_upper.c s21_trim.c
REP = report
UNAME := $(shell uname -s)

ifeq ($(UNAME), Darwin)
LIBS = -lcheck
endif
ifeq ($(UNAME), Linux)
LIBS = -lcheck -lsubunit -lrt -lm -lpthread
endif


rebuild : clean all

all : $(LIB) $(TEST) $(GCOV)

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)	

$(LIB) : $(OBJ)
	ar rc $@ $^
	ranlib $@

$(TEST) : 
	checkmk clean_mode=1 test.check > ${TEST}.c
	$(CC) $(TEST_FUNC) ${TEST}.c -o $@ $(LIBS)
	./$@

$(GCOV):
	$(CC) --coverage ${TEST}.c $(TEST_FUNC) -o $(TEST) $(LIBS)
	./$(TEST)
	lcov -t "test" -o ${TEST}.info -c -d .
	genhtml -o $(REP) ${TEST}.info

#d:
#	$(CC) $(CFLAGS) $(SOURCE) main.c
#	./a.out

clean : 
	rm -rf ${TEST}.c $(TEST) *.gcno *.gcda ${TEST}.info $(REP) $(LIB) $(OBJ)