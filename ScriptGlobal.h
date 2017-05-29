#pragma once

#include "Outpost2DLL\Outpost2DLL.h"

struct ScriptGlobal
{
	bool ScoutGroupTransferred;
	bool ScoutGroupPoofed;
	bool ScoutGroupReturned;
	bool ScoutGroupReTransferred;

	bool PatrolGroupTransferred;
	bool PatrolGroupPoofed;
	bool PatrolGroupReturned;
	bool PatrolGroupReTransferred;

	Trigger DisasterTimeTrig;
	Trigger EnemyPatrolTimeTrig;

	Trigger ScoutConvoyReturnTrig;
	Trigger ScoutConvoyTransferToPlayerTrig;

	FightGroup FirstEnemyPatrol;
	FightGroup FinalFightGroupW;
	FightGroup FinalFightGroupNE;
	FightGroup FinalFightGroupSE;
};

// Global instance of ScriptGlobal
extern ScriptGlobal scriptGlobal;