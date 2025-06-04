#include "animate.h"

animate::animate(): _windows(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE_NAME), _info(new graphInfo()), _sys(_info)
{}


void animate::startAnimate()
{
    // _info->pushEquation("x * (x + 1) * (x + 2) + 10");
    
    while(_windows.isOpen()){
        sf::Event event;
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

                // key pressed
            case sf::Event::KeyPressed:
                cout << "key press: " << event.key.code << endl;
                cout << "here is Delete: "<<sf::Keyboard::Key::Delete << endl;

                switch (event.key.code)
                {
                case sf::Keyboard::Key::A:
                    _info->currentInputing += 'a';
                    break;
                case sf::Keyboard::Key::B:
                    _info->currentInputing += 'b';
                    break;
                case sf::Keyboard::Key::C:
                    _info->currentInputing += 'c';
                    break;
                case sf::Keyboard::Key::D:
                    _info->currentInputing += 'd';
                    break;
                case sf::Keyboard::Key::E:
                    _info->currentInputing += 'e';
                    break;
                case sf::Keyboard::Key::F:
                    _info->currentInputing += 'f';
                    break;
                case sf::Keyboard::Key::G:
                    _info->currentInputing += 'g';
                    break;
                case sf::Keyboard::Key::H:
                    _info->currentInputing += 'h';
                    break;
                case sf::Keyboard::Key::I:
                    _info->currentInputing += 'i';
                    break;
                case sf::Keyboard::Key::J:
                    _info->currentInputing += 'j';
                    break;
                case sf::Keyboard::Key::K:
                    _info->currentInputing += 'k';
                    break;
                case sf::Keyboard::Key::L:
                    _info->currentInputing += 'l';
                    break;
                case sf::Keyboard::Key::M:
                    _info->currentInputing += 'm';
                    break;
                case sf::Keyboard::Key::N:
                    _info->currentInputing += 'n';
                    break;
                case sf::Keyboard::Key::O:
                    _info->currentInputing += 'o';
                    break;
                case sf::Keyboard::Key::P:
                    _info->currentInputing += 'p';
                    break;
                case sf::Keyboard::Key::Q:
                    _info->currentInputing += 'q';
                    break;
                case sf::Keyboard::Key::R:
                    _info->currentInputing += 'r';
                    break;
                case sf::Keyboard::Key::S:
                    _info->currentInputing += 's';
                    break;
                case sf::Keyboard::Key::T:
                    _info->currentInputing += 't';
                    break;
                case sf::Keyboard::Key::U:
                    _info->currentInputing += 'u';
                    break;
                case sf::Keyboard::Key::V:
                    _info->currentInputing += 'v';
                    break;
                case sf::Keyboard::Key::W:
                    _info->currentInputing += 'w';
                    break;
                case sf::Keyboard::Key::X:
                    _info->currentInputing += 'x';
                    break;
                case sf::Keyboard::Key::Y:
                    _info->currentInputing += 'y';
                    break;
                case sf::Keyboard::Key::Z:
                    _info->currentInputing += 'z';
                    break;
                case sf::Keyboard::Key::Num0:
                    _info->currentInputing += '0';
                    break;
                case sf::Keyboard::Key::Num1:
                    _info->currentInputing += '1';
                    break;
                case sf::Keyboard::Key::Num2:
                    _info->currentInputing += '2';
                    break;
                case sf::Keyboard::Key::Num3:
                    _info->currentInputing += '3';
                    break;
                case sf::Keyboard::Key::Num4:
                    _info->currentInputing += '4';
                    break;
                case sf::Keyboard::Key::Num5:
                    _info->currentInputing += '5';
                    break;
                case sf::Keyboard::Key::Num6:
                    _info->currentInputing += '6';
                    break;
                case sf::Keyboard::Key::Num7:
                    _info->currentInputing += '7';
                    break;
                case sf::Keyboard::Key::Num8:
                    _info->currentInputing += '8';
                    break;
                case sf::Keyboard::Key::Num9:
                    _info->currentInputing += '9';
                    break;
                case sf::Keyboard::Key::Add:
                    _info->currentInputing += '+';
                    break;
                case sf::Keyboard::Key::Subtract:
                    _info->currentInputing += '-';
                    break;
                case sf::Keyboard::Key::Multiply:
                    _info->currentInputing += '*';
                    break;
                case sf::Keyboard::Key::Divide:
                    _info->currentInputing += '/';
                    break;
                case sf::Keyboard::Key::Space:
                    _info->currentInputing += ' ';
                    break;
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
