CC=gcc
CXXFLAGS=-Wall -pedantic
CXXLDFLAGS=
DEFINES=-D__linux__

STD=c11

BINDIR=bin
INCLUDEDIR=include
LIBDIR=lib
OBJDIR=obj

TARGET=kerntool

all: $(TARGET)

$(TARGET): clean main.o kerntool-conio.o kerntool-info.o kerntool-util.o
	$(CC) -std=$(STD) -I$(INCLUDEDIR) -L$(LIBDIR) $(DEFINES) $(CXXFLAGS) -g -s main.o kerntool-conio.o kerntool-info.o kerntool-util.o -o $(TARGET) $(CXXLDFLAGS)
	mkdir bin obj
	mv *.o $(OBJDIR)
	mv $(TARGET) $(BINDIR)

main.o: src/main.c
	$(CC) -std=$(STD) -I$(INCLUDEDIR) -L$(LIBDIR) $(DEFINES) $(CXXFLAGS) -c $^

kerntool-conio.o: src/kerntool-conio.c
	$(CC) -std=$(STD) -I$(INCLUDEDIR) -L$(LIBDIR) $(DEFINES) $(CXXFLAGS) -c $^

kerntool-info.o: src/kerntool-info.c
	$(CC) -std=$(STD) -I$(INCLUDEDIR) -L$(LIBDIR) $(DEFINES) $(CXXFLAGS) -c $^

kerntool-util.o: src/kerntool-util.c
	$(CC) -std=$(STD) -I$(INCLUDEDIR) -L$(LIBDIR) $(DEFINES) $(CXXFLAGS) -c $^

clean:
	rm -rf $(BINDIR) $(OBJDIR) *.log *.o *.exe *.stackdump