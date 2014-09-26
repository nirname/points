EXECUTABLE = lpoints
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)
RM = rm -rf
CXXFLAGS = -Wall

BINDIR = ../game
OBJDIR = ../objs

#all: $(SOURCES) $(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(EXECUTABLE) $(OBJECTS)

$(BINDIR):
	mkdir $(BINDIR)

%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

%.o : %.c %.h
	$(CXX) -c -o $@ $<

.PHONY: clean

clean:
	#$(RM) $(BINDIR)/$(EXECUTABLE)
	$(RM) $(OBJECTS)

#
