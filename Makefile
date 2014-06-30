#
# source files
srcfiles 	:= $(wildcard src/**/*.cpp)
obj-suffix      := o
#
# object files
objects         := $(patsubst %.cpp, %.$(obj-suffix), $(srcfiles))

CXX = clang++
CXXFLAGS = -g 
INCLUDES = -Iinclude
LDFLAGS = 

.PHONY: clean clobber distclean

# Target:
#
target 	   := numpro


all:: $(target)

# Production rules:  how to make the target - depends on library configuration
$(target): $(objects)
	@echo "  LD  "$@
	@$(CXX) $(INCLUDES) $(CXXFLAGS) $(objects) $(LDFLAGS) -o $@ 

%.o: %.cpp
	@echo "  CXX  "$@
	@$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< $(LDFLAGS) -o $@

# Useful rules.
clean:
	@rm -f $(objects) *~ .depend

clobber:
	@$(MAKE) clean
	@rm -f $(target)

distclean:
	@$(MAKE) clobber


