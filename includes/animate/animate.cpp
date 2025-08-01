#include "animate.h"
#include <cmath>
animate::animate(): _windows(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE_NAME), _info(new graphInfo()), _sys(_info)
{}


void animate::startAnimate()
{    
    bool debug = false;
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
                if(ignoreNextChar){
                    ignoreNextChar = false;
                    break;
                }
                //get the unicode of the input and ignore non-printable characters
                if(_info->isInputingFunction){
                    unicode = event.text.unicode;
                    if(unicode < 128 && unicode > 31)
                    {
                        if(debug){
                            cout << "get a input: " << static_cast<char>(unicode) << endl;
                        }
                        // _info->currentInputing += static_cast<char>(unicode);
                        _info->addInput(static_cast<char>(unicode));
                    }
                }
                break;
                // key pressed
            case sf::Event::KeyPressed:
                if(debug){
                    cout << "key pressed" << endl;
                }

                if(_info->isInputingFunction){
                    //inputing functions
                    switch (event.key.code)
                    {
                    // case sf::Keyboard::Key::Delete:
                    //     lastIndex = _info->currentInputing.size() - 1;
                    //     if(lastIndex > -1){
                    //         _info->currentInputing.erase(lastIndex);
                    //     }
                    //     break;
                    case sf::Keyboard::Key::Enter:
                        _info->pushMyInput();
                        _info->isInputingFunction = false;
                        break;
                    case sf::Keyboard::Key::Left:
                        _info->inputIndexMove(-1);  //insert key more left
                        break;
                    case sf::Keyboard::Key::Right:
                        _info->inputIndexMove(1);  //insert ket more right
                        break;
                    default:
                        break;
                    }
                }
                else{
                    //do operations by sending command
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Key::Up:
                    case sf::Keyboard::Key::W:  //up
                        _sys.callCommand(401);
                        break;
                    case sf::Keyboard::Key::Left:
                    case sf::Keyboard::Key::A:  //left
                        _sys.callCommand(402);
                        break;
                    case sf::Keyboard::Key::Down:
                    case sf::Keyboard::Key::S:  //down
                        _sys.callCommand(403);
                        break;
                    case sf::Keyboard::Key::Right:
                    case sf::Keyboard::Key::D:  //right
                        _sys.callCommand(404);
                        break;
                    case sf::Keyboard::Key::Z:  //zoom in
                        _sys.callCommand(500);
                        break;
                    case sf::Keyboard::Key::X:  //zoom out
                        _sys.callCommand(501);
                        break;
                    case sf::Keyboard::Key::R:  //reset
                        _sys.callCommand(999);
                        break;
                    case sf::Keyboard::Key::F:  //start input functions
                        _sys.callCommand(100);
                        ignoreNextChar = true;
                        break;
                    case sf::Keyboard::Key::Enter:
                        break;
                    
                    default:
                        break;
                    }

                    if(event.key.code == sf::Keyboard::Enter){
                        if(event.key.shift){
                            _sys.callCommand(501);  //zoom out
                        }
                        else{
                            _sys.callCommand(500);  //zoom in
                        }
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if(debug){
                    cout << "get event: mouse clicked" << endl;
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    _sys.mouseOnCliked(event.mouseButton.x, event.mouseButton.y);
                }
                break;
            default:
                break;
            }
        }

        _info->buttonBounds.clear();
        //do update();
        _sys.update(_windows);
    }
}


animate::~animate(){
    delete _info;
}
