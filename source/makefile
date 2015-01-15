#BINDIR = .
#OBJDIR = objects

EXECUTABLE = lpoints

SOURCES = $(shell find . -name "*.cpp")
OBJECTS = $(SOURCES:%.cpp=%.o)
DEPENDENCIES = $(SOURCES:%.cpp=%.d)

LDFLAGS = -L libraries/ubuntu13
LDLIBS = -lglut -lGL -lGLU -lopenal -lalut -lyaml-cpp

CXXFLAGS = -Wall -I include -I core -I core/convert
#-Wextra -pedantic
CFLAGS = $(CXXFLAGS)

# Сгенерируем файлы зависимостей (*.d)
#
# the -MD option if you wish to include system headers, or
# the -MMD option if you do not.
CPPFLAGS += -MMD -MP

RM = rm -rf

# Используемые переменные
#
# $@ - имя цели
# $< - имя перового элемента в зависимостях

# Основное правило $(BINDIR)/$(EXECUTABLE): $(OBJECTS) | $(OBJDIR)
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS) $(LDLIBS)

# Очищаем правила по умолчанию
%.o: %.cpp
%.o: %.c
#	$(CC) -c $(CFLAGS) -o $@ $<

# Добавляем в зависимости заголовочные файлы
%.o: %.cpp %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# Добавляем правила на случай, если заголовочных файлов нет
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

-include $(DEPENDENCIES)

# Правила для автоматического создания директорий #$(BINDIR)
#$(OBJDIR):
#	mkdir $@ # each target

.PHONY: clean cleand cleano cleane

clean: cleand cleano cleane

cleand:
	$(RM) $(DEPENDENCIES)

cleano:
	$(RM) $(OBJECTS)

cleane:
	$(RM) $(EXECUTABLE)

#
