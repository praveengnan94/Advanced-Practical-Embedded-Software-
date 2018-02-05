#Makefile
testfile.elf:testfile.c ../p6/doublylinkedlist.c
	gcc -o $@ $^ -lcmocka

clean:
	-rm -f *.o *.d
	-rm -f testfile