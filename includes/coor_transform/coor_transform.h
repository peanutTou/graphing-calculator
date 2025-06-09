#ifndef COOR_TRANSFORM_H
#define COOR_TRANSFORM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../vector/vector_class.h"

#include "../constants.h"
#include "../graphInfo/graphInfo.h"
using namespace std;


class coor_transform{
public:
    coor_transform();
    coor_transform(graphInfo *info);

    //transform functions
    sf::Vector2f transform(sf::Vector2f pre_coor);
    sf::Vector2f operator()(sf::Vector2f pre_coor);
    vector<sf::Vector2f> transform(vector<sf::Vector2f> pre_coor);
    vector<sf::Vector2f> operator()(vector<sf::Vector2f> pre_coor);
private:
    graphInfo *_info;
};






#endif