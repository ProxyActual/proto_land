include CommandLine/CommandLine.mk
include Window/Window.mk
include World/World.mk
include GraphicsWindow/GraphicsWindow.mk

MAIN_OBJS = $(COMMANDLINE_OBJS) \
			$(WINDOW_OBJS) \
			$(WORLD_OBJS)

main: $(MAIN_OBJS) main.o
	$(CXX) $(MAIN_OBJS) main.o -o main $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

WindowTest: WindowTesting.o $(WINDOW_OBJS)
	$(CXX) $(WINDOW_OBJS) WindowTesting.o -o WindowTest $(LDFLAGS)

WindowTesting.o: WindowTesting.cpp
	$(CXX) $(CXXFLAGS) -c WindowTesting.cpp -o WindowTesting.o

Space_Trader: Space_Trader.o $(GRAPHICS_OBJS)
	$(CXX) Space_Trader.o $(GRAPHICS_OBJS) -o Space_Trader $(LDFLAGS)

Space_Trader.o: Space_Trader.cpp
	$(CXX) $(CXXFLAGS) -c Space_Trader.cpp -o Space_Trader.o

clean:
	rm -f	$(MAIN_OBJS) \
			$(GRAPHICS_OBJS) \
			main.o WindowTesting.o WindowTest main Space_Trader