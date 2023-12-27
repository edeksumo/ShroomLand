#include "StageMenager.h"
/****************************************************/
//Private
/****************************************************/
void StageMenager::LoadStagesFromFile()
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
    StageContainer.clear();
    std::ifstream file(p_dM->SaveFormat.SaveFileName);
    std::vector<std::string> v;
    std::string s;
    std::multimap<std::string, Stage>::iterator it;
    while (file >> s) {
        v.push_back(s);
    }
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == p_dM->SaveFormat.StageDefiner) {
            auto n = v[i + 1];
            StageContainer.insert(std::pair<std::string, Stage>(n, Stage(p_oM, n, p_dM)));
            StageNames.push_back(n);
            it = StageContainer.find(n);
            std::cout << "== GAME == Stage Created" << std::endl;
            //printf("== GAME == Stage Created\n");
        }
        if (v[i] == p_dM->SaveFormat.ObjectDefiner) {
            if (v[i + 1] == p_dM->SaveFormat.TileDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                auto va = stoi(v[i + 5]);
                it->second.fillDeque(GridCell(x, y), j, va);
                //.... adding tile objects to deque
            }
            if (v[i + 1] == p_dM->SaveFormat.BackTileDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                it->second.addBackgroundTile(GridCell(x, y), j);
                //.... adding tile objects to deque
            }
            if (v[i + 1] == p_dM->SaveFormat.StaticObjectDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                it->second.addObject(sf::Vector2f(x, y), j);
                //.... adding static objects to deque
            }
            if (v[i + 1] == p_dM->SaveFormat.InteractableObjectDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                it->second.addObject(sf::Vector2f(x, y), j);
                //.... adding Interactable objects to deque
            }
            if (v[i + 1] == p_dM->SaveFormat.PlayerObjectDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                it->second.addObject(sf::Vector2f(x, y), j);
                //.... adding player objects to deque
            }

            if (v[i + 1] == p_dM->SaveFormat.SpecialObjectDefiner) {
                auto j = stoi(v[i + 2]);
                auto x = stoi(v[i + 3]);
                auto y = stoi(v[i + 4]);
                auto z = v[i + 5];
                it->second.addObject(sf::Vector2f(x, y), j, z);
                //.... adding special objects to deque
            }
            ///.... each type of obj must be specified here 
        }
    }
    std::cout << "Total Stages: " << StageContainer.size() << std::endl;
}

/****************************************************/
//Protected
/****************************************************/

/****************************************************/
//Public
/****************************************************/

void StageMenager::restoreStages()
{
    ActiveStageContainer.clear();
    ActiveStageContainer = StageContainer;
    std::cout << "Copy stgs\n";
}