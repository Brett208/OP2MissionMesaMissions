#include "VehicleCounter.h"

namespace UnitHelper
{
	int VehicleCounter::GetVehicleCount(map_id vehicleType)
	{
		std::vector<int> vehicleIndices;
		GetVehicleIndices(vehicleIndices, vehicleType);

		int count = 0;

		for (int index : vehicleIndices)
		{
			count += VehicleCountVector[index].Count;
		}

		return count;
	}

	int VehicleCounter::GetVehicleCount(map_id vehicleType, map_id cargoType)
	{
		int index = GetVehicleIndex(vehicleType, cargoType);

		if (index == -1)
			return 0;

		return VehicleCountVector[index].Count;
	}

	int VehicleCounter::GetTruckCargoCount(Truck_Cargo truckCargo)
	{
		int index = GetTruckCargoIndex(truckCargo);

		if (index == -1)
			return 0;

		return truckCargoCountVector[index].Count;
	}

	void VehicleCounter::PullVehiclesFromPlayer(PlayerNum playerNum)
	{
		PlayerVehicleEnum playerVehicleEnum(playerNum);

		Clear();

		UnitEx unit;
		while (playerVehicleEnum.GetNext(unit))
		{
			map_id unitType = unit.GetType();
			map_id unitCargo = map_id::mapNone;

			Truck_Cargo truckCargo = Truck_Cargo::truckEmpty;

			if (unitType == map_id::mapCargoTruck)
				truckCargo = unit.GetCargoType();
			else
				unitCargo = unit.GetCargo();

			SortVehicle(unitType, unitCargo, truckCargo);
		}
	}

	void VehicleCounter::PullVehiclesFromRectangle(PlayerNum playerNum, const MAP_RECT& mapRect)
	{
		InRectEnumerator inRectEnumerator(mapRect);

		Clear();

		UnitEx unit;
		while (inRectEnumerator.GetNext(unit))
		{
			if ((playerNum != PlayerNum::PlayerAll) && (unit.OwnerID() != (int)playerNum))
			{
				continue;
			}

			SortVehicle(unit.GetType(), unit.GetCargo(), unit.GetCargoType());
		}
	}

	void VehicleCounter::Clear()
	{
		vehicleCount = 0;
		nonCombatVehicleCount = 0;
		combatVehicleCount = 0;
		VehicleCountVector.clear();

		allConVecsHaveKits = true;
		allTrucksHaveCargo = true;
	}

	// PRIVATE FUNCTIONS

	void VehicleCounter::GetVehicleIndices(std::vector<int>& vehicleIndices, map_id vehicleType)
	{
		for (size_t i = 0; i < VehicleCountVector.size(); ++i)
		{
			if (VehicleCountVector[i].UnitType == vehicleType)
			{
				vehicleIndices.push_back(i);
			}
		}
	}

	/*If Unit and cargo combination do not exist in vector, -1 is returned.*/
	int VehicleCounter::GetVehicleIndex(map_id vehicleType, map_id cargoType)
	{
		for (size_t i = 0; i < VehicleCountVector.size(); ++i)
		{
			if (VehicleCountVector[i].UnitType == vehicleType &&
				VehicleCountVector[i].UnitCargo == cargoType)
			{
				return i;
			}
		}

		return -1;
	}

	/*If Unit and cargo combination do not exist in vector, -1 is returned.*/
	int VehicleCounter::GetTruckCargoIndex(Truck_Cargo truckCargo)
	{
		for (size_t i = 0; i < truckCargoCountVector.size(); ++i)
		{
			if (truckCargoCountVector[i].TruckCargo == truckCargo)
				return i;
		}

		return -1;
	}

	void VehicleCounter::SortVehicle(map_id vehicleType, map_id cargoType, Truck_Cargo truckCargo)
	{
		AddVehicleToVector(vehicleType, cargoType);

		if (vehicleType == map_id::mapCargoTruck)
		{
			AddTruckCargoToVector(truckCargo);
		}

		//Not required because both enums only return vehicles.
		/*if (!IsVehicle(vehicleType))
		return;*/

		vehicleCount++;

		if (vehicleType == map_id::mapConVec && cargoType == map_id::mapNone)
			allConVecsHaveKits = false;

		else if (vehicleType == map_id::mapCargoTruck && truckCargo == Truck_Cargo::truckEmpty)
			allTrucksHaveCargo = false;

		if (IsWeapon(cargoType))
			combatVehicleCount++;
		else
			nonCombatVehicleCount++;
	}

	void VehicleCounter::AddVehicleToVector(map_id vehicleType, map_id cargoType)
	{
		int vehicleIndex = GetVehicleIndex(vehicleType, cargoType);

		if (vehicleIndex == -1)
		{
			VehicleCount unitCount;
			unitCount.UnitType = vehicleType;
			unitCount.UnitCargo = cargoType;
			unitCount.Count = 1;

			VehicleCountVector.push_back(unitCount);
		}
		else
		{
			VehicleCountVector[vehicleIndex].Count++;
		}
	}

	void VehicleCounter::AddTruckCargoToVector(Truck_Cargo truckCargo)
	{
		int truckCargoIndex = GetTruckCargoIndex(truckCargo);

		if (truckCargoIndex == -1)
		{
			TruckCount truckCount;
			truckCount.TruckCargo = truckCargo;
			truckCount.Count = 1;
		}
		else
		{
			truckCargoCountVector[truckCargoIndex].Count++;
		}
	}
}