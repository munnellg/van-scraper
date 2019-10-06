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
	std::string getUuid();

	void setHeightCode(HeightCode heightCode);
	HeightCode getHeightCode();

	void setLengthCode(LengthCode lengthCode);
	LengthCode getLengthCode();

	void setAdTitle(std::string adTitle);
	std::string getAdTitle();

	void setPrice(int price);
	int getPrice();

	void setYear(int year);
	int getYear();

	void setMake(std::string make);
	std::string getMake();

	void setModel(std::string model);
	std::string getModel();

	void setMileage(double mileage);
	double getMileage();

	void setEmissions(double emissions);
	double getEmissions();

	void setBodyType(std::string bodyType);
	std::string getBodyType();

	void setEngineSize(double engineSize);
	double getEngineSize();

	void setMilesPerGallon(double milesPerGallon);
	double getMilesPerGallon();

	void setPayload(double payload);
	double getPayload();

	void setLength(double length);
	double getLength();

	void setFuelType(FuelType fuelType);
	FuelType getFuelType();

	void setColour(std::string colour);
	std::string getColour();

	void setTransmission(Transmission transmission);
	Transmission getTransmission();

	void setHasAbs(IsPresent hasAbs);
	IsPresent getHasAbs();

	void setHasAirConditioning(IsPresent hasAirConditioning);
	IsPresent getHasAirConditioning();

	void setHasAirbags(IsPresent hasAirbags);
	IsPresent getHasAirbags();

	void setHasBluetooth(IsPresent hasBluetooth);
	IsPresent getHasBluetooth();

	void setHasBulkhead(IsPresent hasBulkhead);
	IsPresent getHasBulkhead();

	void setHasCdPlayer(IsPresent hasCdPlayer);
	IsPresent getHasCdPlayer();

	void setHasCruiseControl(IsPresent hasCruiseControl);
	IsPresent getHasCruiseControl();

	void setHasElectricMirrors(IsPresent hasElectricMirrors);
	IsPresent getHasElectricMirrors();

	void setHasElectricWindows(IsPresent hasElectricWindows);
	IsPresent getHasElectricWindows();

	void setHasHeatedSeats(IsPresent hasHeatedSeats);
	IsPresent getHasHeatedSeats();

	void setHasPlyLining(IsPresent hasPlyLining);
	IsPresent getHasPlyLining();

	void setHasPowerSteering(IsPresent hasPowerSteering);
	IsPresent getHasPowerSteering();

	void setAdvertisementUrl(std::string advertisementUrl);
	std::string getAdvertisementUrl();

	friend std::ostream& operator<<(std::ostream &os, const Van &van);
};

#endif