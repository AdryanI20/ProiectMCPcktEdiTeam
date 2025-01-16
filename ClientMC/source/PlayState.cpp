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

    cpr::Response response = cpr::Get(
        cpr::Url{ "http://"+m_game->getServerLocation() + ":18080/get_map"},
        cpr::Parameters{ {"clientID", std::to_string(m_game->getclientID())} }
    );

    if (response.status_code == 200) {
        auto parsedJson = crow::json::load(response.text);
        auto mapArray = parsedJson["map"];

        for (int y = 0; y < mapArray.size(); ++y) {
            auto jsonRow = mapArray[y];
            for (int x = 0; x < jsonRow.size(); ++x) {
                switch (jsonRow[x].i()) {
                case 0://FREE_SPACE
                    textureManager->Draw("Wall0", x * img_size, y * img_size, 1, renderer);
                    break;
                case 4: { //PLAYER
                    textureManager->Draw("Wall0", x * img_size, y * img_size, 1, renderer);
                    std::string playerPosString = std::to_string(y) + std::to_string(x);
                    if (parsedJson.has(playerPosString)) {
                        Vector2D facingDir = Vector2D(parsedJson[playerPosString][1].i(), parsedJson[playerPosString][2].i());
                        std::string playerTexID = parsedJson[playerPosString][0].s();
                        int angle = 0;
                        if (facingDir == Vector2D(-1, 0))
                            angle = 180;
                        else if (facingDir == Vector2D(1, 0))
                            angle = 0;
                        else if (facingDir == Vector2D(0, 1))
                            angle = 270;
                        else if (facingDir == Vector2D(0, -1))
                            angle = 90;
                        textureManager->Draw("Player"+playerTexID, x * img_size, y * img_size, 1, renderer, angle);
                    }
                }
                    break;
                case 6://BULLET
                    textureManager->Draw("Wall0", x * img_size, y * img_size, 1, renderer);
                    textureManager->Draw("Bullet", x * img_size, y * img_size, 1, renderer);
                    break;
                case 1://DESTRUCTIBIL_WALL
                    textureManager->Draw("Wall1", x * img_size, y * img_size, 1, renderer);
                    break;
                case 2://INDESTRUCTIBIL_WALL
                    textureManager->Draw("Wall2", x * img_size, y * img_size, 1, renderer);
                    break;
                case 3://BOMB_WALL
                    textureManager->Draw("Wall1", x * img_size, y * img_size, 1, renderer);
                    break;
                }
            }
        }
    }

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

    m_game->getTextureManager()->ImageLoad("resources/ship1_small.png", "Player0", m_game->getRenderer());
    m_game->getTextureManager()->ImageLoad("resources/ship2_small.png", "Player1", m_game->getRenderer());
    m_game->getTextureManager()->ImageLoad("resources/ship3_small.png", "Player2", m_game->getRenderer());
    m_game->getTextureManager()->ImageLoad("resources/ship4_small.png", "Player3", m_game->getRenderer());

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
    int moveUpDown = m_game->getInputHandler()->isKeyDown(SDL_SCANCODE_DOWN) - m_game->getInputHandler()->isKeyDown(SDL_SCANCODE_UP);
    int moveLeftRight = m_game->getInputHandler()->isKeyDown(SDL_SCANCODE_RIGHT) - m_game->getInputHandler()->isKeyDown(SDL_SCANCODE_LEFT);
    bool Shoot = m_game->getInputHandler()->isKeyDown(SDL_SCANCODE_Z);
    if (moveUpDown == 0 && moveLeftRight == 0 && Shoot == 0) return;
    auto response = cpr::Put(
        cpr::Url{ "http://"+m_game->getServerLocation()+":18080/player_input" },
        cpr::Parameters{ {"clientID", std::to_string(m_game->getclientID())} },
        cpr::Payload{
            { "upDown", std::to_string(moveUpDown) },
            { "leftRight", std::to_string(moveLeftRight) },
            { "Shoot" , std::to_string(Shoot) }
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
