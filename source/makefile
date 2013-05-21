# Project: square
# Makefile created manually

CPP = g++
CC  = gcc
COMPILER = $(CPP)
OPTIONS = #-std=gnu++11

LIBS = -lglut

PROJECT=square
EXECUTABLE=usquare.exe
RM = rm -rf

SOURCES = main.cpp

all: $(PROJECT)

$(PROJECT): $(SOURCES)
	$(COMPILER) $(SOURCES) -o $(EXECUTABLE) $(LIBS) $(OPTIONS)

clean:
	${RM} $(EXECUTABLE)

