tests: tests.c 
	gcc -o $@ $^ -lcmocka -lm -lrt -pthread

clean:
	-rm -f *.o tests
