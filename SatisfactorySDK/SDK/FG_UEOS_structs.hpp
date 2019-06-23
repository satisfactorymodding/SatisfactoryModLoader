#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum UEOS.ELoginMode
enum class ELoginMode : uint8_t
{
	LM_Unknown                     = 0,
	LM_IDPassword                  = 1,
	LM_ExchangeCode                = 2,
	LM_PinGrant                    = 3,
	LM_MAX                         = 4
};


// Enum UEOS.EInputControllerType
enum class EInputControllerType : uint8_t
{
	ICT_Unknown                    = 0,
	ICT_MouseKeyboard              = 1,
	ICT_Gamepad                    = 2,
	ICT_Touch                      = 3,
	ICT_MAX                        = 4
};


// Enum UEOS.ESupportedAccountType
enum class ESupportedAccountType : uint8_t
{
	SAT_Unknown                    = 0,
	SAT_Epic                       = 1,
	SAT_External                   = 2,
	SAT_MAX                        = 3
};


// Enum UEOS.ELogLevel
enum class ELogLevel : uint8_t
{
	LL_Off                         = 0,
	LL_Fatal                       = 1,
	LL_Error                       = 2,
	LL_Warning                     = 3,
	LL_Info                        = 4,
	LL_Verbose                     = 5,
	LL_VeryVerbose                 = 6,
	LL_MAX                         = 7
};



}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
