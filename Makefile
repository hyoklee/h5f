all:
	cc -D_FILE_OFFSET_BITS=64 f.c
	cc d.c -o d
	h5cc k.c -o k
	h5cc g.c -o g
test:
	time ./d
	time ./k
	time ./g
clean:
	rm -rf *.o *.h5 a.out dir_*

