_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc -O3
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lm

CFLAGS_BIS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include -fsanitize=address

.PHONY: clean doc check-syntax compile-all launch-tests

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- gfind . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete
 
# compile rules
%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

# you should put all the .o files corresponding to your .c files as prerequisites of
# this rule (see examples)
# \ allows to go on the next line
check-syntax: map.o testing-main.o loader.o test-loader.o test-find-neighbors.o maze.o prim.o test-prim.o app-generate-maze.o \
			  heap.o test-heap-correctness.o test-heap-complexity.o prim-bh.o app-generate-maze-bh.o test-prim-bh.o


# put all the rules to build your applications and tests here (see examples)
map: map.o
	$(CC) $(CFLAGS) -o map map.o $(LDFLAGS)

loader: loader.o
	$(CC) $(CFLAGS) -o loader loader.o $(LDFLAGS)

maze: maze.o map.o
	$(CC) $(CFLAGS) -o maze maze.o map.o $(LDFLAGS)

prim: prim.o maze.o map.o loader.o
	$(CC) $(CFLAGS) -o prim prim.o maze.o map.o loader.o $(LDFLAGS)

testing-main: testing-main.o map.o loader.o maze.o prim.o
	$(CC) $(CFLAGS) -o testing-main testing-main.o map.o loader.o maze.o prim.o $(LDFLAGS) 

test-loader: test-loader.o map.o loader.o
	$(CC) $(CFLAGS) -o test-loader test-loader.o map.o loader.o $(LDFLAGS) 

test-find-neighbors: test-find-neighbors.o map.o loader.o
	$(CC) $(CFLAGS) -o test-find-neighbors test-find-neighbors.o map.o loader.o $(LDFLAGS) 

test-prim: test-prim.o prim.o maze.o map.o loader.o
	$(CC) $(CFLAGS) -o test-prim test-prim.o prim.o maze.o map.o loader.o $(LDFLAGS)

app-generate-maze: app-generate-maze.o prim.o maze.o map.o loader.o
	$(CC) $(CFLAGS) -o app-generate-maze app-generate-maze.o prim.o maze.o map.o loader.o $(LDFLAGS)

heap: heap.o 
	$(CC) $(CFLAGS) -o heap heap.o $(LDFLAGS)

test-heap-correctness: test-heap-correctness.o heap.o
	$(CC) $(CFLAGS) -o test-heap-correctness test-heap-correctness.o heap.o $(LDFLAGS)

test-heap-complexity: test-heap-complexity.o heap.o
	$(CC) $(CFLAGS) -o test-heap-complexity test-heap-complexity.o heap.o $(LDFLAGS)

prim-bh: prim-bh.o maze.o map.o loader.o heap.o
	$(CC) $(CFLAGS) -o prim-bh prim-bh.o maze.o map.o loader.o heap.o $(LDFLAGS)

app-generate-maze-bh: app-generate-maze-bh.o prim-bh.o maze.o map.o loader.o heap.o
	$(CC) $(CFLAGS) -o app-generate-maze-bh app-generate-maze-bh.o prim-bh.o maze.o map.o loader.o heap.o $(LDFLAGS)

test-prim-bh: test-prim-bh.o prim-bh.o maze.o map.o loader.o heap.o
	$(CC) $(CFLAGS) -o test-prim-bh test-prim-bh.o prim-bh.o maze.o map.o loader.o heap.o $(LDFLAGS)


# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: testing-main test-loader test-find-neighbors test-prim app-generate-maze \
			 test-heap-correctness test-heap-complexity app-generate-maze-bh test-prim-bh


# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-find-neighbors test-prim test-heap-correctness test-heap-complexity test-prim-bh

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done

# add all .c, .h and .txt files in repository
#git-add-all-files:
#	git add tests/*.c src/*.c include/*.h data/*.txt
