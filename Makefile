
SRCS = $(wildcard src/*.cpp)
HRDS = $(wildcard include/*.h)
OBJS = $(addsuffix .o, $(basename $(SRCS)))
TARGET = libkm_utility.a
OUTPUT = output

.PHONY: all clean
all: $(TARGET)
	mkdir -p $(OUTPUT)/include
	mkdir -p $(OUTPUT)/lib
	cp $(TARGET) $(OUTPUT)/lib/
	cp $(HRDS) $(OUTPUT)/include/
	rm $(TARGET)
	rm src/*.o
	@echo "DONE"

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

clean:
	rm -fr $(TARGET)
	rm -fr *.o
	rm -fr $(OUTPUT)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

