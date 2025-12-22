CXX=clang++
NM=llvm-nm
OBJDUMP=llvm-objdump
OBJCOPY=llvm-objcopy
STRIP=llvm-strip
SIZE=llvm-size
READELF=llvm-readelf
AR=llvm-ar
AS=llvm-as
LIPO=llvm-lipo
WINDRES=llvm-windres
OTOOL=llvm-otool
RANLIB=llvm-ranlib
CXXFLAGS=-O3 -ffast-math -mcpu=cortex-a76+crypto -flto
LDFLAGS=-flto -fuse-ld=lld -Wl,-O3 -Wl,--strip-all
LDLIBS   := -lre2

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
