CC	= gcc
LD	= ld
CFLAGS	= -I./include -O2

CFILES	= $(shell find src/ -name "*.c")
OBJS	= $(CFILES:.c=.o)

micblog: $(OBJS)
	  $(CC)	-o micblog $(OBJS) $(CFLAGS) -lreadline
clean:
	-rm -f micblog $(OBJS) $(OBJS:.o=.d)
