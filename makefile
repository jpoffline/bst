OBJECTS = lib/linked_list.o lib/hashtable.o lib/data_structure_types.o lib/complex_number.o lib/binary_search_tree.o dataStructures/dataStructures.o
INC = -Wall -I/usr/local/include
LIBS = -L/usr/local/lib -lm  -L/usr/local/boost

CC = g++

all: main

%.o:     %.cpp
	$(CC) -std=c++11 -c $(INC) $< -o $@

main: $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@

clean:
	-rm -f $(OBJECTS) main
