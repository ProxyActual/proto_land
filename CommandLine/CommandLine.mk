COMMANDLINE_DIR = CommandLine
COMMANDLINE_OBJS = $(COMMANDLINE_DIR)/Input.o

Input.o: Input.cpp
	$(CXX) $(CXXFLAGS) -c Input.cpp -o Input.o