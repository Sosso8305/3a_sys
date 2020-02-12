#
##

CC	=	gcc 
CFLAGS	=  	-Wall
CFLAGS  +=      -D_GNU_SOURCE
CFLAGS  += 	-g

CIBLES	=	add cat chmod cp date diff grep id ln ls minishell mkdir mv rm rmdir rmline tail tailf touch wc

all: $(CIBLES)

clean: 
	$(RM) -f core *.o $(CIBLES) *~

run: clean all
		./minishell
