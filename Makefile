CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRCDIR = src
INCDIR = include
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = $(BINDIR)/main

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@
	@echo "✓ Compilación completada"

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

run: $(TARGET)
	@./$(TARGET)

clean:
	@rm -f $(OBJECTS)
	@rm -rf $(BINDIR)
	@echo "✓ Archivos limpios"

help:
	@echo "Comandos disponibles:"
	@echo "  make         - Compila el proyecto"
	@echo "  make run     - Compila y ejecuta el proyecto"
	@echo "  make clean   - Elimina archivos compilados"
	@echo "  make help    - Muestra esta ayuda"

