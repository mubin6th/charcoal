SRC:=src/*.c lib/argparse.c
INCLUDE_DIR:=-I"include/"
LIBS:= -lm
LIBS_DIR:=-L"lib/"
EXE:=colorgrid

all:
	$(CC) $(SRC) -o $(EXE) $(INCLUDE_DIR) $(LIBS_DIR) $(LIBS)

run: all
	./colorgrid

clean:
	rm -fr ./colorgrid ./colorgrid.png
