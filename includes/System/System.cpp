#include "System.h"

System::System():_g(),_info(nullptr)
{}

System::System(graphInfo *info): _info(info), _g(info)
{}


void System::update(sf::RenderWindow& window)
{
    window.clear();
    drawBackground(window);
    drawGraph(window);
    drawDisplayUI(window);
    window.display();
    _info->hasChanged = false;
}


void System::drawGraph(sf::RenderWindow& window)
{
    _g.update(window);
}

void System::drawBackground(sf::RenderWindow& window)
{
    //draw xy axis
    sf::RectangleShape x_axis(sf::Vector2f(PLAYGROUND_WIDTH, 1));
    x_axis.setFillColor(sf::Color::White);
    x_axis.setPosition(sf::Vector2f(0, _info->_origin.y));

    window.draw(x_axis);

    sf::RectangleShape y_axis(sf::Vector2f(1, PLAYGROUND_HEIGHT));
    y_axis.setFillColor(sf::Color::White);
    y_axis.setPosition(sf::Vector2f(_info->_origin.x, 0));

    window.draw(y_axis);

    //draw input area
    sf::RectangleShape back_inputs(sf::Vector2f(SCREEN_WIDTH - PLAYGROUND_WIDTH, SCREEN_HEIGHT));
    back_inputs.setFillColor(sf::Color(43, 43, 59));
    back_inputs.setPosition(sf::Vector2f(PLAYGROUND_WIDTH, 0));
    window.draw(back_inputs);

    //draw the bar to split different UI button
    sf::RectangleShape spliter(sf::Vector2f(SCREEN_WIDTH - PLAYGROUND_WIDTH, 2));
    spliter.setFillColor(sf::Color(255, 87, 34));
    spliter.setPosition(sf::Vector2f(PLAYGROUND_WIDTH, SCREEN_HEIGHT * 0.125));
    window.draw(spliter);
    spliter.setPosition(sf::Vector2f(PLAYGROUND_WIDTH, SCREEN_HEIGHT * 0.275));
    window.draw(spliter);

    //draw a bar split graph and UI
    sf::RectangleShape bar(sf::Vector2f(5, SCREEN_HEIGHT));
    bar.setFillColor(sf::Color(55, 120, 40));
    bar.setPosition(sf::Vector2f(PLAYGROUND_WIDTH, 0));
    window.draw(bar);
}


void System::drawDisplayUI(sf::RenderWindow& window)
{
    string functionRegion = "[";
    functionRegion += floatToSting(_info->_left) + ", ";
    functionRegion += floatToSting(_info->_right) + "] X [";
    functionRegion += floatToSting(- _info->_bottom) + ", ";
    functionRegion += floatToSting(- _info->_top) + "]";

    sf::Text region;
    region.setFont(_info->_font);
    region.setString(functionRegion);
    region.setFillColor(sf::Color::White);
    region.setPosition(PLAYGROUND_WIDTH + 15, 15);
    region.setCharacterSize(15);
    window.draw(region);


    //buttons
    sf::RectangleShape button_UI(sf::Vector2f(25, 25));
    button_UI.setFillColor(sf::Color(220, 220, 220));
    button_UI.setPosition(sf::Vector2f(PLAYGROUND_WIDTH + 15, 55));
    sf::Text butttonMsg;
    sf::Vector2f pos(sf::Vector2f(PLAYGROUND_WIDTH + 19, 60));
    butttonMsg.setFont(_info->_font);
    butttonMsg.setString("W");
    butttonMsg.setFillColor(sf::Color::Black);
    butttonMsg.setPosition(pos);
    butttonMsg.setCharacterSize(15);

    //button for move upward
    window.draw(button_UI);
    window.draw(butttonMsg);
    _info->pushBounds(boundInfo(button_UI.getGlobalBounds(), 401));

    //button for left upward
    button_UI.move(sf::Vector2f(40, 0));
    butttonMsg.move(sf::Vector2f(40, 0));
    butttonMsg.setString("A");
    window.draw(button_UI);
    window.draw(butttonMsg);
    _info->pushBounds(boundInfo(button_UI.getGlobalBounds(), 402));

    //button for down upward
    button_UI.move(sf::Vector2f(40, 0));
    butttonMsg.move(sf::Vector2f(40, 0));
    butttonMsg.setString("S");
    window.draw(button_UI);
    window.draw(butttonMsg);
    _info->pushBounds(boundInfo(button_UI.getGlobalBounds(), 403));

    //button for right upward
    button_UI.move(sf::Vector2f(40, 0));
    butttonMsg.move(sf::Vector2f(40, 0));
    butttonMsg.setString("D");
    window.draw(button_UI);
    window.draw(butttonMsg);
    _info->pushBounds(boundInfo(button_UI.getGlobalBounds(), 404));

    //button for zoom in
    button_UI.move(sf::Vector2f(40, 0));
    butttonMsg.move(sf::Vector2f(40, 0));
    butttonMsg.setString("Z");
    window.draw(button_UI);
    window.draw(butttonMsg);
    _info->pushBounds(boundInfo(button_UI.getGlobalBounds(), 500));

    //button for zoom out
    button_UI.move(sf::Vector2f(40, 0));
    butttonMsg.move(sf::Vector2f(40, 0));
    butttonMsg.setString("X");
    window.draw(button_UI);
    window.draw(butttonMsg);
    _info->pushBounds(boundInfo(button_UI.getGlobalBounds(), 501));

    //button for reset
    button_UI.move(sf::Vector2f(40, 0));
    butttonMsg.move(sf::Vector2f(40, 0));
    butttonMsg.setString("R");
    window.draw(button_UI);
    window.draw(butttonMsg);
    _info->pushBounds(boundInfo(button_UI.getGlobalBounds(), 999));

    //draw input functions area
    sf::Vector2f size = sf::Vector2f(SCREEN_WIDTH - PLAYGROUND_WIDTH - 25, 40);
    sf::Vector2f position = sf::Vector2f(PLAYGROUND_WIDTH + 15, 120);
    vector<string> historyInput = _info->equationHistory;

    bool shouldBeBold = false;
    if(_info->isInputingFunction){
        shouldBeBold = true;
    }

    sf::FloatRect rect = drawFunctionDisplay(window, _info->currentInputing, size, position, 20, shouldBeBold).getGlobalBounds();
    _info->pushBounds(boundInfo(rect, 100));
    
    //if current equation is a nan equation
    if(!_info->isCurrentInputValid){
        //think it as invalid input, output warrning
        sf::Text errerMessage;
        sf::Vector2f pos(sf::Vector2f(PLAYGROUND_WIDTH + 30, 175));
        errerMessage.setFont(_info->_font);
        errerMessage.setString("the equation can't be understand!");
        errerMessage.setFillColor(sf::Color::Red);
        errerMessage.setPosition(pos);
        errerMessage.setCharacterSize(15);
        window.draw(errerMessage);
    }


    //latest input display first, only display 10 inputs for a page
    position.y = SCREEN_HEIGHT * 0.3;
    for(int i = 0; i < historyInput.size() && i < 10; i++){
        //for history looking section, each row will own a deleteBox and selectBox to edit the message
        sf::RectangleShape deleteBox(sf::Vector2f(24, 20));
        sf::RectangleShape selectBox(sf::Vector2f(24, 20));

        deleteBox.setFillColor(sf::Color(220, 220, 220));
        deleteBox.setPosition(position.x + 204, position.y + 10);
        deleteBox.setOutlineThickness(2);
        deleteBox.setOutlineColor(sf::Color(40,40,40));
        selectBox.setFillColor(sf::Color(220, 220, 220));
        selectBox.setPosition(position.x + 235, position.y + 10);
        selectBox.setOutlineThickness(2);
        selectBox.setOutlineColor(sf::Color(40,40,40));

        sf::Text operDelete;
        sf::Text operSelect;
        operDelete.setFont(_info->_font);
        operDelete.setString("De");
        operDelete.setFillColor(sf::Color::Black);
        operDelete.setPosition(position.x + 208, position.y + 12);
        operDelete.setCharacterSize(15);
        operSelect.setFont(_info->_font);
        operSelect.setString(">>");
        operSelect.setFillColor(sf::Color::Black);
        operSelect.setPosition(position.x + 237, position.y + 12);
        operSelect.setCharacterSize(15);


        bool isSelected = false;    //if this display box is being selected
        if(_info->selectedHistoryIndex == 300 + i*10){
            isSelected = true;
        }
        rect = drawFunctionDisplay(window, historyInput[historyInput.size() - i - 1], size, position, 20, isSelected).getGlobalBounds();

        _info->pushBounds(boundInfo(deleteBox.getGlobalBounds(), 301 + i * 10));
        _info->pushBounds(boundInfo(selectBox.getGlobalBounds(), 302 + i * 10));
        _info->pushBounds(boundInfo(rect, 300 + i * 10));

        window.draw(deleteBox);
        window.draw(selectBox);
        window.draw(operDelete);
        window.draw(operSelect);

        position.y += 50;
    }
}


//draw a box with a string
sf::RectangleShape System::drawFunctionDisplay(sf::RenderWindow& window, string f, sf::Vector2f size, sf::Vector2f position, int chSize, bool drawBoarder)
{
    //draw input functions area
    sf::RectangleShape fun_background(size);
    fun_background.setFillColor(sf::Color::White);
    fun_background.setPosition(position);
    if(drawBoarder){
        fun_background.setOutlineThickness(3);
        fun_background.setOutlineColor(sf::Color(255, 87, 34));
    }

    sf::Text function;
    function.setFont(_info->_font);
    function.setString(f);
    function.setFillColor(sf::Color::Black);
    function.setPosition(position.x + chSize / 2, position.y + chSize / 3);
    function.setCharacterSize(chSize);


    window.draw(fun_background);
    window.draw(function);


    return fun_background;
}



void System::mouseOnCliked(float posx, float posy){
    int com = _info->boundedCommand(posx, posy);

    callCommand(com);
}



void System::callCommand(int com){
    if(com == 100){
        _info->isInputingFunction = true;
    }
    else{
        _info->isInputingFunction = false;
    }

    if(com >= 300 && com < 400){
        int comRef = (com - 300)/10;
        if(com % 10 == 0){
            _info->selectedHistoryIndex = com;
            _info->currentEquation = _info->equationHistory.at(_info->getHistoryTureIndex(comRef));
        }
        else if(com % 10 == 1){
            //delete
            _info->equationHistory.erase(_info->equationHistory.end() - comRef - 1);
            _info->selectedHistoryIndex = 0;
        }
        else if(com % 10 == 2){
            //add it to editing
            _info->currentInputing = _info->equationHistory.at(_info->getHistoryTureIndex(comRef));
            _info->selectedHistoryIndex = 0;
            _info->isInputingFunction = true;
        }
    }
    else{
        _info->selectedHistoryIndex = 0;
    }

    if(com == 401){
        _info->moveInterval(1);
    }
    else if(com == 402){
        _info->moveInterval(2);
    }
    else if(com == 403){
        _info->moveInterval(3);
    }
    else if(com == 404){
        _info->moveInterval(4);
    }
    else if(com == 500){
        _info->zoomIn();
    }
    else if(com == 501){
        _info->zoomOut();
    }
    else if(com == 999){
        //reset
        _info->reset();
    }

    _info->hasChanged = true;
}



string floatToSting(float f)
{
    string result = to_string(f);
    size_t decimal = result.find('.');    //deciaml location
    if(decimal != std::string::npos){
        result = result.substr(0, decimal + 1 + 2);
    }

    return result;
}