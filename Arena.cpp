//
//  Arena.cpp
//  Game
//
//  Created by Florian D Dutronc on 5/26/15.
//  Copyright (c) 2015 Kdrone. All rights reserved.
//

#include "Arena.h"

#include <iostream>

Arena::Arena()
{}

Arena::~Arena()
{}

bool Arena::createArenaFromFile(const char* arenaName)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("/Users/floriandutronc/Desktop/Game/Game/assets/arenas.xml");
    tinyxml2::XMLNode* pArenas = doc.FirstChildElement("ARENAS");
    tinyxml2::XMLElement* pArena = pArenas->FirstChildElement("ARENA");
    std::cout << pArena->Value() << std::endl;
    std::cout << pArena->Attribute("name") << std::endl;
    while (pArena->Attribute("name") == arenaName) {
        pArena->NextSiblingElement();
    }
    std::cout << "Arena found!" << std::endl;
    m_maxNumOfPlayers = std::atoi(pArena->Attribute("maxNumOfPlayers"));
    m_with = std::atoi(pArena->Attribute("width"));
    m_height = std::atoi(pArena->Attribute("height"));
    m_background = pArena->Attribute("background");
    tinyxml2::XMLElement* pWaitpoints = pArena->FirstChildElement("WAYPOINTS");
    for (tinyxml2::XMLElement* element = pWaitpoints->FirstChildElement("waypoint"); element != NULL ; element = element->NextSiblingElement()) {
        const tinyxml2::XMLElement* coordinate = element->FirstChildElement("coordinate");
        const tinyxml2::XMLElement* xElement = coordinate->FirstChildElement("x");
        const tinyxml2::XMLElement* yElement = coordinate->FirstChildElement("y");
        int x =0;
        int y =0;
        xElement->QueryIntText( &x );
        yElement->QueryIntText( &y );
        Coordinate c(x, y);
        m_waypoints.push_back(c);
        std::cout << "Waypoint SET at coordinates= " << x << "," << y << std::endl;
    }
    tinyxml2::XMLElement* pDeadzones = pArena->FirstChildElement("DEADZONES");
    for (tinyxml2::XMLElement* element = pDeadzones->FirstChildElement("deadzone"); element != NULL ; element = element->NextSiblingElement()) {
        const tinyxml2::XMLElement* coordinate = element->FirstChildElement("coordinate");
        const tinyxml2::XMLElement* xElement = coordinate->FirstChildElement("x");
        const tinyxml2::XMLElement* yElement = coordinate->FirstChildElement("y");
        int x =0;
        int y =0;
        xElement->QueryIntText( &x );
        yElement->QueryIntText( &y );
        Coordinate c(x, y);
        const tinyxml2::XMLElement* widthElement = element->FirstChildElement("width");
        const tinyxml2::XMLElement* heightElement = element->FirstChildElement("height");
        int width = 0;
        int height = 0;
        widthElement->QueryIntText(&width);
        heightElement->QueryIntText(&height);
        Deadzone deadzone(c, width, height);
        m_deadzones.push_back(deadzone);
        std::cout << "Deadzone SET at coordinates= " << x << "," << y << " with width of " << width << " and height of " << height << std::endl;
    }
    return true;
}

std::string Arena::getBackground()
{
    return m_background;
}

std::vector<Coordinate> Arena::getWaypoints()
{
    return m_waypoints;
}

std::vector<Deadzone> Arena::getDeadzones()
{
    return m_deadzones;
}