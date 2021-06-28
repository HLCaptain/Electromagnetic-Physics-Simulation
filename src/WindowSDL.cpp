#include "WindowSDL.h"

/**
 * Window
 * @brief Default constructor.
 * @param title title of the window.
 * @param width width in pixels.
 * @param height height in pixels.
 */
Window::Window(std::string const& title, int width, int height) : _title(title), _width(width), _height(height) {
	if (!init()) {
		this->~Window();
	}
}

/**
 * ~Window
 * @brief Default destructor.
 */
Window::~Window() {
	SDL_FreeSurface(_surface);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

/**
 * init
 * @brief Initializes SDL, creates the window and renderer for the window.
 * @return true if creation successful, false if failed.
 */
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

/**
 * clear
 * @brief Clears the window with a gray background.
 */
void Window::clear() const {
	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
}

/**
 * close
 * @brief Closes the window (calls the destructor).
 */
void Window::close() {
	closed = true;
}