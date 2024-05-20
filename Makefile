all:
	cc -D_FILE_OFFSET_BITS=64 f.c
	cc d.c -o d
test:
	time ./d
clean:
	rm -rf *.o *.h5 a.out dir_*

