SRC:=src/*.c lib/*.c
INCLUDE_DIR:=-I"include/"
LIBS:=-lm -lglfw3 -lGL -ldl
LIBS_DIR:=-L"lib/"
FLAGS:=-Wall -std=gnu99
EXE:=colorgrid

all:
	$(CC) $(FLAGS) $(SRC) -o $(EXE) $(INCLUDE_DIR) $(LIBS_DIR) $(LIBS)

run: all
	./colorgrid

install: all
	cp colorgrid /usr/local/bin

clean:
	rm -fr ./colorgrid ./colorgrid.png
