CC = g++
CCFLAGS = -c -Wall -std=c++14
LDFLAGS = -lm -L/usr/lib/ -l boost_system -l boost_filesystem -DBOOST_NO_CXX11_SCOPED_ENUMS

CLASSES = FractalDrawer Fractal

OBJS = $(patsubst %, %.o,  $(CLASSES))

FractalDrawer: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o FractalDrawer

%.o: %.cpp
	$(CC) $(CCFLAGS) $*.cpp

depend:
	makedepend -- $(CCFLAGS) -- $(SRCS)

clean:
	rm -rf *.o

prod:
	make FractalDrawer
	rm -rf *.o *.h *.cpp Makefile
	chmod 755 FractalDrawer