#include "graph.h"

graph::graph():_info(nullptr), _ploter()
{

}
graph::graph(graphInfo *info):_info(info), _ploter(info)
{

}

void graph::update(sf::RenderWindow& window)
{
    graph_function(window);
}

void graph::graph_function(sf::RenderWindow& window)
{
    getPoints();
    drawPointes(window);
}

//use ploter get position of each points
void graph::getPoints()
{
    _info->_points = _ploter.cal_points(_info->currentEquation);
}

//draw eachpoint on to the screen
void graph::drawPointes(sf::RenderWindow& window)
{
    if(_info->_points.size() == 0 && _info->currentEquation != ""){
        _info->isCurrentInputValid = false;
        return;
    }

    for(int i = 0; i < _info->_points.size(); i++){
        sf::CircleShape point(PLOT_SIZE);
        point.setFillColor(sf::Color::Red);
        point.setPosition(_info->_points[i]);
        window.draw(point);
    }
    _info->isCurrentInputValid = true;
}
