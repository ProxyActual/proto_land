# AIElement module makefile

AIELEMENT_DIR = AIElement

AIELEMENT_OBJS = \
	$(AIELEMENT_DIR)/AICore.o \

AICore.o: AICore.cpp AICore.h
	$(CXX) $(CXXFLAGS) -c AICore.cpp -o AICore.o
