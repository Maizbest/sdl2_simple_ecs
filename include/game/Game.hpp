#ifndef BD13B8D7_C105_48E8_AF90_FA2539C26382
#define BD13B8D7_C105_48E8_AF90_FA2539C26382

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running(){return isRunning;};

private:
    int counter = 0;
    bool isRunning = false;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif /* BD13B8D7_C105_48E8_AF90_FA2539C26382 */
