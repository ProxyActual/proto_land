#include "Window.h"
#include <stdexcept>
#include <cstring>

Window::Window(const std::string& title, int w, int h) 
    : window(nullptr), renderer(nullptr), texture(nullptr), 
      pixels(nullptr), width(w), height(h), shouldClose(false) {
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(std::string("Failed to initialize SDL: ") + SDL_GetError());
    }

    // Create window
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Quit();
        throw std::runtime_error(std::string("Failed to create window: ") + SDL_GetError());
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error(std::string("Failed to create renderer: ") + SDL_GetError());
    }

    // Create texture for pixel buffer
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
    );

    if (!texture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error(std::string("Failed to create texture: ") + SDL_GetError());
    }

    // Allocate pixel buffer
    pixels = new uint32_t[width * height];
    clear();
}

Window::~Window() {
    if (pixels) {
        delete[] pixels;
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Window::setPixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        uint8_t a = (color & 0x000000FF);
        if(a == 255){
            pixels[y * width + x] = color;
        }else{
            pixels[y * width + x] = color * (a / 255.0f) + pixels[y * width + x] * (1.0f - (a / 255.0f));
        }
    }
}

void Window::clear(uint32_t color) {
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = color;
    }
}

void Window::update() {
    // Update texture with pixel buffer
    SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(uint32_t));
    
    // Clear renderer
    SDL_RenderClear(renderer);
    
    // Copy texture to renderer
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    
    // Present the renderer
    SDL_RenderPresent(renderer);
}

bool Window::isOpen() {
    return !shouldClose;
}

void Window::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            shouldClose = true;
        }
        // Handle other events here if needed
    }
}

void Window::setWindow(int x, int y, int w, int h, uint32_t* buffer) {
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            int bufferIndex = i + j * w;
            if(bufferIndex < w * h){
                setPixel(x+i, y+j, buffer[bufferIndex]);
            }
        }
    }
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}
