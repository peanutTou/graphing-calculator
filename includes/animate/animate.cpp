#include "animate.h"

animate::animate(): _windows(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE_NAME), _info(new graphInfo()), _sys(_info)
{}


void animate::startAnimate()
{
    // _info->pushEquation("x * (x + 1) * (x + 2) + 10");
    
    while(_windows.isOpen()){
        sf::Event event;
        int unicode;
        while (_windows.pollEvent(event))
        {
            int lastIndex;
            // check the type of the event...
            switch (event.type)
            {
            // window closed
            // "close requested" event: we close the window
            case sf::Event::Closed:
                cout<<"close event was encountered!"<<endl;
                _windows.close();
                _info->writeInputToHistory();
                break;
            case sf::Event::TextEntered:
                //get the unicode of the input and ignore non-printable characters
                unicode = event.text.unicode;
                if(unicode < 127 && unicode > 31)
                {
                    _info->currentInputing += static_cast<char>(unicode);
                    cout << unicode << endl;
                }
                // key pressed
            case sf::Event::KeyPressed:
                cout << "key press: " << event.key.code << endl;
                cout << "here is Delete: "<<sf::Keyboard::Key::Delete << endl;

                switch (event.key.code)
                {
                case sf::Keyboard::Key::Delete:
                    lastIndex = _info->currentInputing.size() - 1;
                    if(lastIndex > -1){
                        _info->currentInputing.erase(lastIndex);
                    }
                    break;
                case sf::Keyboard::Key::Enter:
                    _info->pushMyInput();
                    break;
                
                default:
                    break;
                }
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
