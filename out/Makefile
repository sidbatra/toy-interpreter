CXX = g++
CFLAGS = -g
LDFLAGS =
OBJS = #NdArray.o FactoredMDP.o xmlParser.o

OPTS = $(OBJS) $(CFLAGS) $(LDFLAGS)

#default: depend features

$(OBJS): %.o : %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<

inter: $(OBJS) out.cpp
	$(CXX) -o out out.cpp $(OPTS)

depend:
	$(CXX) $(CFLAGS) -MM *.cpp > Makefile.dep

clean:
	rm -f *.o inter

include Makefile.dep
