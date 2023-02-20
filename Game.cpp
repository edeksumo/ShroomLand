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

void Game::LoadStages()
{
    /*
       save format:
       STAGE name_of_stage
       OBJ obj_class_name   obj_id  obj_grid_posX   obj_grid posY

       example:
       STAGE overworld
       OBJ tile 1 0 0
       OBJ tile 2 1 2
       OBJ tile 4 1 1
    */
    
    std::ifstream file("Stages.txt");
    std::vector<std::string> v;
    std::string s;
    std::multimap<std::string, Stage>::iterator it;
    while (file >> s) {
        v.push_back(s);
    }
    for (int i = 0; i < v.size(); i++) {
        //std::cout << v[i] << std::endl;
        if (v[i] == "STAGE") {
            auto n = v[i + 1];
            StageContainer.insert(std::pair<std::string, Stage>(n, Stage()));
            it = StageContainer.find(n);
            std::cout << "== GAME == Stage Created" << std::endl;
        }
        if (v[i] == "OBJ") {
            if (v[i + 1] == "tile") {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                std::multimap<int, Tile*>::iterator it2 = TilePtrContainer.find(j);
                it->second.addTile(sf::Vector2f(x, y), it2->second);
                //it->second.TileDeque.push_back(*it2->second);
                //.... adding tile objects to deque
            }
            ///.... each type of obj must be specified here 
        }
    }
    std::cout << "Total Stages: " << StageContainer.size() << std::endl;

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
