BINDIR = .
OBJDIR = objects
INCLUDE_PATH = include

EXECUTABLE = lpoints
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)
RM = rm -rf
CXXFLAGS = -Wall

#all: $(SOURCES) $(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(BINDIR) $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(EXECUTABLE) $(OBJECTS) -I $(INCLUDE_PATH)

#$(BINDIR)
$(OBJDIR):
	mkdir $@ # each target

%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) -o $@ $< -I $(INCLUDE_PATH)

#%.o : %.c %.h
#	$(CXX) -c -o $@ $< -I $(INCLUDE_PATH)

.PHONY: clean

clean:
	#$(RM) $(BINDIR)/$(EXECUTABLE)
	$(RM) $(OBJECTS)

#
