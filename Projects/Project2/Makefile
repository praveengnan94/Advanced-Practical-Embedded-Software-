main.elf:main.c  i2c_wrap.o
	gcc -g -o $@ $^ -lpthread -lrt -lm

i2c_wrap.o: i2c_wrap.c
	gcc -c -o $@ $<

AccelTask.o:AccelTask.c includes.h
	gcc -c -o $@ $<  -lpthread -lrt

notify.o:notify.c
	gcc -c -o $@ $<

clean:
	rm -f *.o *.elf logfile.txt ./remote_request/*.o
