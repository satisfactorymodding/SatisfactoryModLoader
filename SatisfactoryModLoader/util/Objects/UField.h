#pragma once

#include "UObject.h"

namespace SML {
	namespace Objects {
		/**
		* Representation of field in a UClass
		* 
		* Nearly everything a UClass contains and stores information are UFields like Variables and Functions.
		*
		* @author Panakotta00
		*/
		SML_API class UField : public UObject {
		public:
			/**
			* Points to the next UField in the field array of a UClass
			*
			* @author Panakotta00
			*/
			UField*	next;

			/**
			* Returns the UClass instance of the UField
			*
			* @author Panakotta00
			*/
			SML_API static UClass* staticClass();
		};
	}
}