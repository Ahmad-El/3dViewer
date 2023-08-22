TESTFLAGS = -lcheck
GCCFLAGS = -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: clean install dist test gcov_report

test:
	@gcc $(GCCFLAGS) -std=c11 -o test tests/test.c c_code/sources/*.c $(TESTFLAGS) $(GCCFLAGS)
	./test

gcov_test: 
	@gcc $(GCCFLAGS) -std=c11 -o test tests/test.c c_code/sources/*.c $(TESTFLAGS) $(GCCFLAGS) $(GCOVFLAGS)
	./test

gcov_report: gcov_test
	@lcov -t "./gcov" -o report.info --no-external -c -d .
	@genhtml -o report report.info
	@open ./report/index.html

install: uninstall
	make clean
	mkdir -p build
	cd ui && qmake && make && make clean && rm Makefile && cd ../ && mv ui/ui.app build

uninstall:
	rm -rf build
	
clean: dist_clean
	@rm -rf *.o *.a test
	@rm -rf *.gcno *gcda *.gcov gcov
	@rm -rf report report.info
	@rm -rf *.dSYM
	@rm -rf *.a


clean_test: 
	rm -rf test

dvi:
	open info.md

dist: 
	tar -cvf 3DViewer_v1.tar.gz c_code ui models


dist_clean: 
	rm -rf 3DViewer_v1.tar.gz

launch:
	open build/ui.app


style:
	clang-format -n --style=google c_code/3D_viewer.h
	clang-format -n --style=google c_code/sources/*.c 
	clang-format -n --style=google c_code/sources/*.h
	clang-format -n --style=google tests/test.c
	clang-format -n --style=google ui/*.h  
	clang-format -n --style=google ui/*.cpp
	clang-format -n --style=google ui/src/3rdParty/giflib/*.c
	clang-format -n --style=google ui/src/3rdParty/giflib/*.h
	clang-format -n --style=google ui/src/gifimage/*.cpp
	clang-format -n --style=google ui/src/gifimage/*.h