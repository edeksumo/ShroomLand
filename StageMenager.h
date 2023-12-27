#pragma once
#include "Stage.h"
class StageMenager
{
private:
	void LoadStagesFromFile();
	DataMenager* p_dM;
	ObjectMenager* p_oM;
protected:

public:
	std::multimap<std::string, Stage> StageContainer;			//stores all stages in the game
	std::multimap<std::string, Stage> ActiveStageContainer;			//Keeps stages that are used in gameState
	std::vector<std::string> StageNames;						//stores all stage names
	void restoreStages();
	StageMenager() {
		p_dM = nullptr;
		p_oM = nullptr;
	}
	StageMenager(DataMenager* m_dM, ObjectMenager* m_oM) {
		p_dM = m_dM;
		p_oM = m_oM;
		LoadStagesFromFile();
		restoreStages();
	}
};

