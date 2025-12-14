AIRCRAFT_SIM_OBJS = $(AIRCRAFT_SIM_DIR)/AircraftSimulation.o \
					$(AIRCRAFT_SIM_DIR)/Aircraft.o  \
					$(AIRCRAFT_SIM_DIR)/Instraments/Altimeter.o

AIRCRAFT_SIM_DIR = AircraftSimulation

$(AIRCRAFT_SIM_DIR)/%.o: $(AIRCRAFT_SIM_DIR)/%.cpp $(AIRCRAFT_SIM_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@