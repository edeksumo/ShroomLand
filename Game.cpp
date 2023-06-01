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
    if (Keyboard::checkKeyState(sf::Keyboard::Up) == Keyboard::KeyState::hold) {
        view.move(0.f, -2);
    }
    else if (Keyboard::checkKeyState(sf::Keyboard::Down) == Keyboard::KeyState::hold) {
        view.move(0.f, 2);
    }
    if (Keyboard::checkKeyState(sf::Keyboard::Left) == Keyboard::KeyState::hold) {
        view.move(-2, 0.f);
    }
    else if (Keyboard::checkKeyState(sf::Keyboard::Right) == Keyboard::KeyState::hold) {
        view.move(2, 0.f);
    }
}

void Game::LoadStages()
{
    /*
       save format:
       STAGE name_of_stage
       OBJ OBJ_CLASS_NAME   obj_id  obj_grid_posX   obj_grid posY   variant

       example:
       STAGE overworld
       OBJ TILE 1 0 0
       OBJ TILE 2 1 2
       OBJ TILE 4 1 1
    */
    
    std::ifstream file(dataMenager.SaveFormat.SaveFileName);
    std::vector<std::string> v;
    std::string s;
    std::multimap<std::string, Stage>::iterator it;
    while (file >> s) {
        v.push_back(s);
    }
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == dataMenager.SaveFormat.StageDefiner) {
            auto n = v[i + 1];
            StageContainer.insert(std::pair<std::string, Stage>(n, Stage(objMenager, &dataMenager)));
            it = StageContainer.find(n);
            std::cout << "== GAME == Stage Created" << std::endl;
            //printf("== GAME == Stage Created\n");
        }
        if (v[i] == dataMenager.SaveFormat.ObjectDefiner) {
            if (v[i + 1] == dataMenager.SaveFormat.TileDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                auto va = stoi(v[i + 5]);
                it->second.fillDeque(GridCell(x, y), j, va);
                //.... adding tile objects to deque
            }
            if (v[i + 1] == dataMenager.SaveFormat.BackTileDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                it->second.addBackgroundTile(GridCell(x, y), j);
                //.... adding tile objects to deque
            }
            if (v[i + 1] == dataMenager.SaveFormat.StaticObjectDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                it->second.addObject(sf::Vector2f(x, y), j);
                //.... adding static objects to deque
            }
            ///.... each type of obj must be specified here 
        }
    }
    std::cout << "Total Stages: " << StageContainer.size() << std::endl;

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
       
        if (States.top()->stateQuit)
            States.pop();
       
        if (States.size() == 0)
            Window->close();
        Window->setView(view);
        
        
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
