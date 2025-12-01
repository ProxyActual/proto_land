include CommandLine/CommandLine.mk
include Window/Window.mk
include AIElement/AICore.mk
include World/World.mk

MAIN_OBJS = $(COMMANDLINE_OBJS) \
			$(WINDOW_OBJS) \
			$(AIELEMENT_OBJS) \
			$(WORLD_OBJS)

main: $(MAIN_OBJS) main.o
	$(CXX) $(MAIN_OBJS) main.o -o main $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

WindowTest: WindowTesting.o $(WINDOW_OBJS)
	$(CXX) $(WINDOW_OBJS) WindowTesting.o -o WindowTest $(LDFLAGS)

WindowTesting.o: WindowTesting.cpp
	$(CXX) $(CXXFLAGS) -c WindowTesting.cpp -o WindowTesting.o

clean:
	rm -f $(MAIN_OBJS) main.o WindowTesting.o WindowTest main