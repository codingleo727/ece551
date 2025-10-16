# ---- config ----
CXX      := g++
CXXFLAGS := -std=c++98 -Wall -Werror -pedantic -O2 -MMD -MP

TARGET   := circles
SRCS     := main.cpp circle.cpp point.cpp
OBJS     := $(SRCS:.cpp=.o)
DEPS     := $(OBJS:.o=.d)

# ---- build rules ----
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile each .cpp to .o (deps generated via -MMD -MP)
%.o: %.cpp circle.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- housekeeping ----
.PHONY: clean run
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

run: $(TARGET)
	./$(TARGET)

# Include auto-generated dependency files (safe if missing)
-include $(DEPS)
