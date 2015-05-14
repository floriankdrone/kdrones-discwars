//
//  Player.cpp
//  Game
//
//  Created by Florian D Dutronc on 1/22/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include "Player.h"

#include <iostream>

#include "Player.h"
#include "InputHandler.h"
#include "Game.h"
#include <SDL2_mixer/SDL_mixer.h>

Player::Player(const LoaderParams* pParams, int zoneWidthStart, int zoneWidthEnd) : SDLGameObject(pParams)
{
    std::cout << "Player created" << std::endl;
    m_currentFrame = 0;
    myDisc = new Disc(new LoaderParams(m_position.getX() + (m_width / 2) - (DISC_RAD / 2), m_position.getY()+(m_height/2) - (DISC_RAD/2), DISC_RAD, DISC_RAD, "disc"));
    hasDisc = true;
    m_zoneWidthEnd = zoneWidthEnd;
    m_zoneWidthStart = zoneWidthStart;
    m_health = 100;
}

Player::~Player()
{
    std::cout << "Player destructed" << std::endl;
}

void Player::draw()
{
    Vector2D* target = TheInputHandler::Instance()->getMousePosition();
    if (target->getX() < m_position.getX()) {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
    }
    else
    {
        TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
    }
    
    if (!hasDisc) {
        myDisc->draw();
    }
}

void Player::update()
{
    if (m_health <= 0) {
        std::cout << "Player died, game will end now. Thank you for playing bitch" << std::endl;
        TheGame::Instance()->quit();
    }
    
    handleInput();
    
    if (!hasDisc) {
        myDisc->update();
        
        if (myDisc->shouldReturnToPlayer())  {
            Vector2D armPosition(m_position.getX() + (m_width / 2) - (DISC_RAD / 2), m_position.getY()+(m_height/2) - (DISC_RAD/2));
            myDisc->returnToPlayer(armPosition);
        }
        if (discHasReturned()) {
            myDisc->caughtBack();
            hasDisc = true;
        }
    }
    
    SDLGameObject::update();
}

void Player::clean()
{
    myDisc->clean();
    SDLGameObject::clean();
}

void Player::handleInput()
{
    m_velocity.setX(0);
    m_velocity.setY(0);
    
    if (TheInputHandler::Instance()->isMouseButtonReleased()) {
        throwDisc();
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
        goRight();
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
        goLeft();
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
        goUp();
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
        goDown();
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
        myDisc->shouldReturnToPlayer(true);
    }
}

bool Player::throwDisc()
{
    std::cout << "Will try to throw Disc" << std::endl;
    if (hasDisc)
    {
        if (!TheTextureManager::Instance()->load("/Users/floriandutronc/Desktop/SDLDevelopment/SDLDevelopment/SDLDevelopment/assets/disc1.png", "disc", TheGame::Instance()->getRenderer())) {
            std::cout << "Problem throwing disc" << std::endl;
            return false;
        }
        Vector2D* target = TheInputHandler::Instance()->getMousePosition();
        if (target->getX() < m_position.getX()) {
            std::cout << "arm not the same" << std::endl;
            Vector2D test(m_position.getX() - DISC_RAD, m_position.getY()+(m_height/2) - (DISC_RAD/2));
            myDisc->justThrown(test);
        }
        else
        {
            Vector2D test(m_position.getX() + m_width + DISC_RAD, m_position.getY()+(m_height/2) - (DISC_RAD/2));
            myDisc->justThrown(test);
        }
        //Vector2D armPosition(m_position.getX() + (m_width / 2) - (DISC_RAD / 2), m_position.getY()+(m_height/2) - (DISC_RAD/2));
        hasDisc = false;
        return true;
    }
    std::cout << "Cannot Throw disc" << std::endl;
    return false;
}

bool Player::discHasReturned()
{
    if (!hasDisc) {
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;
        
        leftA = m_position.getX();
        rightA = m_position.getX() + m_width;
        topA = m_position.getY();
        bottomA = m_position.getY() + m_height;
        
        leftB = myDisc->getPosition().getX();
        rightB = myDisc->getPosition().getX() + myDisc->getWidth();
        topB = myDisc->getPosition().getY();
        bottomB = myDisc->getPosition().getY() + myDisc->getHeight();
        
        if (bottomA <= topB) { return false; }
        if (topA >= bottomB) { return false; }
        if (rightA <= leftB) { return false; }
        if (leftA >= rightB) { return false; }
    }
    std::cout << "Disc has returned" << std::endl;
    return true;
}

bool Player::goRight()
{
    m_velocity.setX(2);
    return true; 
}

bool Player::goLeft()
{
    if (m_position.getX() < myDisc->getWidth() + m_zoneWidthStart) {
        return false;
    }
    m_velocity.setX(-2);
    return true;
}

bool Player::goUp()
{
    if (m_position.getY() < myDisc->getHeight()) {
        return false;
    }
    m_velocity.setY(-2);
    return true;
}

bool Player::goDown()
{
    if (m_position.getY() + m_height > TheGame::Instance()->getWindowHeight()) {
        return false;
    }
    m_velocity.setY(2);
    return true;
}

void Player::dies()
{
    m_health = 0;
}