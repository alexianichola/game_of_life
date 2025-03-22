all: compile 
compile:
	gcc task1_test.c task1.c -o task1.out
clean:
	rm -f task1.out
