TARGET = e10

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o,$(SRC))


CXXFLAGS = -c -g -Wall

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.c
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(TARGET)
