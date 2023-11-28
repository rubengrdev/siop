CC=gcc
CFLAGS=
LDFLAGS=

TARGET=cada_segundo cada_segundo_sigchld signal_basico signal_izquierda_derecha plauncher_sigchld

%: %.c
	$(CC) -o $@ $< $(CFLAGS)

all: $(TARGET)

clean:
	rm -f *.o *~ core $(TARGET)

