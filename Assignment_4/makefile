build:
	clear && gcc -Wall 200010036.c -o 200010036

verify: build
	./200010036 assignment#4-io/input1.txt
	diff -s bst.txt assignment#4-io/bst1.txt
	./200010036 assignment#4-io/input2.txt
	diff -s bst.txt assignment#4-io/bst2.txt
	./200010036 assignment#4-io/input3.txt
	diff -s bst.txt assignment#4-io/bst3.txt

test: build
	./200010036 test.txt

debug:
	clear && gcc -Wall -g 200010036.c -o 200010036
	gdb --args ./200010036 assignment#4-io/input3.txt