CPPFLAGS := -Ivisibility -std=c++14
LDFLAGS := -L/usr/lib/x86_64-linux-gnu/mesa/ -L/usr/lib/nvidia-current -lGL -lGLU -lglut

all:
	g++ $(CPPFLAGS) lightvolume.cpp -o lightvolume $(LDFLAGS)


