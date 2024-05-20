all:
	cc -D_FILE_OFFSET_BITS=64 f.c
	cc d.c -o d
	h5cc g.c -o g
	h5cc k.c -o k
	cc k4.c -o k4
test:
	time ./d
	time ./g
	time ./k
	time ./k4
clean:
	rm -rf d g k k4 a.out *.o *.h5  *.bin dir_*


