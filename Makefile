	CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14 -MMD

	UNIT_TESTS = pe-vector-tests
OBJS = main.o
DEPS = $(OBJS:.o=.d)

$(UNIT_TESTS): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(UNIT_TESTS)
	./$(UNIT_TESTS)

test: run

clean:
	-@$(RM) $(UNIT_TESTS)
	-@$(RM) $(OBJS)
	-@$(RM) $(DEPS)

.PHONY: run test clean

-include $(DEPS)
