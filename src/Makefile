# ==================================================
#  src/Makefile
#  Builds string/file functions into a dynamic library
#  (libmyutils.so) and links main.c against it
# ==================================================
CC      = gcc
CFLAGS  = -Wall -Wextra -g
INCDIR  = ../include
LIBDIR  = ../lib
BINDIR  = ../bin
APP     = client_dynamic
TARGET  = $(BINDIR)/$(APP)
LIB     = $(LIBDIR)/libmyutils.so
LIBOBJS = mystrfunctions.o myfilefunctions.o

.PHONY: all run clean

all: $(TARGET)

# Link main.c against the dynamic library
$(TARGET): main.c $(LIB)
		mkdir -p $(BINDIR)
		$(CC) $(CFLAGS) -I$(INCDIR) main.c -L$(LIBDIR) -lmyutils -o $(TARGET)

# Build the dynamic library using -shared
$(LIB): $(LIBOBJS)
		mkdir -p $(LIBDIR)
		$(CC) -shared $(LIBOBJS) -o $(LIB)

# Generic rule: compile any .c file into a position-independent object file (-fPIC)
%.o: %.c
		$(CC) $(CFLAGS) -fPIC -I$(INCDIR) -c $< -o $@

run: $(TARGET)
		cd $(BINDIR) && ./$(APP)

clean:
		rm -f $(TARGET) $(LIB) *.o $(BINDIR)/sample.txt


