CXX=g++ -std=c++17
LIBS = -lgtest -lstdc++ -lpthread -lrt -lm
PR_NAME = PhotoLab

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=-lgtest -lstdc++  -lpthread -lrt -lm
  OPEN=xdg-open
else
  LIBS=-lgtest -lstdc++ -pthread
  OPEN=open
endif

all: install dist dvi test lint


build: clean
	@-rm -rf ../build
	@mkdir -p ../build
	@cmake -B../build
	@make -C ../build
	@cd ../build &&  rm -rf ./*[^$(PR_NAME)\.app] CMakeCache.txt $(PR_NAME)_autogen

install: build

uninstall:
	 @-rm -rf ../build

tests: test

test:
	cmake -S ./tests -B build_test
	cmake --build build_test
	./build_test/PhotoLab_test

dvi:
	$(OPEN) ./documentation/dvi.html

dist:
	@-rm -rf DIST
	@-mkdir DIST
	@cp -R ../build/* DIST
	@tar -czvf $(PR_NAME).tar DIST
	@-rm -rf DIST

lint:
	@clang-format -i --style=Google ./*/*h ./*/*cc ./*.cc
	@clang-format -n --style=Google ./*/*h ./*/*cc ./*.cc

check:
	@cppcheck --enable=all --suppress=missingInclude  --suppress=unusedFunction --std=c++17 --language=c++  ./*/*.cc ./*/*.h

clean:
	@rm -rf *.o *.a build_test
