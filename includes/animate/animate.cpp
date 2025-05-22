#include "animate.h"

animate::animate(): _windows(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE_NAME), _info(new graphInfo()), _sys(_info)
{}


void animate::startAnimate()
{
    while(_windows.isOpen()){
        sf::Event event;
        while (_windows.pollEvent(event))
        {
            // check the type of the event...
            switch (event.type)
            {
            // window closed
            // "close requested" event: we close the window
            case sf::Event::Closed:
                cout<<"close event was encountered!"<<endl;
                _windows.close();
                break;

                // key pressed
            case sf::Event::KeyPressed:
                cout<<"a key was pressed..."<<endl;
                //...
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                else
                    std::cout<<"left button?"<<std::endl;
                break;
            default:
                break;
            }
        }

        //do update();
        _sys.update(_windows);
    }
}


animate::~animate(){
    delete _info;
}