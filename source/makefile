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

PROJECT = points
EXECUTABLE = upoints.exe
RM = rm -rf

SOURCES = $(shell find . -name "*.cpp")
#SOURCES = main.cpp include/easy-bmp/EasyBMP.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)

$(PROJECT):
	$(COMPILER) $(SOURCES) -o $(EXECUTABLE) -I $(INCLUDE_PATH) -L $(LIBRARIES_PATH) $(LIBS) $(OPTIONS)

#$(PROJECT): $(OBJECTS)
#	$(COMPILER) $^ -o $(EXECUTABLE) -L $(LIBRARIES_PATH) $(LIBS)

#main.o: main.cpp
#	$(COMPILER) -c main.cpp -I $(INCLUDE_PATH)

#EasyBMP.o: include/easy-bmp/EasyBMP.cpp
#	$(COMPILER) -c include/easy-bmp/EasyBMP.cpp

clean:
	${RM} `find . -name "*.o"`

.PHONY: $(PROJECT) clean
