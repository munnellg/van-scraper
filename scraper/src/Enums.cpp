#include "Enums.hpp"
#include "Utils.hpp"

#include <map>

static std::string UNKNOWN      = "UNKNOWN";
static std::string UNRECOGNISED = "UNRECOGNISED";

static std::string NO  = "NO";
static std::string YES = "YES";

static std::string DIESEL   = "DIESEL";
static std::string PETROL   = "PETROL";
static std::string ELECTRIC = "ELECTRIC";

static std::string MANUAL    = "MANUAL";
static std::string AUTOMATIC = "AUTOMATIC";

static std::string H1 = "H1";
static std::string H2 = "H2";
static std::string H3 = "H3";

static std::string L1 = "L1";
static std::string L2 = "L2";
static std::string L3 = "L3";
static std::string L4 = "L4";

static std::map<std::string, IsPresent> lookupStringToIsPresent = {
	{ UNKNOWN,      IsPresent::unknown      },
	{ UNRECOGNISED, IsPresent::unrecognised },
	{ NO,           IsPresent::no           },
	{ YES,          IsPresent::yes          }
};

static std::map<IsPresent, std::string> lookupIsPresentToString = {
	{ IsPresent::unknown,      UNKNOWN      },
	{ IsPresent::unrecognised, UNRECOGNISED },
	{ IsPresent::no,           NO           },
	{ IsPresent::yes,          YES          }
};

static std::map<std::string, FuelType> lookupStringToFuelType = {
	{ UNKNOWN,      FuelType::unknown      },
	{ UNRECOGNISED, FuelType::unrecognised },
	{ DIESEL,       FuelType::diesel       },
	{ PETROL,       FuelType::petrol       },
	{ ELECTRIC,     FuelType::electric     }
};

static std::map<FuelType, std::string> lookupFuelTypeToString = {
	{ FuelType::unknown,      UNKNOWN      },
	{ FuelType::unrecognised, UNRECOGNISED },
	{ FuelType::diesel,       DIESEL       },
	{ FuelType::petrol,       PETROL       },
	{ FuelType::electric,     ELECTRIC     }
};

static std::map<std::string, Transmission> lookupStringToTransmission = {
	{ UNKNOWN,      Transmission::unknown      },
	{ UNRECOGNISED, Transmission::unrecognised },
	{ MANUAL,       Transmission::manual       },
	{ AUTOMATIC,    Transmission::automatic    }
};

static std::map<Transmission, std::string> lookupTransmissionToString = {
	{ Transmission::unknown,      UNKNOWN      },
	{ Transmission::unrecognised, UNRECOGNISED },
	{ Transmission::manual,       MANUAL       },
	{ Transmission::automatic,    AUTOMATIC    }
};

static std::map<std::string, LengthCode> lookupStringToLengthCode = {
	{ UNKNOWN,      LengthCode::unknown      },
	{ UNRECOGNISED, LengthCode::unrecognised },
	{ L1,           LengthCode::l1           },
	{ L2,           LengthCode::l2           },
	{ L3,           LengthCode::l3           },
	{ L4,           LengthCode::l4           }
};

static std::map<LengthCode, std::string> lookupLengthCodeToString = {
	{ LengthCode::unknown,      UNKNOWN      },
	{ LengthCode::unrecognised, UNRECOGNISED },
	{ LengthCode::l1,           L1           },
	{ LengthCode::l2,           L2           },
	{ LengthCode::l3,           L3           },
	{ LengthCode::l4,           L4           }
};

static std::map<std::string, HeightCode> lookupStringToHeightCode = {
	{ UNKNOWN,      HeightCode::unknown      },
	{ UNRECOGNISED, HeightCode::unrecognised },
	{ H1,           HeightCode::h1           },
	{ H2,           HeightCode::h2           },
	{ H3,           HeightCode::h3           }
};

static std::map<HeightCode, std::string> lookupHeightCodeToString = {
	{ HeightCode::unknown,      UNKNOWN      },
	{ HeightCode::unrecognised, UNRECOGNISED },
	{ HeightCode::h1,           H1           },
	{ HeightCode::h2,           H2           },
	{ HeightCode::h3,           H3           }
};

template <class T>
std::string enumToString(T value, std::map<T, std::string> lookup,
		std::string defaultValue)
{
	auto itString = lookup.find(value);

	if (itString != lookup.end()) {
		return itString->second;
	}

	return defaultValue;
}

template <class T>
T stringToEnum(std::string s, std::map<std::string, T> lookup, T defaultValue)
{
	s = upperCase(s);

	auto itT = lookup.find(s);

	if (itT != lookup.end()) {
		return itT->second;
	}

	return defaultValue;
}

std::string isPresentToString(IsPresent ip)
{
	return enumToString<IsPresent>(
		ip, lookupIsPresentToString, UNRECOGNISED
	);
}

IsPresent stringToIsPresent(std::string s)
{
	return stringToEnum<IsPresent>(
		s, lookupStringToIsPresent, IsPresent::unrecognised
	);
}

std::string fuelTypeToString(FuelType ft)
{
	return enumToString<FuelType>(
		ft, lookupFuelTypeToString, UNRECOGNISED
	);
}

FuelType stringToFuelType(std::string s)
{
	return stringToEnum<FuelType>(
		s, lookupStringToFuelType, FuelType::unrecognised
	);
}

std::string transmissionToString(Transmission t)
{
	return enumToString<Transmission>(
		t, lookupTransmissionToString, UNRECOGNISED
	);
}

Transmission stringToTransmission(std::string s)
{
	return stringToEnum<Transmission>(
		s, lookupStringToTransmission, Transmission::unrecognised
	);
}

std::string heightCodeToString(HeightCode hc)
{
	return enumToString<HeightCode>(
		hc, lookupHeightCodeToString, UNRECOGNISED
	);
}

HeightCode stringToHeightCode(std::string s)
{
	return stringToEnum<HeightCode>(
		s, lookupStringToHeightCode, HeightCode::unrecognised
	);
}

std::string lengthCodeToString(LengthCode lc)
{
	return enumToString<LengthCode>(
		lc, lookupLengthCodeToString, UNRECOGNISED
	);
}

LengthCode stringToLengthCode(std::string s)
{
	return stringToEnum<LengthCode>(
		s, lookupStringToLengthCode, LengthCode::unrecognised
	);
}
