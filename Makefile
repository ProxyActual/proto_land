include CommandLine/CommandLine.mk
include Window/Window.mk
include AIElement/AICore.mk
include World/World.mk

MAIN_OBJS = main.o \
			$(COMMANDLINE_OBJS) \
			$(WINDOW_OBJS) \
			$(AIELEMENT_OBJS) \
			$(WORLD_OBJS)

main: $(MAIN_OBJS)
	$(CXX) $(MAIN_OBJS) -o main $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f $(MAIN_OBJS)

