#pragma once

#include "Outpost2DLL\Outpost2DLL.h"
#include "ScenarioHelperLibrary\UnitHelper.h"
#include <array>

using namespace UnitHelper;

void BuildStartingConvoy(VehicleBuilder& vehicleBuilder)
{
	//LOCATION startLoc(1 + X_, 98 + Y_);
	LOCATION startLoc(20 + X_, 50 + Y_);

	vehicleBuilder.SetPlayer(Player0);
	vehicleBuilder.SetVehicleDirection(UnitDirection::East);

	std::vector<VehicleData> vehicleData{
		VehicleData(map_id::mapLynx, map_id::mapMicrowave),
		VehicleData(map_id::mapLynx, map_id::mapStickyfoam),
		VehicleData(map_id::mapLynx, map_id::mapRPG),
		VehicleData(map_id::mapLynx, map_id::mapEMP),
		VehicleData(map_id::mapLynx, map_id::mapESG),
		VehicleData(map_id::mapConVec, map_id::mapCommandCenter),
		VehicleData(map_id::mapConVec, map_id::mapStructureFactory),
		VehicleData(map_id::mapConVec, map_id::mapCommonOreSmelter),
		VehicleData(map_id::mapConVec, map_id::mapTokamak),
		VehicleData(map_id::mapConVec, map_id::mapAgridome),
		VehicleData(map_id::mapConVec, map_id::mapRareStorage),
		VehicleData(map_id::mapRoboDozer),
		VehicleData(map_id::mapRoboMiner),
		VehicleData(map_id::mapRoboMiner),
		VehicleData(map_id::mapEarthworker),
		VehicleData(map_id::mapRoboSurveyor),
		VehicleData(map_id::mapRoboSurveyor),
		VehicleData(map_id::mapEvacuationTransport),
		VehicleData(map_id::mapEvacuationTransport),
		VehicleData(map_id::mapEvacuationTransport),
		VehicleData(map_id::mapEvacuationTransport),
		VehicleData(Truck_Cargo::truckCommonMetal, 1000),
		VehicleData(Truck_Cargo::truckCommonMetal, 1000),
		VehicleData(Truck_Cargo::truckCommonMetal, 1000),
		VehicleData(Truck_Cargo::truckCommonMetal, 1000),
		VehicleData(Truck_Cargo::truckRareMetal, 1000),
		VehicleData(Truck_Cargo::truckRareMetal, 1000),
		VehicleData(Truck_Cargo::truckFood, 1000),
		VehicleData(Truck_Cargo::truckFood, 1000),
		VehicleData(Truck_Cargo::truckFood, 1000),
		VehicleData(map_id::mapLynx, map_id::mapMicrowave),
		VehicleData(map_id::mapLynx, map_id::mapStickyfoam),
		VehicleData(map_id::mapLynx, map_id::mapRPG),
		VehicleData(map_id::mapLynx, map_id::mapEMP),
		VehicleData(map_id::mapLynx, map_id::mapESG),
		VehicleData(map_id::mapPanther, map_id::mapMicrowave),
		VehicleData(map_id::mapPanther, map_id::mapRPG),
		VehicleData(map_id::mapPanther, map_id::mapStickyfoam),
		VehicleData(map_id::mapPanther, map_id::mapEMP),
		VehicleData(map_id::mapPanther, map_id::mapESG)
	};

	std::vector<Unit> units;
	
	vehicleBuilder.CreateGridOfVehicles(units, startLoc, 5, 2, 2, vehicleData);

	MoveRelativeAmount(units, LOCATION(3, 0));
}

void BuildReturnRescueConvoy(VehicleBuilder& vehicleBuilder)
{
	vehicleBuilder.SetPlayer(Player1);
	vehicleBuilder.SetVehicleDirection(UnitDirection::North);

	//Evac Transport x3

	std::vector<VehicleData> vehicleData{
		VehicleData(map_id::mapScout),
		VehicleData(map_id::mapSpider),
		VehicleData(map_id::mapSpider),
		VehicleData(map_id::mapLynx, map_id::mapMicrowave),
		VehicleData(map_id::mapLynx, map_id::mapMicrowave),
		VehicleData(map_id::mapLynx, map_id::mapStickyfoam),
		VehicleData(map_id::mapLynx, map_id::mapStickyfoam),
		VehicleData(map_id::mapLynx, map_id::mapRPG),
		VehicleData(map_id::mapLynx, map_id::mapRPG),
		VehicleData(map_id::mapLynx, map_id::mapEMP),
		VehicleData(map_id::mapLynx, map_id::mapEMP),
		VehicleData(map_id::mapLynx, map_id::mapESG),
		VehicleData(map_id::mapLynx, map_id::mapESG),
		VehicleData(Truck_Cargo::truckCommonMetal, 1000),
		VehicleData(Truck_Cargo::truckCommonMetal, 1000),
		VehicleData(Truck_Cargo::truckCommonMetal, 1000),
		VehicleData(Truck_Cargo::truckRareMetal, 1000),
		VehicleData(Truck_Cargo::truckFood, 1000),
		VehicleData(Truck_Cargo::truckFood, 1000),
		VehicleData(Truck_Cargo::truckFood, 1000),
		VehicleData(map_id::mapRoboDozer),
		VehicleData(map_id::mapEarthworker),
		VehicleData(map_id::mapEarthworker),
		VehicleData(map_id::mapRoboMiner),
		VehicleData(map_id::mapRoboMiner),
		VehicleData(map_id::mapRoboMiner),
		VehicleData(map_id::mapRoboSurveyor),
		VehicleData(map_id::mapRoboSurveyor),
		VehicleData(map_id::mapConVec, map_id::mapCommandCenter),
		VehicleData(map_id::mapConVec, map_id::mapStructureFactory),
		VehicleData(map_id::mapConVec, map_id::mapCommonOreSmelter),
		VehicleData(map_id::mapConVec, map_id::mapRareStorage),
		VehicleData(map_id::mapConVec, map_id::mapAgridome),
		VehicleData(map_id::mapConVec, map_id::mapTokamak),
		VehicleData(map_id::mapPanther, map_id::mapMicrowave),
		VehicleData(map_id::mapPanther, map_id::mapStickyfoam),
		VehicleData(map_id::mapPanther, map_id::mapRPG),
		VehicleData(map_id::mapPanther, map_id::mapEMP),
		VehicleData(map_id::mapPanther, map_id::mapESG),
	};

	std::vector<int> vehicleIndices;
	for (size_t i = 0; i < vehicleData.size(); ++i)
		vehicleIndices.push_back(i);

	double basePercentToKeep = 0.8;
	if (Player[Player0].Difficulty() == DiffHard)
		basePercentToKeep -= 0.1;
	else if (Player[Player0].Difficulty() == DiffEasy)
		basePercentToKeep += 0.1;

	int numberOfVehiclesToRemove = (int)(vehicleData.size() * (basePercentToKeep + TethysGame::GetRand(11) / 100));
	vehicleBuilder.RemoveRandomVehicles(vehicleData, numberOfVehiclesToRemove);

	LOCATION startLoc(44 + X_, 120 + Y_);

	std::vector<Unit> units;
	vehicleBuilder.CreateGridOfVehicles(units, startLoc, 5, 2, 2, vehicleData);
	vehicleBuilder.CauseRandomDamage(units, 25, 10, 30);

	MoveRelativeAmount(units, LOCATION(0, -20));

	//vehicleBuilder.CreateLineOfVehicles(units, startLoc, UnitDirection::East, 2, std::vector<map_id>{});
}

const std::vector<VehicleData> scoutConvoyData{
	//VehicleData(map_id::mapScout),
	//VehicleData(map_id::mapScout),
	//VehicleData(map_id::mapScout),
	VehicleData(map_id::mapLynx, map_id::mapRPG),
	VehicleData(map_id::mapLynx, map_id::mapRPG),
	//VehicleData(map_id::mapLynx, map_id::mapRPG),
	//VehicleData(map_id::mapLynx, map_id::mapEMP),
	//VehicleData(map_id::mapLynx, map_id::mapEMP),
	//VehicleData(map_id::mapLynx, map_id::mapEMP),
};

const std::vector<VehicleData> patrolConvoyData{
	//VehicleData(map_id::mapScout),
	//VehicleData(map_id::mapScout),
	//VehicleData(map_id::mapScout),
	VehicleData(map_id::mapLynx, map_id::mapRPG),
	VehicleData(map_id::mapLynx, map_id::mapRPG),
	//VehicleData(map_id::mapLynx, map_id::mapRPG),
	//VehicleData(map_id::mapLynx, map_id::mapEMP),
	//VehicleData(map_id::mapLynx, map_id::mapEMP),
	//VehicleData(map_id::mapLynx, map_id::mapEMP),
};

void BuildReturnScoutConvoy(VehicleBuilder& vehicleBuilder)
{
	LOCATION startLoc(0 + X_, 0 + Y_);

	vehicleBuilder.SetPlayer(Player1);
	vehicleBuilder.SetVehicleDirection(South);

	std::vector<Unit> units;

	vehicleBuilder.CreateGridOfVehicles(units, startLoc, 3, 2, 2, scoutConvoyData);

	MoveRelativeAmount(units, LOCATION(0, 5));
}

map_id GetRandomEdenTurret()
{
	switch (TethysGame::GetRand(5))
	{
	case 0:
		return map_id::mapLaser;
	case 1:
		return map_id::mapRailGun;
	case 2:
		return map_id::mapEMP;
	case 3:
		return map_id::mapAcidCloud;
	default:
		return map_id::mapThorsHammer;
	}
}

void BuildReturnDefenseConvoy(VehicleBuilder& vehicleBuilder)
{
	LOCATION startLoc(0 + X_, 0 + Y_);

	vehicleBuilder.SetPlayer(Player1);
	vehicleBuilder.SetVehicleDirection(North);

	std::vector<VehicleData> vehicleData{
		VehicleData(map_id::mapScout),
		VehicleData(map_id::mapScout),
		VehicleData(map_id::mapSpider),
		VehicleData(map_id::mapSpider),
		VehicleData(map_id::mapSpider),
		VehicleData(Truck_Cargo::truckGarbage, 1),
		VehicleData(Truck_Cargo::truckEmpty, 0),
		VehicleData(Truck_Cargo::truckEmpty, 0),
		VehicleData(map_id::mapLynx, map_id::mapMicrowave),
		VehicleData(map_id::mapLynx, map_id::mapStickyfoam),
		VehicleData(map_id::mapLynx, map_id::mapRPG),
		VehicleData(map_id::mapLynx, map_id::mapEMP),
		VehicleData(map_id::mapLynx, map_id::mapESG),
		VehicleData(map_id::mapPanther, map_id::mapMicrowave),
		VehicleData(map_id::mapPanther, map_id::mapStickyfoam),
		VehicleData(map_id::mapPanther, map_id::mapRPG),
		VehicleData(map_id::mapPanther, map_id::mapEMP),
		VehicleData(map_id::mapPanther, map_id::mapESG),
		VehicleData(map_id::mapTiger,  GetRandomEdenTurret())
	};

	std::vector<Unit> units;

	vehicleBuilder.CreateGridOfVehicles(units, startLoc, 3, 2, 2, vehicleData);

	MoveRelativeAmount(units, LOCATION(0, 10));
}