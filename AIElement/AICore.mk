# AIElement module makefile

AIELEMENT_DIR = AIElement
AIELEMENT_SRCS = $(AIELEMENT_DIR)/AICore.cpp
AIELEMENT_OBJS = $(AIELEMENT_SRCS:.cpp=.o)

# Rule to compile AIElement objects
$(AIELEMENT_DIR)/%.o: $(AIELEMENT_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Add AIElement objects to the main objects list
OBJS += $(AIELEMENT_OBJS)
