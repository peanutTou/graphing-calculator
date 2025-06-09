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
    bool debug = false;
    if(debug){
        cout << "coor_transform::transform: " << pre_coor.x << " " << pre_coor.y << endl;
    }

    //find sclar
    float sclarX = PLAYGROUND_WIDTH / (_info->_right - _info->_left);
    float sclarY = PLAYGROUND_HEIGHT / (_info->_top - _info->_bottom);

    //find each point location respect to the point 0, 0
    float cx = (pre_coor.x - _info->_left) * sclarX;
    float cy = (-pre_coor.y - _info->_top) * sclarY;

    //move the point respect to the origin reference point
    cy += PLAYGROUND_HEIGHT;

    return sf::Vector2f(cx, cy);
}


//coordiante transfrom many points
sf::Vector2f coor_transform::operator()(sf::Vector2f pre_coor)
{
    return transform(pre_coor);
}

//coordiante transfrom single point by operator()
Vector<sf::Vector2f> coor_transform::transform(Vector<sf::Vector2f> pre_coor)
{
    Vector<sf::Vector2f> post_transfrom(pre_coor.size());

    for(int i = 0; i < pre_coor.size(); i++){
        post_transfrom.push_back(transform(pre_coor.at(i)));
    }

    return post_transfrom;
}
//coordiante transfrom many points by operator()
Vector<sf::Vector2f> coor_transform::operator()(Vector<sf::Vector2f> pre_coor)
{
    return transform(pre_coor);
}