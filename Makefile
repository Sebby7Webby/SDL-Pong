all:
	g++ -I src/include/SDL2 -L src/lib -o main main.cpp classes/vector.cpp classes/colour.cpp classes/collision.cpp log/log.cpp -lSDL2main -lSDL2