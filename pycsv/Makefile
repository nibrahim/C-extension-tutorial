CINC="/home/noufal/projects/python/builds/3.1.2/include/python3.1"

pycsv.so: pycsvmodule.o 
	gcc -pthread -shared pycsvmodule.o -o pycsv.so	

pycsvmodule.o: pycsvmodule.c csv.h Makefile
	gcc  -I${CINC} -c -fPIC pycsvmodule.c -o pycsvmodule.o

clean:
	rm *.so *.o

check-syntax:
	gcc -I${CINC} -Wall -o nul -S ${CHK_SOURCES}

