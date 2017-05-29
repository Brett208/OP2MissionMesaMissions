#pragma once

#include "OP2Helper\OP2Helper.h"
#include "HFL\Source\HFL.h"
#include "Outpost2DLL\Outpost2DLL.h"

#include <vector>
#include <functional>

namespace UnitHelper
{
	struct VehicleData
	{
		VehicleData()
		{
			Clear();
		}

		VehicleData(map_id vehicle, map_id cargo)
		{
			Clear();
			Vehicle = vehicle;
			Cargo = cargo;
		};

		VehicleData(Truck_Cargo truckCargo, int truckCargoAmount)
		{
			if (truckCargoAmount < 0)
				truckCargoAmount = 0;

			Clear();
			Vehicle = map_id::mapCargoTruck;
			TruckCargo = truckCargo;
			TruckCargoAmount = truckCargoAmount;
		}

		VehicleData(map_id vehicle)
		{
			Clear();
			Vehicle = vehicle;
		}

		map_id Vehicle;
		map_id Cargo;
		Truck_Cargo TruckCargo;
		int TruckCargoAmount;

		void Clear()
		{
			Vehicle = map_id::mapNone;
			Cargo = map_id::mapNone;
			TruckCargo = Truck_Cargo::truckEmpty;
			TruckCargoAmount = 0;
		}
	};

	class VehicleBuilder
	{
	public:
		int GetPlayer();
		void SetPlayer(int player);
		
		int GetLightsOn()
		{
			return lightsOn;
		}

		void SetLightsOn(bool lightsOn)
		{
			this->lightsOn = lightsOn;
		}

		void SetVehicleDirection(UnitDirection unitDirection);
		UnitDirection GetVehicleDirection();

		void SetupMiningGroup(MiningGroup &miningGroup, const Unit &vehicleFactory, Unit &mine, Unit &smelter, MAP_RECT &oreIdleRect, int numbOfTrucks);
		void PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units);
		void PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units, map_id target);
		void CreateVechLightsOn(Unit &unit, map_id vehicleType, LOCATION location, map_id cargo);
		void VehicleBuilder::CreateVechLightsOn(Unit &unit, VehicleData vehicleData, LOCATION location);

		void VehicleBuilder::CreateGridOfVehicles(std::vector<Unit> &units, LOCATION topLeftLoc, int vehiclesPerRow, int horzSpacing, int vertSpacing, std::vector<VehicleData> vehicleData);
		
		void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
			int vehicleSpacing, const map_id vehicleType, const map_id cargo, int vehicleCount);
		void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
			int vehicleSpacing, map_id vehicleType, const std::vector<map_id> &cargoVector);
		void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
			int vehicleSpacing, const std::vector<map_id> &vehicleTypes);

		void VehicleBuilder::CreateLineOfTrucksWithCargo(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
			int vehicleSpacing, const std::vector<Truck_Cargo> &cargoTypes);

		void VehicleBuilder::CauseRandomDamage(PlayerVehicleEnum &playerVehicEnum, double percentChanceDamaged,
			double percentMinDamage, double percentMaxDamage);
		void VehicleBuilder::CauseRandomDamage(std::vector<Unit> &units, int percentChanceDamaged, int minDamage, int maxDamage);

		void VehicleBuilder::CreateVehiclesInRect(std::vector<Unit> &units, MAP_RECT mapRect, map_id vehicleType,
			const std::vector<map_id> &cargoTypes);

		void VehicleBuilder::SetPercentDamaged(UnitEx &unitEx, double percentDamaged);

		void VehicleBuilder::CreateVehicleInRect(Unit &unit, const MAP_RECT &mapRect, map_id vehicleType, map_id cargoType);

		void VehicleBuilder::CreateTrucksInRect(std::vector<Unit> &trucks, MAP_RECT mapRect,
			Truck_Cargo cargoType, const std::vector<int> &amount);

		void VehicleBuilder::CreateVehicleInGarage(Unit &garage, int bayIndex, map_id vehicleType, map_id cargo);

		//Add cargoAmount of none to add an empty truck.
		void VehicleBuilder::CreateVehicleInGarage(Unit &garage, int bayIndex, Truck_Cargo truckCargo, int cargoAmount);
		void VehicleBuilder::RemoveRandomVehicles(std::vector<VehicleData>& vehicleData, int numberToRemove);

	private:
		int playerNumber = Player0;
		bool lightsOn = true;
		UnitDirection unitDirection = UnitDirection::North;

		std::function<LOCATION(LOCATION, int)> VehicleBuilder::getLineDirectionIterator(UnitDirection lineDirection);
	};

	void Move(std::vector<Unit> &units, const LOCATION& location);
	void MoveRelativeAmount(Unit& unit, const LOCATION& relativeMoveAmount);
	void MoveRelativeAmount(std::vector<Unit>& units, const LOCATION& relativeMoveAmount);

	void PoofOrMoveUnit(UnitEx& unit, UnitDirection directionToEdge, int mapWidth, int mapHeight);
	//Returns if true if all units have poofed.
	bool PoofUnitsOnMapEdge(const MAP_RECT& mapRect, PlayerNum playerNum, UnitDirection directionToEdge, int mapWidth, int mapHeight);

	//Gets a separate copy of std::vector<VehicleData> vehicleData because it will remove entries from vehicleData.
	void PullVehiclesFromRect(std::vector<Unit>& unitsOut, PlayerNum playerNum, const MAP_RECT& mapRect, std::vector<VehicleData> vehicleData);

	bool BuildingConstructed(int playerNumber, map_id buildingType);
	bool KitInConVec(int player, map_id structureKitType);
	bool KitInStructFactory(int playerNumber, map_id structureKitType);
	bool BuildingOrKitAvailable(int playerNumber, map_id buildingType);
	bool IsCombatUnit(map_id unitType);
	void FindBuildings(std::vector<Unit> &buildings, int playerNumber, const std::vector<map_id> &buildingTypes);
	bool GetFirstBuildingOfType(Unit &building, int playerNumber, map_id buildingType);
	void FindBuildingLocations(std::vector<LOCATION> &locations, int playerNumber, const std::vector<map_id> &buildingTypes);
	int FindSouthernYCoordOfCombatant(int playerNumber);

	//Counts all buildings of a certain type owned by a specific player. This includes buildings still under construction.
	int CountBuildings(int playerNumber, map_id buildingType);

	//Counts all buildings owned by a player. This includes buildings still under construction.
	int CountAllBuildings(int playerNumber);

	//Iterates through all vehicles of a given player and returns true if any of their vehicles are inside of the provided rectangle.
	bool VehicleInRectangle(MAP_RECT mapRect, int playerNumber);

	UnitDirection GetRandomUnitDirection();

	map_id GetRandomTankType(bool includeTigers = true);
	map_id ChooseRepairVehicleType(bool isEden);
}