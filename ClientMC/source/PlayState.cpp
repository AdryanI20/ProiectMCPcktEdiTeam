#include "PlayState.h"
#include <iostream>
#include "Game.h"

const std::string PlayState::playID = "PLAY";

std::string PlayState::getStateID() const {
    return playID;
}

void PlayState::Update() {
    //for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
    //    iterator->second->Update(m_game);
    //}
}

void PlayState::Render() {
    int img_size = 64;
    SDL_Renderer* renderer = m_game->getRenderer();
    SDL_SetRenderDrawColor(renderer, 33, 149, 199, 255);

    TextureManager* textureManager = m_game->getTextureManager();

    //
    cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/get_map" });

    if (response.status_code == 200) {
        size_t index = 0;
        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 30; ++j) {
                switch (static_cast<int>(response.text[index++])) {
                case 0://FREE_SPACE
                    textureManager->Draw("Wall0", j * img_size, i * img_size, 1, renderer);
                    break;
                case 4://PLAYER
                    textureManager->Draw("Wall0", j * img_size, i * img_size, 1, renderer);
                    textureManager->Draw("Player1", j * img_size, i * img_size, 1, renderer);
                    break;
                case 6://BULLET
                    textureManager->Draw("Bullet", j * img_size, i * img_size, 1, renderer);
                    break;
                case 1://DESTRUCTIBIL_WALL
                    textureManager->Draw("Wall1", j * img_size, i * img_size, 1, renderer);
                    break;
                case 2://INDESTRUCTIBIL_WALL
                    textureManager->Draw("Wall2", j * img_size, i * img_size, 1, renderer);
                    break;
                case 3://BOMB_WALL
                    textureManager->Draw("Wall1", j * img_size, i * img_size, 1, renderer);
                    break;
                }
                //std::cout << static_cast<int>(response.text[index++]) << " ";
            }
        }
    }
    //

    //std::pair<int, int> mapSize = m_game->getMap()->getSize();
    //const std::vector<std::vector<CellType>>& mapData = m_game->getMap()->getMap();
    //for (int i = 0; i < mapSize.first; ++i) {
    //    for (int j = 0; j < mapSize.second; ++j) {
    //        switch (mapData[i][j]) {
    //        case FREE_SPACE:
    //            textureManager->Draw("Wall0", j * img_size, i * img_size, 1, renderer);
    //            break;
    //        case PLAYER:
    //            textureManager->Draw("Wall0", j * img_size, i * img_size, 1, renderer);
    //            break;
    //        case BULLET:
    //            textureManager->Draw("Wall0", j * img_size, i * img_size, 1, renderer);
    //            break;
    //        case DESTRUCTIBIL_WALL:
    //            textureManager->Draw("Wall1", j * img_size, i * img_size, 1, renderer);
    //            break;
    //        case INDESTRUCTIBIL_WALL:
    //            textureManager->Draw("Wall2", j * img_size, i * img_size, 1, renderer);
    //            break;
    //        case BOMB_WALL:
    //            textureManager->Draw("Wall1", j * img_size, i * img_size, 1, renderer);
    //            break;
    //        }
    //    }
    //}

    //for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++)
    //{
    //    iterator->second->Draw(m_game->getTextureManager(), m_game->getRenderer());
    //}
}

bool PlayState::onEnter() {
    std::cout << "entering Play" << std::endl;

    m_game->getTextureManager()->ImageLoad("resources/cannonBall_small.png", "Bullet", m_game->getRenderer());

    m_game->getTextureManager()->ImageLoad("resources/water_small.png", "Wall0", m_game->getRenderer());
    m_game->getTextureManager()->ImageLoad("resources/brick_red_small.png", "Wall1", m_game->getRenderer());
    m_game->getTextureManager()->ImageLoad("resources/brick_grey_small.png", "Wall2", m_game->getRenderer());

    m_game->getTextureManager()->ImageLoad("resources/ship1_small.png", "Player1", m_game->getRenderer());
    m_game->getTextureManager()->ImageLoad("resources/ship2_small.png", "Player2", m_game->getRenderer());
    m_game->getTextureManager()->ImageLoad("resources/ship3_small.png", "Player3", m_game->getRenderer());
    m_game->getTextureManager()->ImageLoad("resources/ship4_small.png", "Player4", m_game->getRenderer());

    //getMap();

    return true; //success
}

bool PlayState::onExit() {
    //for (objs_it iterator = gameObjects.begin(); iterator != gameObjects.end(); iterator++) {
    //    iterator->second->Clean();
    //}
    //gameObjects.clear();

    std::cout << "exiting Play" << std::endl;
    return true;
}

void PlayState::onKeyDown(SDL_Event* e) {
    //trimite input catre server
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:18080/player_input" },
        cpr::Payload{
            { "clientID", std::to_string(m_game->getclientID()) },
            { "upDown", std::to_string(m_game->getInputHandler()->isKeyJustPressed(SDL_SCANCODE_DOWN) - m_game->getInputHandler()->isKeyJustPressed(SDL_SCANCODE_UP)) },
            { "leftRight", std::to_string(m_game->getInputHandler()->isKeyJustPressed(SDL_SCANCODE_RIGHT) - m_game->getInputHandler()->isKeyJustPressed(SDL_SCANCODE_LEFT)) },
            { "Shoot" , std::to_string(m_game->getInputHandler()->isKeyJustPressed(SDL_SCANCODE_Z)) }
        }  
    );
    if (response.status_code != 201) {
        std::cout << "error with input";
    }
    //std::cout << "Key Pressed: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
}

void PlayState::onKeyUp(SDL_Event* e) {
    //std::cout << "Key Released: " << SDL_GetKeyName(e->key.keysym.sym) << std::endl;
}

void PlayState::onMouseButtonUp(SDL_Event* e) {

}

void PlayState::onMouseButtonDown(SDL_Event* e) {

}

void PlayState::onMouseMove(SDL_Event* e) {

}
