.PHONY: clean run

all: bin/version_editor

bin/version_editor: build/version_editor.o | bin
	@echo "-- Building the binary file... --"
	g++ -o bin/version_editor build/version_editor.o
	@echo ""

bin:
	mkdir bin

build/version_editor.o: src/version_editor.cpp | build
	@echo "-- Building the object files... --"
	g++ -c -o build/version_editor.o src/version_editor.cpp
	@echo ""

build:
	mkdir build

clean:
	rm -rf build
	rm -rf bin

run: bin/version_editor
	./bin/version_editor