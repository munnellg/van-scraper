#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

#include <string>

enum class IsPresent
{
	unknown,
	unrecognised,
	no,
	yes,
};

enum class FuelType
{
	unknown,
	unrecognised,
	diesel,
	petrol,
	electric
};

enum class Transmission
{
	unknown,
	unrecognised,
	manual,
	automatic
};

enum class HeightCode
{
	unknown,
	unrecognised,
	h1,
	h2,
	h3
};

enum class LengthCode
{
	unknown,
	unrecognised,
	l1,
	l2,
	l3,
	l4
};

std::string isPresentToString(IsPresent ip);

IsPresent stringToIsPresent(std::string s);

std::string fuelTypeToString(FuelType ft);

FuelType stringToFuelType(std::string s);

std::string transmissionToString(Transmission t);

Transmission stringToTransmission(std::string s);

std::string heightCodeToString(HeightCode hc);

HeightCode stringToHeightCode(std::string s);

std::string lengthCodeToString(LengthCode lc);

LengthCode stringToLengthCode(std::string s);

#endif