proj4: proj4.c
	  gcc -o proj4 proj4.c
clean:
	  rm proj4
runLRU1:
	./proj4 input1.txt LRU
runCLOCK1:
	./proj4 input1.txt CLOCK
runLRU2:
	./proj4 input2.txt LRU
runCLOCK2:
	./proj4 input2.txt CLOCK
