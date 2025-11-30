

WORLD_DIR = World
WORLD_OBJS = \
	$(WORLD_DIR)/WorldBase.o \
	$(WORLD_DIR)/Location.o \

Location.o: Location.cpp Location.h
	$(CXX) $(CXXFLAGS) -c Location.cpp -o Location.o

WorldBase.o: WorldBase.cpp WorldBase.h
	$(CXX) $(CXXFLAGS) -c WorldBase.cpp -o WorldBase.o
