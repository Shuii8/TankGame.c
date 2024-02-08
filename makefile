compilar:
	gcc gwar.c -lm `pkg-config --cflags --libs sdl` -o gwar
	./gwar
