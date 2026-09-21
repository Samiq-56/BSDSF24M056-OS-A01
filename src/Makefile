# ==================================================
#  src/Makefile
#  Compiles all .c files directly and links them
# ==================================================
CC      = gcc
CFLAGS  = -Wall -Wextra -g
INCDIR  = ../include
BINDIR  = ../bin
APP     = multifile_app
TARGET  = $(BINDIR)/$(APP)

SRCS    = main.c mystrfunctions.c myfilefunctions.c
HDRS    = $(INCDIR)/mystrfunctions.h $(INCDIR)/myfilefunctions.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	cd $(BINDIR) && ./$(APP)

clean:
	rm -f $(TARGET) $(BINDIR)/sample.txt
