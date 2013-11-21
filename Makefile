CC    = gcc

LIB			= libutil.so
CFLAGS		= -fPIC -pedantic -Wall -Wextra -Werror -g -O0
LDFLAGS		= -shared

OBJS		= slist.o

export LIB

.PHONY		= clean

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@

check: $(LIB)
	$(MAKE) -C checktests $@

checkmem: $(LIB)
	$(MAKE) -C checktests $@

clean:
	$(RM) $(LIB) $(OBJS)
	$(MAKE) -C checktests $@

print-%:
	$(ECHO) $*=$($*)
