CC=gcc
LIBS=-lncurses

SOURCES :=$(shell ls *.c)
OBJS	:=$(SOURCES:%.c=%.o)



%.out: $(OBJS)
	${CC} -o $@ $^ ${LIBS}


%.o: %.c
	${CC} -o $@ -c -g -Wall -Wextra $<


clean:
	@rm -f *.out *.o


test:
	@echo SOURCES ARE: $(SOURCES)
	@echo OBJECTS ARE: $(OBJS)
