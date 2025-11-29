COMMANDLINE_DIR = CommandLine
COMMANDLINE_OBJS = \
	$(COMMANDLINE_DIR)/CommandManager.o \
	$(COMMANDLINE_DIR)/Input.o \


CommandManager.o: CommandManager.cpp CommandManager.h
	$(CXX) $(CXXFLAGS) -c CommandManager.cpp -o CommandManager.o

Input.o: Input.cpp Input.h
	$(CXX) $(CXXFLAGS) -c Input.cpp -o Input.o