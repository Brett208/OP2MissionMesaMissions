#include "ScriptGlobal.h"
#include "ConvoyBuilder.h"
#include "ScenarioHelperLibrary\DisasterHelper.h"
#include "ScenarioHelperLibrary\UnitHelper.h"
#include "ScenarioHelperLibrary\VehicleCounter.h"
#include "HFL\Source\HFL.h"
#include "OP2Helper/OP2Helper.h"
#include "Outpost2DLL/Outpost2DLL.h"
#include "EnemyConvoyBuilder.h"

using namespace UnitHelper;

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetails("Campaign - Ply, Pursued, Ep 4, Mesa Missions", "Mesa.map", "MULTITEK.TXT", MissionTypes::Colony, 3)

DisasterHelper disasterHelper;
UnitHelper::VehicleBuilder vehicleBuilder;
UnitHelper::VehicleCounter vehicleCounter;

extern void ShowBriefing();

const MAP_RECT topLeftRallyRect(0 + X_, 0 + Y_, 31 + X_, 12 + Y_);
const MAP_RECT bottomRallyRect(39 + X_, 117 + Y_, 65 + X_, 128 + Y_);
const int mapWidth = 128;

ScriptGlobal scriptGlobal;
ExportSaveLoadData(scriptGlobal);

// List of songs to play
SongIds PlayList[] = {
	SongIds::songEP62,
	SongIds::songEP63
};

Export int InitProc()
{
	HFLInit();

	ShowBriefing();

	//GameMap::SetCellType(LOCATION(10 + X_, 128 + Y_), CellTypes::cellFastPassible1);

	Player[Player0].GoPlymouth();
	Player[Player0].SetColorNumber(PlayerColor::PlayerRed);
	Player[Player0].GoHuman();

	Player[Player1].GoPlymouth();
	Player[Player1].SetColorNumber(PlayerColor::PlayerGreen);
	Player[Player1].GoAI();
	ExtPlayer[Player1].SetPlayerName("CPT Jones");

	Player[Player2].GoEden();
	Player[Player2].SetColorNumber(PlayerColor::PlayerBlue);
	Player[Player2].GoAI();

	Player[Player0].AllyWith(Player1);
	Player[Player1].AllyWith(Player0);

	TethysGame::SetDaylightMoves(true);
	TethysGame::SetDaylightEverywhere(false);
	GameMap::SetInitialLightLevel(mapWidth);
	

	Player[0].CenterViewOn(10 + X_, 10 + Y_);

	TethysGame::SetMusicPlayList(2, 0, PlayList);

	scriptGlobal.DisasterTimeTrig = CreateTimeTrigger(true, false, 1500, 3500, "CreateDisaster"); //Set time in ticks (marks / 100)

	Unit marker;
	TethysGame::PlaceMarker(marker, 12 + X_, 6 + Y_, MarkerTypes::Circle); // Evac Point
	TethysGame::PlaceMarker(marker, 50 + X_, 120 + Y_, MarkerTypes::Circle); // Convoy Return Point

	//BuildReturnRescueConvoy(vehicleBuilder);
	BuildStartingConvoy(vehicleBuilder);

	scriptGlobal.ScoutConvoyReturnTrig = CreateTimeTrigger(false, true, 1000 + TethysGame::GetRand(100), "ReturnScoutGroup");
	scriptGlobal.ScoutConvoyTransferToPlayerTrig = CreateTimeTrigger(false, true, 400, "TransferScoutGroupBack");

	scriptGlobal.EnemyPatrolTimeTrig = CreateTimeTrigger(true, false, 1000 + TethysGame::GetRand(100), "CreateEnemyPatrol");

	std::vector<LOCATION> mineLocs{
		LOCATION(70 + X_, 76 + Y_),
		LOCATION(77 + X_, 78 + Y_),
		LOCATION(75 + X_, 71 + Y_),
		LOCATION(79 + X_, 75 + Y_),
		LOCATION(80 + X_, 69 + Y_),
		LOCATION(79 + X_, 62 + Y_),
		LOCATION(85 + X_, 65 + Y_),
	};

	for (int i = 0; i < 3; ++i)
	{
		int locIndex = TethysGame::GetRand(mineLocs.size());

		TethysGame::CreateBeacon(map_id::mapMiningBeacon, mineLocs[locIndex].x, mineLocs[locIndex].y, BeaconTypes::OreTypeCommon, Yield::Bar1, Variant::VariantRandom);
		
		mineLocs.erase(mineLocs.begin() + locIndex);
	}

	TethysGame::CreateBeacon(map_id::mapMiningBeacon, 71 + X_, 29 + Y_, BeaconTypes::OreTypeRare, Yield::Bar2, Variant::Variant2);

	return true;
}

void CheckScoutConvoy()
{
	std::vector<Unit> units;
	PullVehiclesFromRect(units, Player0, topLeftRallyRect, scoutConvoyData);

	if (units.size() == scoutConvoyData.size())
	{
		ExtPlayer[Player1].SetPlayerName("CPT Jones");
		scriptGlobal.ScoutGroupTransferred = true;

		for (size_t i = 0; i < units.size(); ++i)
		{
			units[i].DoTransfer(Player1);
		}

		MoveRelativeAmount(units, LOCATION(0, -10));
	}
}

void CheckPatrolConvoy()
{
	std::vector<Unit> units;
	PullVehiclesFromRect(units, Player0, bottomRallyRect, patrolConvoyData);

	if (units.size() == patrolConvoyData.size())
	{
		ExtPlayer[Player1].SetPlayerName("MAJ Tanaka");
		scriptGlobal.ScoutGroupTransferred = true;

		for (size_t i = 0; i < units.size(); ++i)
		{
			units[i].DoTransfer(Player1);
		}

		MoveRelativeAmount(units, LOCATION(0, -10));
	}
}

void HandleScoutGroupLogic()
{
	if (!scriptGlobal.ScoutGroupTransferred)
	{
		CheckScoutConvoy();
	}
	else if (!scriptGlobal.ScoutGroupPoofed)
	{
		MAP_RECT explodedRect(topLeftRallyRect);
		explodedRect.Offset(-10, -10);
		explodedRect.Inflate(10, 10);

		scriptGlobal.ScoutGroupPoofed =
			PoofUnitsOnMapEdge(explodedRect, Player1, UnitDirection::North, mapWidth, mapWidth);

		if (scriptGlobal.ScoutGroupPoofed)
		{
			scriptGlobal.ScoutConvoyReturnTrig.Enable();
			//TODO: Enable time trigger.
		}
	}
	else if (scriptGlobal.ScoutGroupReturned)
	{

	}
}

void HandlePatrolGroupLogic()
{
	if (!scriptGlobal.PatrolGroupTransferred)
	{
		CheckPatrolConvoy();
	}
	else
	{
		scriptGlobal.PatrolGroupPoofed = PoofUnitsOnMapEdge(topLeftRallyRect, Player1, UnitDirection::North, mapWidth, mapWidth);

	}
}

Export void AIProc()
{
	HandleScoutGroupLogic();
	
	HandlePatrolGroupLogic();

	//vehicleCounter.Clear();
	//vehicleCounter.PullVehiclesFromRectangle(Player0, MAP_RECT(0 + X_, 0 + Y_, 0 + X_, 0 + Y_));

	//if (vehicleCounter.GetVehicleCount(map_id::mapScout) >= 3 &&
	//	vehicleCounter.GetVehicleCount(map_id::mapLynx, map_id::mapRPG) >= 3 &&
	//	vehicleCounter.GetVehicleCount(map_id::mapLynx, map_id::mapEMP) >= 3)
	//{
		//TODO: 1. Transfer all vehicles to Player2.
	//}

	//if (TethysGame::Tick() > 3000)
	//{
	//	PlayerUnitEnum playerUnitEnum(Player1);
	//	
	//	UnitEx unit;
	//	while (playerUnitEnum.GetNext(unit))
	//	{
	//		unit.DoPoof();
	//	}
	//}
}


Export void CreateDisaster()
{
	if (!disasterHelper.MapPropertiesSet())
	{
		disasterHelper.SetMapProperties(mapWidth, mapWidth, false); //MapWidth, MapHeight, Does map wrap East/West
	}

	disasterHelper.CreateRandomDisaster();
}

Export void ReturnScoutGroup()
{
	BuildReturnScoutConvoy(vehicleBuilder);

	scriptGlobal.ScoutConvoyReturnTrig.Destroy();
	scriptGlobal.ScoutConvoyTransferToPlayerTrig.Enable();
}

Export void TransferScoutGroupBack()
{



	scriptGlobal.ScoutConvoyTransferToPlayerTrig.Destroy();
}

Export void CreateEnemyPatrol()
{
	BuildInitialEnemyPatrol(vehicleBuilder, scriptGlobal.FirstEnemyPatrol);
}

Export void NoResponseToTrigger() {}