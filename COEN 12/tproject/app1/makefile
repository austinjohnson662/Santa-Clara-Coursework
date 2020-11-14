CC = gcc
PROGS = data

all: $(PROGS)

clean:; $(RM) $(PROGS) *.o core

run: $(PROGS)
	./data

data: collegeApp1.o datasetApp1.o
	$(CC) -o data collegeApp1.o datasetApp1.o
