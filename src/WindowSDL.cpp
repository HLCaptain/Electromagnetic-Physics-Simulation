#include "WindowSDL.h"

/// <summary>
/// Creates window object if able to, but destroys it if something is wrong.
/// </summary>
/// <param name="title"></param>
/// <param name="width"></param>
/// <param name="height"></param>
Window::Window(std::string const& title, int width, int height) : _title(title), _width(width), _height(height) {
	if (!init()) {
		this->~Window();
	}
}

Window::~Window() {
	SDL_FreeSurface(_surface);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Failed to Initialize SDL." << std::endl;
		closed = true;
		return false;
	}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

	if (_window == nullptr) {
		std::cerr << "Failed to create Window." << std::endl;
		closed = true;
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (_renderer == nullptr) {
		std::cerr << "Failed to create Renderer." << std::endl;
		closed = true;
		return false;
	}

	closed = false;
	clear();

	return true;
}

void Window::clear() const {
	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
}

void Window::close() {
	this->~Window();
}