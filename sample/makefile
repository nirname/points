#BINDIR = .
OBJDIR = objects
INCLUDE_PATH = include

EXECUTABLE = lpoints
SOURCES = $(shell find . -name "*.cpp")
SOURCE_DIRS = $(shell find . -name "*.cpp" -exec dirname {} \; | uniq)
#OBJECTS = $(SOURCES:%.cpp=%.o)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:%.cpp=%.o)))
RM = rm -rf
CXXFLAGS = -Wall

VPATH = $(SOURCE_DIRS)

#all:
#	echo $(SOURCE_DIRS) >> /dev/null

#all: $(SOURCES) $(EXECUTABLE)

#$(BINDIR)/$(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS) -I $(INCLUDE_PATH)

#$(BINDIR) $(OBJDIR)
$(OBJDIR):
	mkdir $@ # each target

$(OBJDIR)/%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c -o $@ $<

#%.o : %.c %.h
#	$(CXX) -c -o $@ $< -I $(INCLUDE_PATH)

.PHONY: clean

clean:
	#$(RM) $(BINDIR)/$(EXECUTABLE)
	$(RM) $(OBJECTS)

#
