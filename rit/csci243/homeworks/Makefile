## Stephen Allan
## An example Makefile that probably works... with a bit of tweaking

FLAGS =	gcc -std=c99 -ggdb -Wall -Wextra -pedantic
LIBFLAGS =	-lm
OBJFILES =	

all:	main clean

main:	main.o $(OBJFILES)
	$(FLAGS) -o main main.o $(OBJFILES) $(LIBFLAGS)

clean:	$(OBJFILES)
	-/bin/rm -f $(OBJFILES) main.o core
