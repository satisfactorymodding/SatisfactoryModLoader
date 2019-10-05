#pragma once

#include <Lib.h>

#include "UStruct.h"
#include "UFunction.h"

#include <Windows.h>
#include <detours.h>

namespace SML {
	namespace Objects {
		/**
		* Register for classFlag
		*/
		enum EClassFlags {
			CLASS_None = 0x00000000u,
			CLASS_Abstract = 0x00000001u,
			CLASS_DefaultConfig = 0x00000002u,
			CLASS_Config = 0x00000004u,
			CLASS_Transient = 0x00000008u,
			CLASS_Parsed = 0x00000010u,
			CLASS_MatchedSerializers = 0x00000020u,
			CLASS_AdvancedDisplay = 0x00000040u,
			CLASS_Native = 0x00000080u,
			CLASS_NoExport = 0x00000100u,
			CLASS_NotPlaceable = 0x00000200u,
			CLASS_PerObjectConfig = 0x00000400u,
			CLASS_ReplicationDataIsSetUp = 0x00000800u,
			CLASS_EditInlineNew = 0x00001000u,
			CLASS_CollapseCategories = 0x00002000u,
			CLASS_Interface = 0x00004000u,
			CLASS_CustomConstructor = 0x00008000u,
			CLASS_Const = 0x00010000u,
			CLASS_LayoutChanging = 0x00020000u,
			CLASS_CompiledFromBlueprint = 0x00040000u,
			CLASS_MinimalAPI = 0x00080000u,
			CLASS_RequiredAPI = 0x00100000u,
			CLASS_DefaultToInstanced = 0x00200000u,
			CLASS_TokenStreamAssembled = 0x00400000u,
			CLASS_HasInstancedReference = 0x00800000u,
			CLASS_Hidden = 0x01000000u,
			CLASS_Deprecated = 0x02000000u,
			CLASS_HideDropDown = 0x04000000u,
			CLASS_GlobalUserConfig = 0x08000000u,
			CLASS_Intrinsic = 0x10000000u,
			CLASS_Constructed = 0x20000000u,
			CLASS_ConfigDoNotCheckDefaults = 0x40000000u,
			CLASS_NewerVersionExists = 0x80000000u
		};

		/**
		* Register for castFlag to check in wich types the class is able to cast
		*/
		enum EClassCastFlags : std::uint64_t {
			CAST_None = 0x0000000000000000,
			CAST_UField = 0x0000000000000001,
			CAST_UInt8Property = 0x0000000000000002,
			CAST_UEnum = 0x0000000000000004,
			CAST_UStruct = 0x0000000000000008,
			CAST_UScriptStruct = 0x0000000000000010,
			CAST_UClass = 0x0000000000000020,
			CAST_UByteProperty = 0x0000000000000040,
			CAST_UIntProperty = 0x0000000000000080,
			CAST_UFloatProperty = 0x0000000000000100,
			CAST_UUInt64Property = 0x0000000000000200,
			CAST_UClassProperty = 0x0000000000000400,
			CAST_UUInt32Property = 0x0000000000000800,
			CAST_UInterfaceProperty = 0x0000000000001000,
			CAST_UNameProperty = 0x0000000000002000,
			CAST_UStrProperty = 0x0000000000004000,
			CAST_UProperty = 0x0000000000008000,
			CAST_UObjectProperty = 0x0000000000010000,
			CAST_UBoolProperty = 0x0000000000020000,
			CAST_UUInt16Property = 0x0000000000040000,
			CAST_UFunction = 0x0000000000080000,
			CAST_UStructProperty = 0x0000000000100000,
			CAST_UArrayProperty = 0x0000000000200000,
			CAST_UInt64Property = 0x0000000000400000,
			CAST_UDelegateProperty = 0x0000000000800000,
			CAST_UNumericProperty = 0x0000000001000000,
			CAST_UMulticastDelegateProperty = 0x0000000002000000,
			CAST_UObjectPropertyBase = 0x0000000004000000,
			CAST_UWeakObjectProperty = 0x0000000008000000,
			CAST_ULazyObjectProperty = 0x0000000010000000,
			CAST_USoftObjectProperty = 0x0000000020000000,
			CAST_UTextProperty = 0x0000000040000000,
			CAST_UInt16Property = 0x0000000080000000,
			CAST_UDoubleProperty = 0x0000000100000000,
			CAST_USoftClassProperty = 0x0000000200000000,
			CAST_UPackage = 0x0000000400000000,
			CAST_ULevel = 0x0000000800000000,
			CAST_AActor = 0x0000001000000000,
			CAST_APlayerController = 0x0000002000000000,
			CAST_APawn = 0x0000004000000000,
			CAST_USceneComponent = 0x0000008000000000,
			CAST_UPrimitiveComponent = 0x0000010000000000,
			CAST_USkinnedMeshComponent = 0x0000020000000000,
			CAST_USkeletalMeshComponent = 0x0000040000000000,
			CAST_UBlueprint = 0x0000080000000000,
			CAST_UDelegateFunction = 0x0000100000000000,
			CAST_UStaticMeshComponent = 0x0000200000000000,
			CAST_UMapProperty = 0x0000400000000000,
			CAST_USetProperty = 0x0000800000000000,
			CAST_UEnumProperty = 0x0001000000000000,
		};

		class FVTableHelper;
		struct FClassBaseChain {
			std::uint8_t unknownData[10];
		};

		/**
		* Representation of a class in the UObjectSystem (Unreals reflection system)
		*/
		class UClass : public UStruct, FClassBaseChain {
		public:
			static UFunction*(*findFunction_f)(UObject*, Objects::FName);

			void(__fastcall *ClassConstructor)(void *);
			UObject *(__fastcall *ClassVTableHelperCtorCaller)(void *);
			void(__fastcall *ClassAddReferencedObjects)(void *, void *);
			unsigned __int32 ClassUnique : 31;
			unsigned __int32 bCooked : 1;
			EClassFlags ClassFlags;
			EClassCastFlags castFlags;
			UClass *ClassWithin;
			UObject *ClassGeneratedBy;
			void* uberGraphFrame;
			FName config;
			TArray<void*> reps;
			TArray<void*> netFields;
			UObject* defaultObj;

			/**
			* Creates an instance based on this class
			*/
			template<typename T>
			SML_API inline T* createDefObj() {
				return static_cast<T*>(createDefObj());
			}

			/**
			* returns the registers UClass instance
			*/
			SML_API static UClass* staticClass();

			/**
			* Creates an instance based on this class
			*/
			SML_API UObject* createDefObj();

			/**
			* Trys to find a UField in this classed by the given name otherwise returns nullptr
			*
			* @author Panakotta00
			*/
			template<typename T>
			inline T* findField(const std::string& name) {
				auto field = this->childs;
				while (field) {
					if (field->getName() == name) {
						return (T*)field;
					} else {
						field = field->next;
					}
				}
				return nullptr;
			}

			/**
			* prints out usful information about this UClass
			*
			* @author Panakotta00
			*/
			SML_API void debug();
		};
	}
}