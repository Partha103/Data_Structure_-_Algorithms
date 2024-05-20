# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -Iinclude

# Source files
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Object files directory
OBJDIR = build

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Output executable
TARGET = main

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

# Rule to create the build directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJDIR) $(TARGET)
