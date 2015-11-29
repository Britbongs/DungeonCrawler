#ifndef COMBATHANDLER_H
#define COMBATHANDLER_H
#include <vector> 
#include "..\Entities\Entities.h"

class CombatHandler
{
public:
	CombatHandler();
	~CombatHandler();

private:
	std::vector<Entity> entities_; 

};

#endif