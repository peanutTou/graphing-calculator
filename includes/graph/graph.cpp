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

    if(_info->hasChanged){
        _info->_points = _ploter.cal_points(_info->currentEquation);
    }
}


//draw eachpoint on to the screen
//if no avaliable points in the container, and current input is not empty, assume this equation is unvalid in this interval
void graph::drawPointes(sf::RenderWindow& window)
{
    if(_info->_points.size() == 0 && _info->currentEquation != ""){
        _info->isCurrentInputValid = false;
        return;
    }

    sf::Vertex vertices[2];
    sf::Vertex* vertices_ptr_front = vertices;
    sf::Vertex* vertices_ptr_end = vertices + 1;
    sf::CircleShape point(PLOT_SIZE);
    point.setFillColor(sf::Color::Red);

    for(int i = 0; i < _info->_points.size(); i++){
        point.setPosition(_info->_points[i]);
        window.draw(point);

        //use vertices create a line between two points
        if(!isnan(_info->_points[i].y) && i < _info->_points.size() - 1)
        {
            *vertices_ptr_front = sf::Vertex(_info->_points[i], sf::Color::Red);
            *vertices_ptr_end = sf::Vertex(_info->_points[i + 1], sf::Color::Red);
            window.draw(vertices, 2, sf::Lines);
        }

    }

    _info->isCurrentInputValid = true;
}
