BINDIR = .
#OBJDIR = objects

EXECUTABLE = lpoints
SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)

INCPATH = include

LDFLAGS = -L libraries/ubuntu13
LDLIBS = -lglut -lGL -lGLU -lopenal -lalut -lyaml-cpp

CXXFLAGS = -Wall -I $(INCPATH)
CFLAGS = $(CXXFLAGS)


# the -MD option if you wish to include system headers, or
# the -MMD option if you do not.

CPPFLAGS += -MMD -MP

RM = rm -rf
# Основное правило $(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(OBJDIR)
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS) $(LDLIBS)

# Очищаем правила по умолчанию
%.o: %.cpp
%.o: %.c
#	$(CC) -c $(CFLAGS) -o $@ $<

# $@ - имя цели
# $< - имя перового элемента в зависимостях

# Добавляем в зависимости заголовочные файлы
%.o: %.cpp %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# Добавляем правила на случай, если заголовочных файлов нет
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# Правила для автоматического создания директорий #$(BINDIR)
#$(OBJDIR):
#	mkdir $@ # each target

-include $(SRC:%.cpp=%.d)

.PHONY: clean

clean:
	$(RM) $(OBJECTS)
	$(RM) $(BINDIR)/$(EXECUTABLE)

#
