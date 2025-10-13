CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= main.c prompt.c vec_util.c vecmath.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=vectorcalc

all: $(SOURCES) $(EXECUTABLE) 

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d

