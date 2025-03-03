IDIR=.
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=.

LIBS=-lm

_DEPS = affichage.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = affichage.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~