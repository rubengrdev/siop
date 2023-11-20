CC=gcc
CFLAGS=
LDFLAGS=

TARGET= prova_pipe exercici_pipes1 exercici_pipes2 exercici_pipes3 exercici_pipes3_millor

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

all: $(TARGET)

clean:
	rm -f *.o *~ core $(TARGET)

