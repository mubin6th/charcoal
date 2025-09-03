SRC:=src/*.c lib/*.c
INCLUDE_DIR:=-I"include/"
LIBS:= -lm -lglfw3 -lGL -ldl
LIBS_DIR:=-L"lib/"
EXE:=colorgrid

all:
	$(CC) $(SRC) -o $(EXE) $(INCLUDE_DIR) $(LIBS_DIR) $(LIBS)

run: all
	./colorgrid

clean:
	rm -fr ./colorgrid ./colorgrid.png
