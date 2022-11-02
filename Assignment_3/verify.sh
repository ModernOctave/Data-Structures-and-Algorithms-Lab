#/usr/bin/bash

gcc 200010036.c -o 200010036

./200010036 assignment#3-io/input1.txt 6
diff -s radix.txt assignment#3-io/radix1.txt

./200010036 assignment#3-io/input2.txt 5
diff -s radix.txt assignment#3-io/radix2.txt

./200010036 assignment#3-io/input3.txt 4
diff -s radix.txt assignment#3-io/radix3.txt