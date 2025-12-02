# Window module makefile

WINDOW_DIR = Window
WINDOW_SRCS = $(WINDOW_DIR)/Window.cpp \
			  $(WINDOW_DIR)/Pane.cpp
WINDOW_OBJS = $(WINDOW_SRCS:.cpp=.o)

# SDL2 flags
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LIBS = $(shell sdl2-config --libs)

# Add SDL2 flags to the compilation
CXXFLAGS += $(SDL2_CFLAGS)
LDFLAGS += $(SDL2_LIBS)

# Rule to compile Window objects
$(WINDOW_DIR)/%.o: $(WINDOW_DIR)/%.cpp $(WINDOW_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Add Window objects to the main objects list
OBJS += $(WINDOW_OBJS)
