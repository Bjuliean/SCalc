CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRC=calc_engine.c
PFLAGS=$(shell pkg-config --libs --cflags check)
OBJ=calc_engine.o
TLIBS=-lcheck -lm -lpthread

all: gcov_report

gcov_report: test
	$(CC) $(CFLAGS) --coverage test.c $(SRC) $(TLIBS) -o gcov_test $(PFLAGS)
	@chmod +x *
	@./gcov_test
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	@genhtml -o report/ gcov_test.info
	@open report/index.html

calc_engine.a:
	$(CC) $(CFLAGS) -c $(SRC) $(PFLAGS)
	ar rcs calc_engine.a $(OBJ)

test: calc_engine.a
	$(CC) -c $(SRC) -o $(OBJ) $(PFLAGS)
	$(CC) test.c calc_engine.a -lcheck -lm -lpthread -o test $(PFLAGS)
	./test

clean:
	rm -rf *.o *.a test *.info *.gcno *.gcda test_output gcov_test report

dvi:
	open readme.html

install:
	rm -rf build
	mkdir build
	cd untitled && qmake && make && mv untitled.app ../build && cd ..

uninstall:
	rm -rf build*
	rm -rf untitled/moc*
	rm -rf untitled/*.o
	rm -rf untitled/ui*

dist: install
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src
	cp -r ./build/untitled.app Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/