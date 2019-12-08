
VPATH = src:out
source := $(wildcard *.cc)
objs := $(patsubst %.cc,%.o,$(source))

all: $(objs)
	g++ -std=c++17 build/$(objs) -o out/main
*.o: $(source)
	g++ -std=c++17 -c $(source)