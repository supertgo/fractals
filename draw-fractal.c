#include <SDL2/SDL.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

void draw_lines(SDL_Renderer *renderer, int start_x, int start_y, const char *pattern, double angle) {
    double current_angle = 0;
    int x = start_x;
    int y = start_y;
    unsigned int pattern_length = strlen(pattern);
    int line_length = 5;
    
    if (pattern_length < 100) {
      line_length = 30;
    } else if (pattern_length < 1000) {
      line_length = 10;  
    } else {
      line_length = 5;
    }

    for (unsigned int i = 0; i < pattern_length; i++) {
        char c = pattern[i];
        if (c == 'F') {
            int new_x = x + (int)(line_length * cos(current_angle));
            int new_y = y - (int)(line_length * sin(current_angle));
            SDL_RenderDrawLine(renderer, x, y, new_x, new_y);
            x = new_x;
            y = new_y;
        } else if (c == '+') {
            current_angle += angle;
        } else if (c == '-') {
            current_angle -= angle;
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Thiago Roberto Fractal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    const char *pattern = "FFFF-F+F+F-F-FF-F+F+F-F+FF-F+F+F-F+FF-F+F+F-F-FF-F+F+F-F-FFF-F+F+F-F-FF-F+F+F-F+FF-F+F+F-F+FF-F+F+F-F-FF-F+F+F-F+FFF-F+F+F-F-FF-F+F+F-F+FF-F+F+F-F+FF-F+F+F-F-FF-F+F+F-F+FFF-F+F+F-F-FF-F+F+F-F+FF-F+F+F-F+FF-F+F+F-F-FF-F+F+F-F-FFF-F+F+F-F-FF-F+F+F-F+FF-F+F+F-F+FF-F+F+F-F-FF-F+F+F-FFFF-F+F+F-F-FF-F+F+F-F+FF-F+F+F-F+FF-F+F+F-F-FF-F+F+F-FFF-F+F+F-FF";
    double angle = M_PI / 2.0;

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
      SDL_SetWindowResizable(window, 1);
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      draw_lines(renderer, 500, WINDOW_HEIGHT / 3, pattern, angle);
      SDL_RenderPresent(renderer);
    }

    // SDL_Delay(100000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

