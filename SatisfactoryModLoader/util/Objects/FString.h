#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>

#include "TArray.h"

namespace SML {
	namespace Objects {
		/**
		* Array of characters used as string in Unreal
		*
		* @author Panakotta00
		*/
		class FString : public TArray<wchar_t> {
		public:
			/**
			* Constructs a empty FString
			*
			* @author Panakotta00
			*/
			SML_API FString();
			
			/**
			* Constructs a FString filled with the given characters
			*
			* @author Panakotta00
			*/
			SML_API FString(const wchar_t* other);
			
			/**
			* Constructs a FString filled with the given characters
			*
			* @author Panakotta00
			*/
			SML_API FString(const char* message);

			/**
			* Copys the given FString
			*
			* @author Panakotta00
			*/
			SML_API FString(const FString& other);

			/**
			* Moves the given FString
			*
			* @author Panakotta00
			*/
			SML_API FString(FString&& other);

			/**
			* Deconstructs the FString
			*
			* @author Panakotta00
			*/
			SML_API ~FString();

			/**
			* Copys the given FString into this FString
			*
			* @author Panakotta00
			*/
			SML_API FString& operator=(const FString& other);
			
			/**
			* Moves the given FString into this FString
			*
			* @author Panakotta00
			*/
			SML_API FString& operator=(FString&& other);

			/**
			* Checks if the FString is valid
			*
			* @author Panakotta00
			*/
			SML_API bool isValid() const;

			/**
			* Returns the content as copied string
			*
			* @author Panakotta00
			*/
			SML_API const wchar_t* c_str() const;

			/**
			* returns the content as copied std::string
			*
			* @author Panakotta00
			*/
			SML_API std::string toStr() const;
		};
	}
}