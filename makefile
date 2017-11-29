CC = g++
C_FLAGS = -g
EXEC = cache_sim
TEST = test.o
OBJS = cache.o
MAIN = parse_input.o
INPUT = associativityTest blockTest lruTest repetitionTest writeBackTest

all: $(OBJS) $(MAIN)
	$(CC) $(C_FLAGS) -o $(EXEC) $^
test:  $(TEST) $(OBJS)
	$(CC) $(C_FLAGS) -o $@ $^
run: all
	for N in $(INPUT); do ./cache_sim $$N; done
verbose: all
	for N in $(INPUT); do ./cache_sim $$N verbose; done
clean:
	rm *.o $(EXEC) test
