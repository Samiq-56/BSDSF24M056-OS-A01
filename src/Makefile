# ==================================================
#  src/Makefile
#  Builds string/file functions into a static library
#  (libmyutils.a) and links main.c against it
# ==================================================
CC      = gcc
CFLAGS  = -Wall -Wextra -g
INCDIR  = ../include
LIBDIR  = ../lib
BINDIR  = ../bin
APP     = client_static
TARGET  = $(BINDIR)/$(APP)
LIB     = $(LIBDIR)/libmyutils.a
LIBOBJS = mystrfunctions.o myfilefunctions.o

.PHONY: all run clean

all: $(TARGET)

# Link main.c against the static library
$(TARGET): main.c $(LIB)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) main.c -L$(LIBDIR) -lmyutils -o $(TARGET)

# Build the static library from the object files
$(LIB): $(LIBOBJS)
	mkdir -p $(LIBDIR)
	ar rcs $(LIB) $(LIBOBJS)

# Generic rule: compile any .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

run: $(TARGET)
	cd $(BINDIR) && ./$(APP)

clean:
	rm -f $(TARGET) $(LIB) *.o $(BINDIR)/sample.txt
