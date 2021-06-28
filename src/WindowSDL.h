#ifndef WINDOWSDL_H
#define WINDOWSDL_H

#include <string>
#include <iostream>
#include <SDL.h>

class Window {
	std::string _title;
	int _width;
	int _height;
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
	bool closed;

	bool init();

public:
	Window(std::string const& title = "Default Title" , int width = 800, int height = 600);
	~Window();

	void clear() const;
	void close();

	SDL_Renderer* getRenderer() { return _renderer; }
	int getHeight() { return _height; }
	int getWidth() { return _width; }
	std::string getTitle() const { return _title; }
	bool isClosed() { return closed; }
};

#endif // WINDOWSDL_H

