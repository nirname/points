# Project: square
# Makefile created manually

CPP = g++
CC  = gcc
COMPILER = $(CPP)

LIBS = -lglut

PROJECT=square
EXECUTABLE=usquare.exe
RM = rm -rf

SOURCES = main.cpp

all: $(PROJECT)

$(PROJECT): $(SOURCES)
	$(COMPILER) $(SOURCES) -o $(EXECUTABLE) $(LIBS)

clean:
	${RM} $(EXECUTABLE)

