#include "game/Game.hpp"
#include "game/TextureManager.hpp"
#include "game/GameObject.hpp"
#include <vector>

std::vector<GameObject *> objects;
SDL_Rect srcRect, destRect;

Game::Game(/* args */)
{
    std::cout << "Game instantiated." << std::endl;
}

Game::~Game()
{
    clean();
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Initialized" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created succesfully." << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
            std::cout << "Renderer created succesfully." << std::endl;
        }
        isRunning = true;

        objects.push_back(new GameObject("assets/man.png", renderer, 0, 0));
        objects.push_back(new GameObject("assets/man.png", renderer, 0, 32));
        objects.push_back(new GameObject("assets/man.png", renderer, 0, 64));
    }

    SDL_SetMainReady();
}

void Game::update()
{
    counter++;
    for (auto &obj : objects)
    {
        obj->update();
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    ///----- main render

    SDL_SetRenderDrawColor(renderer, 130, 230, 60, 255);

    for (auto &obj : objects)
    {
        obj->render();
    }

    /// ------
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Game cleaned succesfully." << std::endl;
}