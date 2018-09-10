CC = g++
SRC = rt.cpp vector.cpp sphere.cpp light.cpp plane.cpp object.cpp box.cpp
TARGET = rt

all:
	$(CC) $(SRC) -lm -o $(TARGET)
png:
	convert img.ppm img.png
clean:
	rm -f *.o $(TARGET)
default:
	./rt default.txt img.ppm
