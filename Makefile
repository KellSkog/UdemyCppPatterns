
VPATH = src:out
source := $(wildcard *.cc)
objs := $(patsubst %.cc,%.o,$(source))

all: $(objs)
	g++ -std=c++17 $(objs) -o main
*.o: $(source)
	g++ -std=c++17 -c $(source)