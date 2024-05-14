all:
	cc -D_FILE_OFFSET_BITS=64 f.c
clean:
	rm -rf *.o *.h5 a.out

