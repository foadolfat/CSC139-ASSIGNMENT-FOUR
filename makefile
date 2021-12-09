proj4: proj4.c
	  gcc -o proj4 proj4.c
clean:
	  rm proj4
runLRU:
	./proj4 input1.txt LRU
runCLOCK:
	./proj4 input1.txt CLOCK
