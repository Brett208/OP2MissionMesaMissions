#pragma once

#include "ScenarioHelperLibrary\UnitHelper.h"
#include "ScriptGlobal.h"
#include "OP2Helper/OP2Helper.h"

using namespace UnitHelper;

std::vector<std::pair<LOCATION, UnitDirection>> patrolStartLocs
{
	std::make_pair(LOCATION(63 + X_, 1 + Y_), UnitDirection::East),
	std::make_pair(LOCATION(97 + X_, 1 + Y_), UnitDirection::East),
	std::make_pair(LOCATION(128 + X_, 20 + Y_), UnitDirection::South),
	std::make_pair(LOCATION(126 + X_, 65 + Y_), UnitDirection::South),
	std::make_pair(LOCATION(126 + X_, 101 + Y_), UnitDirection::South),
	std::make_pair(LOCATION(1 + X_, 54 + Y_), UnitDirection::South),
	std::make_pair(LOCATION(1 + X_, 97 + Y_), UnitDirection::South)
};

void BuildFinalEnemyPatrol(FightGroup& fightGroup, VehicleBuilder& vehicleBuilder, LOCATION startLoc)
{
	std::vector<Unit> units;
	vehicleBuilder.CreateLineOfVehicles(units, startLoc, UnitDirection::South, 1, map_id::mapTiger, map_id::mapThorsHammer, 10);
	vehicleBuilder.CreateLineOfVehicles(units, startLoc + LOCATION(1, 0), UnitDirection::South, 1, map_id::mapTiger, map_id::mapEMP, 10);
	vehicleBuilder.CreateLineOfVehicles(units, startLoc + LOCATION(2, 0), UnitDirection::South, 1, map_id::mapTiger, map_id::mapRailGun, 10);

	vehicleBuilder.PopulateFightGroup(fightGroup, units);
	fightGroup.DoAttackEnemy();
}

void BuildFinalEnemyPatrols(VehicleBuilder& vehicleBuilder)
{
	vehicleBuilder.SetPlayer(Player2);
	vehicleBuilder.SetVehicleDirection(UnitDirection::South);

	BuildFinalEnemyPatrol(scriptGlobal.FinalFightGroupW, vehicleBuilder, LOCATION(1 + X_, 94 + Y_));
	BuildFinalEnemyPatrol(scriptGlobal.FinalFightGroupNE, vehicleBuilder, LOCATION(126 + X_, 19 + Y_));
	BuildFinalEnemyPatrol(scriptGlobal.FinalFightGroupSE, vehicleBuilder, LOCATION(126 + X_, 93 + Y_));
}

void OffsetLocation(LOCATION& loc, UnitDirection offsetDirection)
{
	switch (offsetDirection)
	{
	case UnitDirection::East:
		loc = loc + LOCATION(1, 0);
		return;
	case UnitDirection::West:
		loc = loc - LOCATION(1, 0);
		return;
	case UnitDirection::North:
		loc = loc + LOCATION(0, 1);
		return;
	case UnitDirection::South:
		loc = loc - LOCATION(0, -1);
		return;
	case UnitDirection::NorthEast:
		loc = loc + LOCATION(1, 1);
		break;
	case UnitDirection::NorthWest:
		loc = loc + LOCATION(1, -1);
		return;
	case UnitDirection::SouthEast:
		loc = loc + LOCATION(-1, 1);
		return;
	case UnitDirection::SouthWest:
		loc = loc + LOCATION(-1, -1);
		return;
	}
}

void BuildInitialEnemyPatrol(VehicleBuilder& vehicleBuilder, FightGroup& fightGroup)
{
	std::pair<LOCATION, UnitDirection> pair = patrolStartLocs.at(TethysGame::GetRand(patrolStartLocs.size()));

	vehicleBuilder.SetPlayer(Player2);
	vehicleBuilder.SetVehicleDirection(pair.second);

	LOCATION secondLoc = pair.first;
	OffsetLocation(secondLoc, pair.second);

	std::vector<Unit> units;
	vehicleBuilder.CreateLineOfVehicles(units, pair.first, pair.second, 1, map_id::mapScout, map_id::mapNone, 5);

	switch (TethysGame::GetRand(3))
	{
	case 0:
		vehicleBuilder.CreateLineOfVehicles(units, secondLoc, pair.second, 1, map_id::mapLynx, map_id::mapLaser, 7);
		break;
	case 1:
		vehicleBuilder.CreateLineOfVehicles(units, secondLoc, pair.second, 1, map_id::mapLynx, map_id::mapRailGun, 5);
		break;
	case 2:
		vehicleBuilder.CreateLineOfVehicles(units, secondLoc, pair.second, 1, map_id::mapLynx, map_id::mapEMP, 5);
		break;
	}

	vehicleBuilder.PopulateFightGroup(fightGroup, units);
	fightGroup.DoAttackEnemy();
}

void BuildMiddleEnemyPatrol()
{

}

void BuildLateEnemyPatrol()
{

}