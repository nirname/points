BINDIR = .
OBJDIR = objects
INCLUDE_PATH = include

EXECUTABLE = lpoints
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)
RM = rm -rf
CXXFLAGS = -Wall -I $(INCLUDE_PATH)
CFLAGS = $(CXXFLAGS)

# Основное правило
$(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(EXECUTABLE) $(OBJECTS)

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
