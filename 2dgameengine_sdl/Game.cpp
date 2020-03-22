#pragma once
#include <iostream>
#include "Constans.h"
#include "Game.h"
#include "./AssetManager.h"
#include "./TransformComponent.h"
#include "./SpriteComponent.h"
#include "./KeyboardControlComponent.h"
#include "./glm/glm.hpp"
#include "./Map.h";


EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
Map* map;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }
    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
    // Start including new assets to the assetmanager list

    //Entity& newEntity(manager.AddEntity("projectile"));
    // Itt adunk hozza az assetjeink map tipusu tarolojaba egy texture-t , ami kap egy index nevet es egy eleresi utat egy kephez
    assetManager->AddTexture("tank-image", std::string("../assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("../assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("../assets/images/radar.png").c_str());
    assetManager->AddTexture("jungle-tile", std::string("../assets/tilemaps/jungle.png").c_str());

    map = new Map("jungle-tile", 1, 32);
    map->LoadMap("../assets/tilemaps/jungle.map", 25, 20);

    // Start including entities and also components to them
    // Itt implementaljuk az uj entity-t a aminek ket komponenese lesz , egy transform a mozgashoz es egy sprite a hozza betoltott kep felhasznalasahoz
    Entity& tankEntity(manager.AddEntity("tank"));
    tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");

    Entity& chopperEntity(manager.AddEntity("chopper"));
    chopperEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true , false);
    chopperEntity.AddComponent<KeyboardControlComponent>("up" , "right" , "left" , "down" , "space");

    Entity& radarEntity(manager.AddEntity("Radar"));
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT: {
        isRunning = false;
        break;
    }
    case SDL_KEYDOWN: {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
        }
    }
    default: {
        break;
    }
    }
}

void Game::Update() {
    // Wait until 16ms has ellapsed since the last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

    // Delta time is the difference in ticks from last frame converted to secomds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    // runs and calls its every type of entities update method
    manager.Update(deltaTime);

}   

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    // runs and calls its every type of entities update method
    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


