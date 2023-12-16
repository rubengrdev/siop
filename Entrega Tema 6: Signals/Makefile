CC=gcc
CFLAGS=
LDFLAGS=

TARGET=busca_z

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

all: $(TARGET)

clean:
	rm -f *.o *~ core $(TARGET)

