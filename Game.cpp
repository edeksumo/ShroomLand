#include "Game.h"
/****************************************************/
//Private
/****************************************************/
void Game::Begin() {
    States.push(MainMenu);
}

void Game::Render() {
    Window->clear();
    States.top()->RenderWindows(Window);
    States.top()->Render(Window);
    Window->display();
}

void Game::Keyboard()
{

}

void Game::Update(){

     while (Window->isOpen())
     {
        while (Window->pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                Window->close();
        }
        Keyboard::keyAndButtonStateSetter();
        
        Keyboard();
        
        mousePosition = sf::Mouse::getPosition(*Window);
       
        States.top()->UpdateWindows(&mousePosition);
        States.top()->Update(&mousePosition);
        
        Render();
       
        if (States.top()->stateQuit)
            States.pop();
       
        if (States.size() == 0)
            Window->close();
        Window->setView(view);
        //std::cout << "== GAME == Update Func" << std::endl;

     }
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
