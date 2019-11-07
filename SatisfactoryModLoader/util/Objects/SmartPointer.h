#pragma once

#include "UObject.h"
#include "../SatisfactorySDK/SDK.hpp"

namespace SML {
	namespace Objects {
		struct FWeakObjectPtr {
			std::int32_t index;
			std::int32_t serial;

			/*
			* Constructs a FWeakObjectPointer and indirectly references the given UObject
			*
			* @author Panakotta00
			*/
			SML_API FWeakObjectPtr(UObject* o);
			
			/*
			* Converts a SDK::TWeakObjectPtr<?, SDK::FWeakObjectPtr> to a FWeakObjectPtr
			*
			* @author Panakotta00
			*/
			template<typename T1>
			SML_API inline FWeakObjectPtr(const SDK::TWeakObjectPtr<T1, SDK::FWeakObjectPtr>& o) {
				(*this) = *((FWeakObjectPtr*)&o);
			}
			
			/*
			* checks if the weak ptr refers to a valid object
			*
			* @author Panakotta00
			*/
			SML_API bool isValid() const;
			
			/*
			* returns the pointer to refered object, if it is not valid, then nullptr
			*
			* @author Panakotta00
			*/
			SML_API UObject* get() const;

			/*
			* returns the pointer like get()
			*
			* @author Panakotta00
			*/
			SML_API UObject* operator*() const;
			
			/*
			* accesses the get() pointer
			*
			* @author Panakotta00
			*/
			SML_API UObject* operator->() const;
			
			/*
			* checks if two weak object pointer refer to the same valid object
			*
			* @author Panakotta00
			*/
			SML_API bool operator==(const FWeakObjectPtr& o) const;

			/*
			* sets the reference to the reference of the given weak object ptr
			*
			* @author Panakotta00
			*/
			SML_API void operator=(const FWeakObjectPtr& o);

			/*
			* sets the weak reference to the given UObject
			*
			* @author Panakotta00
			*/
			SML_API void operator=(UObject* o);

			/*
			* checks if the given weak object index & serial is biger than self
			*
			* @author Panakotta00
			*/
			SML_API bool operator<(const FWeakObjectPtr& o) const;
		};
	}
}