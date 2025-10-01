# Makefile for Student Record System
# Author: Abrahim Soleiman
# Purpose: Builds the StudentRecordSystem as a static library and links to test and menu interfaces


# Compiler
CXX = cl

# Compiler flags
CXXFLAGS = /EHsc /W4

# Target names
LIB_NAME = student_record_system.lib
LIB_OBJ = student_record_system.obj

# Main executables
MENU_EXE = menu.exe
TEST_EXE = test.exe

# Source files
MENU_SRC = menu.cpp
TEST_SRC = test.cpp

# Header file
HEADERS = student_record_system.h

# Default target: build all
all: $(LIB_NAME) $(MENU_EXE) $(TEST_EXE)

# Compile the library source into an object
$(LIB_OBJ): student_record_system.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) /c student_record_system.cpp

# Build the library
$(LIB_NAME): $(LIB_OBJ)
	lib /OUT:$(LIB_NAME) $(LIB_OBJ)

# Link the menu interface to the library
$(MENU_EXE): $(MENU_SRC) $(LIB_NAME)
	$(CXX) $(CXXFLAGS) $(MENU_SRC) $(LIB_NAME) /Fe$(MENU_EXE)

# Link the test interface to the library
$(TEST_EXE): $(TEST_SRC) $(LIB_NAME)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(LIB_NAME) /Fe$(TEST_EXE)

# Clean all built files
clean:
	del /Q *.obj *.lib *.exe
