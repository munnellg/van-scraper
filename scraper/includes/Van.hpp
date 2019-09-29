#ifndef __VAN_HPP__
#define __VAN_HPP__

#include "Enums.hpp"

#include <string>
#include <ostream>

class Van
{
private:

	std::string uuid;

	int price;

	int year;

	LengthCode lengthCode;

	HeightCode heightCode;

	std::string adTitle;

	std::string make;
	
	std::string model;

	double mileage;

	double emissions;

	std::string bodyType;

	double engineSize;

	double milesPerGallon;

	double payload;

	double length;

	FuelType fuelType;

	std::string colour;

	Transmission transmission;

	IsPresent hasAbs;

	IsPresent hasAirConditioning;

	IsPresent hasAirbags;

	IsPresent hasBluetooth;

	IsPresent hasBulkhead;

	IsPresent hasCdPlayer;

	IsPresent hasElectricMirrors;

	IsPresent hasElectricWindows;

	IsPresent hasHeatedSeats;

	IsPresent hasPlyLining;

	IsPresent hasPowerSteering;

	IsPresent hasCruiseControl;

	std::string advertisementUrl;

public:
	Van();

	~Van();

	void setUuid(std::string uuid);

	void setHeightCode(HeightCode hc);

	void setLengthCode(LengthCode lc);

	void setAdTitle(std::string adTitle);

	std::string getAdTitle();

	void setPrice(int price);

	void setYear(int year);

	void setMake(std::string make);

	void setModel(std::string model);

	void setMileage(double mileage);

	void setEmissions(double emissions);

	void setBodyType(std::string bodyType);

	void setEngineSize(double engineSize);

	void setMilesPerGallon(double milesPerGallon);

	void setPayload(double payload);

	void setLength(double length);

	void setFuelType(FuelType fuelType);

	void setColour(std::string colour);

	void setTransmission(Transmission transmission);

	void setHasAbs(IsPresent hasAbs);

	void setHasAirConditioning(IsPresent hasAirConditioning);

	void setHasAirbags(IsPresent hasAirbags);

	void setHasBluetooth(IsPresent hasBluetooth);

	void setHasBulkhead(IsPresent hasBulkhead);

	void setHasCdPlayer(IsPresent hasCdPlayer);

	void setHasCruiseControl(IsPresent hasCruiseControl);

	void setHasElectricMirrors(IsPresent hasElectricMirrors);

	void setHasElectricWindows(IsPresent hasElectricWindows);

	void setHasHeatedSeats(IsPresent hasHeatedSeats);

	void setHasPlyLining(IsPresent hasPlyLining);

	void setHasPowerSteering(IsPresent hasPowerSteering);

	void setAdvertisementUrl(std::string advertisementUrl);

	std::string getAdvertisementUrl();

	friend std::ostream& operator<<(std::ostream &os, const Van &van);
};

#endif