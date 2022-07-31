FLAGS = g++ -g -std=c++17 -Wall -Wextra #-Werror

OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -pthread
else
	CHECK_FLAGS = -lgtest
endif

SRC = Model/Errors_Handling.cpp Model/Fill_Stack.cpp Model/Reverse_Polish_Notation.cpp Model/Entry_Point.cpp \
	Model/Calculate.cpp Controller/Calc_Controller.cpp

TEST_COMPILE = $(FLAGS) tests.cpp $(SRC) $(CHECK_FLAGS)

DATA = "The max length of string is 255 symbols. Press 'Func graph' in order to get function's\
		 graph (domain is from -1000000 to 1000000)"

all: clean test

install:
	mkdir ProgramFiles
	cd View && qmake && make && make clean && rm Makefile && mv View.app/Contents/MacOS/View ../ProgramFiles \
	&& rm -rf View.app

uninstall:
	rm -rf ProgramFiles

dist:
	tar cfz Calc.tgz ProgramFiles

dvi:
	touch info.dvi
	@(echo $(DATA) > info.dvi)

gcov_report: gcov_report_build
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info

gcov_report_build:
	$(FLAGS) tests.cpp $(SRC) $(CHECK_FLAGS) --coverage -o gcov_report
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html

test:
	$(TEST_COMPILE)
	./a.out

check_leaks:
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean

check_style:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=cpp tests.cpp $(SRC) Controller/*.h Model/*.h \
	View/main.cpp View/mainwindow.cpp View/mainwindow.h View/Other_Functions.cpp
	rm CPPLINT.cfg

clean: uninstall
	rm -rf *.o *.g* *.info *gcov_report report *.a *.dSYM a.out Calc.tgz CPPLINT.cfg info.dvi
