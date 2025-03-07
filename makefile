IDIR =.
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =.

LIBS=-lm

_DEPS = define.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = affichage.o fichiers.o fir.o iir.o mesure.o main_sim.o autotests.o lecture.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cardiofrequencemetre: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
.PHONY: run
.PHONE: valgrind

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

run: cardiofrequencemetre
	./cardiofrequencemetre

valgrind: cardiofrequencemetre
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./cardiofrequencemetre