CC=gcc --std=c99 -g

all: test_mergesort3 test_merge3


test_mergesort3: test_merge.c
	$(CC) test_merge.c -o merge3Time

test_merge3: merge3.c 
	$(CC) merge3.c -o Mergesort3

clean:
	rm -f Mergesort3 merge3.txt merge3Time
