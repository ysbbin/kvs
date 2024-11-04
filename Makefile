SRCS = main.c
LIBSRCS = open.c close.c put.c get.c
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LSO = libkvs.so

all: static dynamic

# Static library build
static: $(TARG)

$(TARG): $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static

$(LARS): $(LOBJS)
	ar rs $(LARS) $(LOBJS)

# Dynamic library build
dynamic: $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS) $(LSO)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) -L. -lkvs

$(LSO): $(LOBJS)
	$(CC) -shared -o $(LSO) $(LOBJS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(LSO) $(TARG) $(TARG_DYNAMIC)



