#/usr/bin/bash

gcc 200010036.c -o 200010036

./200010036 assignment-2-io/input1.txt
diff -s mergesort.txt assignment-2-io/output1.txt

./200010036 assignment-2-io/input2.txt
diff -s mergesort.txt assignment-2-io/output2.txt

./200010036 assignment-2-io/input3.txt
diff -s mergesort.txt assignment-2-io/output3.txt