#include "Van.hpp"
#include "Enums.hpp"

Van::Van()
{
	this->uuid = "";
	this->heightCode = HeightCode::unknown;
	this->lengthCode = LengthCode::unknown;
	this->adTitle = "";
	this->price = 0;
	this->mileage = 0;
	this->milesPerGallon = 0;
	this->length = 0;
	this->make = "";
	this->model = "";
	this->mileage = 0;
	this->emissions = 0;
	this->bodyType = "";
	this->engineSize = 0;
	this->fuelType = FuelType::unknown;
	this->colour = "";
	this->transmission = Transmission::unknown;
	this->hasAbs = IsPresent::unknown;
	this->hasAirConditioning = IsPresent::unknown;
	this->hasAirbags = IsPresent::unknown;
	this->hasBluetooth = IsPresent::unknown;
	this->hasBulkhead = IsPresent::unknown;
	this->hasCdPlayer = IsPresent::unknown;
	this->hasCruiseControl = IsPresent::unknown;
	this->hasElectricMirrors = IsPresent::unknown;
	this->hasElectricWindows = IsPresent::unknown;
	this->hasHeatedSeats = IsPresent::unknown;
	this->hasPlyLining = IsPresent::unknown;
	this->hasPowerSteering = IsPresent::unknown;
	this->advertisementUrl = "";
}

Van::~Van()
{

}

void Van::setUuid(std::string uuid)
{
	this->uuid = uuid;
}

void Van::setHeightCode(HeightCode hc)
{
	this->heightCode = hc;
}

void Van::setLengthCode(LengthCode lc)
{
	this->lengthCode = lc;
}

void Van::setAdTitle(std::string adTitle)
{
	this->adTitle = adTitle;
}

std::string Van::getAdTitle()
{
	return this->adTitle;
}

void Van::setPrice(int price)
{
	this->price = price;	
}

void Van::setYear(int year)
{
	this->year = year;
}

void Van::setMake(std::string make)
{
	this->make = make;	
}

void Van::setModel(std::string model)
{
	this->model = model;	
}

void Van::setMileage(double mileage)
{
	this->mileage = mileage;
}

void Van::setEmissions(double emissions)
{
	this->emissions = emissions;
}

void Van::setBodyType(std::string bodyType)
{
	this->bodyType = bodyType;
}

void Van::setEngineSize(double engineSize)
{
	this->engineSize = engineSize;
}

void Van::setMilesPerGallon(double milesPerGallon)
{
	this->milesPerGallon = milesPerGallon;
}

void Van::setPayload(double payload)
{
	this->payload = payload;
}

void Van::setLength(double length)
{
	this->length = length;
}

void Van::setFuelType(FuelType fuelType)
{
	this->fuelType = fuelType;
}

void Van::setColour(std::string colour)
{
	this->colour = colour;
}

void Van::setTransmission(Transmission transmission)
{
	this->transmission = transmission;
}

void Van::setHasAbs(IsPresent hasAbs)
{
	this->hasAbs = hasAbs;
}

void Van::setHasAirConditioning(IsPresent hasAirConditioning)
{
	this->hasAirConditioning = hasAirConditioning;
}

void Van::setHasAirbags(IsPresent hasAirbags)
{
	this->hasAirbags = hasAirbags;
}

void Van::setHasBluetooth(IsPresent hasBluetooth)
{
	this->hasBluetooth = hasBluetooth;
}

void Van::setHasBulkhead(IsPresent hasBulkhead)
{
	this->hasBulkhead = hasBulkhead;
}

void Van::setHasCdPlayer(IsPresent hasCdPlayer)
{
	this->hasCdPlayer = hasCdPlayer;
}

void Van::setHasCruiseControl(IsPresent hasCruiseControl)
{
	this->hasCruiseControl = hasCruiseControl;
}

void Van::setHasElectricMirrors(IsPresent hasElectricMirrors)
{
	this->hasElectricMirrors = hasElectricMirrors;
}

void Van::setHasElectricWindows(IsPresent hasElectricWindows)
{
	this->hasElectricWindows = hasElectricWindows;
}

void Van::setHasHeatedSeats(IsPresent hasHeatedSeats)
{
	this->hasHeatedSeats = hasHeatedSeats;
}

void Van::setHasPlyLining(IsPresent hasPlyLining)
{
	this->hasPlyLining = hasPlyLining;
}

void Van::setHasPowerSteering(IsPresent hasPowerSteering)
{
	this->hasPowerSteering = hasPowerSteering;
}

void Van::setAdvertisementUrl(std::string advertisementUrl)
{
	this->advertisementUrl = advertisementUrl;	
}

std::string Van::getAdvertisementUrl()
{
	return this->advertisementUrl;
}

std::ostream& operator<<(std::ostream &os, const Van &van)
{
	os << van.adTitle << "\t" <<
		van.make << "\t" <<
		van.model << "\t" <<
		van.year << "\t" <<
		(double) van.price / 100 << "\t" <<
		lengthCodeToString(van.lengthCode) << "\t" <<
		heightCodeToString(van.heightCode) << "\t" <<
		van.mileage << "\t" <<
		van.emissions << "\t" <<
		van.bodyType << "\t" <<
		van.engineSize << "\t" <<
		van.milesPerGallon << "\t" <<
		van.payload << "\t" <<
		van.length << "\t" <<
		fuelTypeToString(van.fuelType) << "\t" <<
		van.colour << "\t" <<
		transmissionToString(van.transmission) << "\t" <<
		isPresentToString(van.hasAbs) << "\t" <<
		isPresentToString(van.hasAirConditioning) << "\t" <<
		isPresentToString(van.hasAirbags) << "\t" <<
		isPresentToString(van.hasBluetooth) << "\t" <<
		isPresentToString(van.hasBulkhead) << "\t" <<
		isPresentToString(van.hasCdPlayer) << "\t" <<
		isPresentToString(van.hasElectricMirrors) << "\t" <<
		isPresentToString(van.hasElectricWindows) << "\t" <<
		isPresentToString(van.hasHeatedSeats) << "\t" <<
		isPresentToString(van.hasPlyLining) << "\t" <<
		isPresentToString(van.hasPowerSteering) << "\t" <<
		isPresentToString(van.hasCruiseControl) << "\t" <<
		van.advertisementUrl << "\t" <<
    	van.uuid;

    return os;
}