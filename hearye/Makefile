hearye: hearye.c 
	#gcc -o hellomake hellomake.c hellofunc.c -I.
	aarch64-linux-gnu-gcc -z execstack -fno-stack-protector -static -g -O0 -o hearye hearye.c
	zip hearye.zip instructions.txt hearye

clean:
	rm -f hearye *.i64 *.zip
