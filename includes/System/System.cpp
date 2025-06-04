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
    x_axis.setPosition(sf::Vector2f(0, ORIGIN_REFEREN_Y));

    window.draw(x_axis);

    sf::RectangleShape y_axis(sf::Vector2f(1, PLAYGROUND_HEIGHT));
    y_axis.setFillColor(sf::Color::White);
    y_axis.setPosition(sf::Vector2f(ORIGIN_REFEREN_X, 0));

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
    sf::RectangleShape button_UI(sf::Vector2f(25, 25));
    button_UI.setFillColor(sf::Color(220, 220, 220));

    button_UI.setPosition(sf::Vector2f(PLAYGROUND_WIDTH + 15, 15));
    for(int i = 0; i < 2; i++){
        window.draw(button_UI);

        button_UI.move(sf::Vector2f(40, 0));
        window.draw(button_UI);
        button_UI.move(sf::Vector2f(40, 0));
        window.draw(button_UI);
        button_UI.move(sf::Vector2f(40, 0));
        window.draw(button_UI);
        button_UI.move(sf::Vector2f(40, 0));
        window.draw(button_UI);
        button_UI.move(sf::Vector2f(40, 0));
        window.draw(button_UI);
        button_UI.move(sf::Vector2f(40, 0));
        window.draw(button_UI);

        button_UI.setPosition(sf::Vector2f(PLAYGROUND_WIDTH + 15, 55));
    }

    //draw input functions area
    sf::Vector2f size = sf::Vector2f(SCREEN_WIDTH - PLAYGROUND_WIDTH - 25, 40);
    sf::Vector2f position = sf::Vector2f(PLAYGROUND_WIDTH + 15, 120);
    vector<string> historyInput = _info->equationHistory;

    drawFunctionDisplay(window, _info->currentInputing, size, position, 20);

    //latest input display first, only display 10 inputs for a page
    position.y = SCREEN_HEIGHT * 0.3;
    int counter = 0;
    for(int i = 0; i < historyInput.size(); i++){
        drawFunctionDisplay(window, historyInput[historyInput.size() - i - 1], size, position, 20);
        position.y += 50;

        
        counter++;
        if(counter >= 10){
            break;
        }
    }
}



void System::drawFunctionDisplay(sf::RenderWindow& window, string f, sf::Vector2f size, sf::Vector2f position, int chSize)
{
    //draw input functions area
    sf::RectangleShape fun_background(size);
    fun_background.setFillColor(sf::Color::White);
    fun_background.setPosition(position);

    sf::Text function;
    function.setFont(_info->_font);
    function.setString(f);
    function.setFillColor(sf::Color::Black);
    function.setPosition(position.x + chSize / 2, position.y + chSize / 3);
    function.setCharacterSize(chSize);


    window.draw(fun_background);
    window.draw(function);
}