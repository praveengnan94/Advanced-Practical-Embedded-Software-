main.elf:main.c  i2c_wrap.o lsm9ds1.o notify.o
	gcc -g -o $@ $^ -lpthread -lrt -lm

i2c_wrap.o: i2c_wrap.c
	gcc -c -o $@ $<

AccelTask.o:AccelTask.c includes.h
	gcc -c -o $@ $<  -lpthread -lrt

MagnetoTask.o:MagnetoTask.c includes.h
	gcc -c -o $@ $<  -lpthread -lrt

LoggerTask.o:LoggerTask.c includes.h
	gcc -c -o $@ $<  -lpthread -lrt

CommTask.o:CommTask.c includes.h
	gcc -c -o $@ $<  -lpthread -lrt

lsm9ds1.o: lsm9ds1.c i2c_wrap.c
	gcc -c -o $@ $<

notify.o:notify.c
	gcc -c -o $@ $<

clean:
	rm -f *.o *.elf logfile.txt ./remote_request/*.o
