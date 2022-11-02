clear:
	clear

build: clear
	gcc -Wall 200010036.c ll.c queue.c -o 200010036

build-debug: clear
	gcc -Wall -g 200010036.c ll.c queue.c -o 200010036

run: build
	./200010036 Assignment#6-io/input1.graph

debug: build-debug
	gdb --args ./200010036 Assignment#6-io/input1.graph

verify: build
	./200010036 Assignment#6-io/input1.graph
	diff -s sd.txt Assignment#6-io/sd1.txt
	./200010036 Assignment#6-io/input2.graph
	diff -s sd.txt Assignment#6-io/sd2.txt
	./200010036 Assignment#6-io/input3.graph
	diff -s sd.txt Assignment#6-io/sd3.txt
