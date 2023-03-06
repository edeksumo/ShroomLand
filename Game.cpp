#include "Game.h"
/****************************************************/
//Private
/****************************************************/
void Game::Begin() {
    States.push(MainMenu);
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

void Game::LoadStages()
{
    /*
       save format:
       STAGE name_of_stage
       OBJ OBJ_CLASS_NAME   obj_id  obj_grid_posX   obj_grid posY

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
            StageContainer.insert(std::pair<std::string, Stage>(n, Stage(objMenager)));
            it = StageContainer.find(n);
            std::cout << "== GAME == Stage Created" << std::endl;
        }
        if (v[i] == dataMenager.SaveFormat.ObjectDefiner) {
            if (v[i + 1] == dataMenager.SaveFormat.TileDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                it->second.addTile(Grid(x, y), j);
                //.... adding tile objects to deque
            }
            if (v[i + 1] == dataMenager.SaveFormat.BackTileDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                auto z = stoi(v[i + 5]);
                it->second.addBackgroundTile(Grid(x, y), j, z);
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
        worldPos = Window->mapPixelToCoords(mousePosition);
       
        States.top()->UpdateWindows(&mousePosition);
        States.top()->Update(&mousePosition, &worldPos);
        
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
