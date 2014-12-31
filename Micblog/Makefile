CC	= gcc
LD	= ld
CFLAGS	= -I./include -O2

CFILES	= $(shell find src/ -name "*.c")
OBJS	= $(CFILES:.c=.o)

micblog: $(OBJS)
	  $(CC)	-o micblog $(OBJS) $(CFLAGS)	-lreadline
run:	micblog	newfriends.txt	at.txt
	./micblog newfriends.txt at.txt 2>&1 | tee log.txt
clean:
	-rm -f micblog $(OBJS) $(OBJS:.o=.d) log.txt 2> /dev/null
