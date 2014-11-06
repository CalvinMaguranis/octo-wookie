#include <iostream>
#include <SDL.h>

#include <string>

// globals
const int __SDL_RENDERER_USE_HW_DRIVERS = -1;
SDL_Window *win;
SDL_Renderer *ren;
SDL_Texture *tex;

// forward declarations
std::string get_res_path(const std::string &path="");
bool init(const char * label, int width, int height);

int main(int argc, char** argv)
{
    if (init("test SDL", 640, 480)==false) {
        return -1;
    } else {
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);

        SDL_Delay(2000);

        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
    return 0;
}

// sets up window and default renderer
bool init(const char * label, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    win = SDL_CreateWindow(label, 50, 50, width, height, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return false;
    }

    ren = SDL_CreateRenderer(win, __SDL_RENDERER_USE_HW_DRIVERS,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_DestroyRenderer(ren);
        SDL_Quit();
        return false;
    }

    std::string res = "../res/simpsons.bmp";
    std::string res_path = get_res_path(res);
    SDL_Surface *bg = SDL_LoadBMP(res_path.c_str());
    if (bg == nullptr) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    tex = SDL_CreateTextureFromSurface(ren, bg);
    SDL_FreeSurface(bg);
    if (tex == nullptr) {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}

#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif
std::string get_res_path(const std::string &path)
{
    std::string base_path;
    const char *base = SDL_GetBasePath();
    if (base == nullptr) {
        // something went wrong
        std::cout << "SDL_GetBasePath error: " << SDL_GetError() << std::endl;
        return "";
    } else {
        base_path = base;
    }
    return base_path + path;
}
