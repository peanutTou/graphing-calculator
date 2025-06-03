#include "coor_transform.h"


coor_transform::coor_transform():_info(nullptr)
{}

coor_transform::coor_transform(graphInfo *info):_info(info)
{}

//coordiante transfrom single point
//create a matrix and mutiple it by the point
/*
 *      | sclarX     0   |
 *      |   0    -sclarY | 
 * 
 * sclar are defined by size the size of grapthing area divied by the size of the interval  
 */
sf::Vector2f coor_transform::transform(sf::Vector2f pre_coor)
{
    //find sclar
    float sclarX = PLAYGROUND_WIDTH / (_info->_right - _info->_left);
    float sclarY = PLAYGROUND_HEIGHT / (_info->_bottom - _info->_top);

    //find point after coordiante trasnfrom
    float cx = pre_coor.x * sclarX;
    float cy = -pre_coor.y * sclarY;

    //move the point respect to the origin reference point
    cx += _info->_origin.x;
    cy += _info->_origin.y;

    return sf::Vector2f(cx, cy);
}


//coordiante transfrom many points
sf::Vector2f coor_transform::operator()(sf::Vector2f pre_coor)
{
    return transform(pre_coor);
}

//coordiante transfrom single point by operator()
vector<sf::Vector2f> coor_transform::transform(vector<sf::Vector2f> pre_coor)
{
    vector<sf::Vector2f> post_transfrom(pre_coor.size());

    for(int i = 0; i < pre_coor.size(); i++){
        post_transfrom.push_back(transform(pre_coor.at(i)));
    }

    return post_transfrom;
}
//coordiante transfrom many points by operator()
vector<sf::Vector2f> coor_transform::operator()(vector<sf::Vector2f> pre_coor)
{
    return transform(pre_coor);
}