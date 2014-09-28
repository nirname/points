BINDIR = .
OBJDIR = objects

EXECUTABLE = lpoints
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)

INCPATH = include

LIBPATH = libraries/ubuntu13
LIBS = -lglut -lGL -lGLU -lopenal -lalut -lyaml-cpp
# -lopengl32 -lfreeglut -lglu32

CXXFLAGS = -Wall -I $(INCPATH)# -L $(LIBPATH) $(LIBS)
CFLAGS = $(CXXFLAGS)

RM = rm -rf
# Основное правило
$(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(EXECUTABLE) $(OBJECTS) -L $(LIBPATH) $(LIBS)

# Очищаем правила по умолчанию
%.o: %.cpp
%.o: %.c
#	$(CC) -c $(CFLAGS) -o $@ $<

# Добавляем в зависимости заголовочные файлы
%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# Добавляем правила на случай, если заголовочных файлов нет
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

# Правила для автоматического создания директорий #$(BINDIR)
$(OBJDIR):
	mkdir $@ # each target

.PHONY: clean

clean:
	#$(RM) $(BINDIR)/$(EXECUTABLE)
	$(RM) $(OBJECTS)

#
