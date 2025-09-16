TARGET = compito

# Compilatore e flags
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

# File sorgenti
SRCS = compito.cpp grafo.cc tipo.cpp

# File oggetto corrispondenti
OBJS = $(SRCS:.cpp=.o)

# Regola principale: costruisce l'eseguibile
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regole per compilare i .o dai .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pulizia dei file temporanei
clean:
	rm -f $(OBJS) $(TARGET)