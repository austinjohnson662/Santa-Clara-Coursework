CC = gcc
PROGS = data

all: $(PROGS)

clean:; $(RM) $(PROGS) *.o core

run: $(PROGS)
	./data

data: collegeApp2.o datasetApp2.o
	$(CC) -o data collegeApp2.o datasetApp2.o
