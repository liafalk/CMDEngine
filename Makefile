all: main.cpp RenderEngine.cpp
	g++ main.cpp RenderEngine.cpp -std=c++14 -o Render.exe