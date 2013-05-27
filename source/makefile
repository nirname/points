# Project: points
# Makefile created manually

CPP = g++
CC  = gcc
COMPILER = $(CPP)
OPTIONS = #-std=gnu++11

LIBS = -lglut -lGLU

PROJECT=points
EXECUTABLE=upoints.exe
RM = rm -rf

SOURCES = main.cpp

all: $(PROJECT)

$(PROJECT): $(SOURCES)
	$(COMPILER) $(SOURCES) -o $(EXECUTABLE) $(LIBS) $(OPTIONS)

clean:
	${RM} $(EXECUTABLE)

