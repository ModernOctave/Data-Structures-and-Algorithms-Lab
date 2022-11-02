build:
	gcc -Wall 200010036.c ll.c -o 200010036

build-debug:
	gcc -Wall -g 200010036.c ll.c -o 200010036

run: build
	./200010036 words.txt 25000 query.txt

debug: build-debug
	gdb --args ./200010036 words.txt 25000 query.txt

verify: build
	./200010036 words.txt 25000 Assignment#5-IO/query1.txt
	diff -s anagrams.txt Assignment#5-IO/anagrams1.txt
	./200010036 words.txt 25000 Assignment#5-IO/query2.txt
	diff -s anagrams.txt Assignment#5-IO/anagrams2.txt
	./200010036 words.txt 25000 Assignment#5-IO/query3.txt
	diff -s anagrams.txt Assignment#5-IO/anagrams3.txt
