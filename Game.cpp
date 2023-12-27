#include "Game.h"
/****************************************************/
//Private
/****************************************************/
void Game::Begin() {
    States.push(MainMenu);
    
    Window->setVerticalSyncEnabled(true);
    //Window->setFramerateLimit(60);
}

void Game::Render() {
    Window->clear();
    States.top()->Render(Window);
    States.top()->RenderWindows(Window);
    Window->display();
}

void Game::Keyboard()
{

}

void Game::Update(){
    //sf::Thread thead(&Game::secondThead, this);
    //thead.launch();
    while (Window->isOpen())
     {
        Keyboard::resetWheel();
        while (Window->pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                Window->close();
            if (Event.type == sf::Event::MouseWheelMoved)
                Keyboard::setWheelState(&Event);
        }

        Keyboard::keyAndButtonStateSetter();
        Keyboard();
        
        mousePosition = sf::Mouse::getPosition(*Window);
        worldPos = Window->mapPixelToCoords(mousePosition);
       
        States.top()->UpdateWindows(&mousePosition);
        States.top()->Update(&mousePosition, &worldPos);
        
        Render();
       
        if (States.top()->stateQuit) {
            States.pop();
            if (States.size()) {
                stageMenager->restoreStages();
                States.top()->setStateForStages();
                if (States.top()->StateType == Stage::EState::mainMenuState) {
                    States.top()->setActiveStage("MainMenu");
                }
                Keyboard::resetButtons();
            }
        }
       
        if (States.size() == 0) {
            Window->close();
        }
        else if (States.top()->StateType != stageMenager->StageContainer.begin()->second.GetStateType()) {
            States.top()->setStateForStages();
        }

        //Window->setView(view);
        //fps counter
        //currentTime = clock.getElapsedTime();
        //fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        //std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
        //previousTime = currentTime;
        //std::cout << "== GAME == Update Func" << std::endl;

     }
}
void Game::secondThead()
{
    while (Window->isOpen())
    {

        //States.top()->UpdateWindows(&mousePosition);
        //States.top()->Update(&mousePosition, &worldPos);

        //if (States.top()->stateQuit)
        //    States.pop();

        //if (States.size() == 0)
        //    Window->close();
        //std::cout << "== GAME == Update Func" << std::endl;

    }
}
/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/
