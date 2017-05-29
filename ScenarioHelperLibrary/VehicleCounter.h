#pragma once

#include "OP2Helper\ColonyType.h"
#include "HFL\Source\HFL.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

//Note: Only PlayerBuildingEnum returns buildings, so do not try and use this class to count buildings.
//Requires HFL.
//Can distinguish between truck cargo as well.
namespace UnitHelper
{
	struct VehicleCount
	{
		map_id UnitType;
		map_id UnitCargo;
		int Count;
	}; 

	struct TruckCount
	{
		Truck_Cargo TruckCargo;
		int Count;
	};

	class VehicleCounter
	{
	public:
		int GetVehicleCount()
		{
			return vehicleCount;
		}

		bool AllConVecsHaveKits()
		{
			return allConVecsHaveKits;
		}

		bool AllTrucksHaveCargo()
		{
			return allTrucksHaveCargo;
		}

		int GetVehicleCount(map_id vehicleType);
		int GetVehicleCount(map_id vehicleType, map_id cargoType);
		int GetTruckCargoCount(Truck_Cargo truckCargo);

		int CombatVehicleCount()
		{
			return combatVehicleCount;
		}

		//NOTE: Any vehicle without a weapon is considered a non-combatant. This includes spiders & scouts.
		int NonCombatVehicleCount()
		{
			return nonCombatVehicleCount;
		}
			
		void PullVehiclesFromRectangle(PlayerNum playerNum, const MAP_RECT& mapRect);
		void PullVehiclesFromPlayer(PlayerNum playerNum);
		void Clear();

	private:
		int vehicleCount = 0;
		int nonCombatVehicleCount = 0;
		int combatVehicleCount = 0;
		bool allConVecsHaveKits;
		bool allTrucksHaveCargo;

		std::vector<VehicleCount> VehicleCountVector;
		std::vector<TruckCount> truckCargoCountVector;

		void GetVehicleIndices(std::vector<int>& VehicleIndices, map_id vehicleType);
		int GetVehicleIndex(map_id vehicleType, map_id cargoType);
		int GetTruckCargoIndex(Truck_Cargo truckCargo);

		void SortVehicle(map_id vehicleType, map_id cargoType, Truck_Cargo truckCargo);
		void AddVehicleToVector(map_id vehicleType, map_id cargoType);
		void AddTruckCargoToVector(Truck_Cargo truckCargo);
	};
}