GRAPHICS_OBJS = $(GRAPHICS_DIR)/GraphicsWindow.o \
				$(GRAPHICS_DIR)/GraphicsItem.o

GRAPHICS_DIR = GraphicsWindow

$(GRAPHICS_DIR)/%.o: $(GRAPHICS_DIR)/%.cpp $(GRAPHICS_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

