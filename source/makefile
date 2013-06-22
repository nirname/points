# Project: points
# Makefile created manually

CPP = g++
CC  = gcc
COMPILER = $(CPP)
OPTIONS = #-std=gnu++11

INCLUDE_PATH = include
LIBRARIES_PATH = libraries/ubuntu

#-lopengl32 -lfreeglut -lglu32
LIBS = -lglut -lGLU -lyaml-cpp

PROJECT=points
EXECUTABLE=upoints.exe
RM = rm -rf

SOURCES = main.cpp

all: $(PROJECT)

$(PROJECT): $(SOURCES)
	$(COMPILER) $(SOURCES) -o $(EXECUTABLE) -I $(INCLUDE_PATH) -L $(LIBRARIES_PATH) $(LIBS) $(OPTIONS)

clean:
	${RM} $(EXECUTABLE)
