build:
	@gcc -o out/rps-sim -lSDL2 -lm -I/usr/include/SDL2 src/*.c
	@cp -r res out/res

run:
	@./out/rps-sim
