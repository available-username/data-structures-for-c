CC		= gcc

CFLAGS	= -pedantic -Wall -Wextra -Werror -I../ -g -O0
LDFLAGS	= -L../
LDLIBS	= -lcheck -lutil
PROG	= check_util
OBJS	= check_main.o \
		check_slist.o
LIBS	= check

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: check

check: $(OBJS)
	$(CC) -o $(PROG) $^ $(LDFLAGS) $(LDLIBS)
	LD_LIBRARY_PATH=.. ./$(PROG)

checkmem: $(OBJS)
	LD_LIBRARY_PATH=.. CK_FORK=no valgrind --leak-check=full ./$(PROG)

clean:
	$(RM) $(PROG) $(OBJS)

print-%:
	$(ECHO) $*=$($*)
