#pragma once

#include <cstdint>

#include "UObject.h"
#include "UField.h"
#include "FName.h"

namespace SML {
	namespace Objects {
		/**
		* Enum of available property types
		**/
		enum class EPropertyClass {
			Byte,
			Int8,
			Int16,
			Int,
			Int64,
			UInt16,
			UInt32,
			UInt64,
			UnsizedInt,
			UnsizedUInt,
			Float,
			Double,
			Bool,
			SoftClass,
			WeakObject,
			LazyObject,
			SoftObject,
			Class,
			Object,
			Interface,
			Name,
			Str,
			Array,
			Map,
			Set,
			Struct,
			Delegate,
			MulticastDelegate,
			Text,
			Enum,
		};

		/**
		* Register enum for proprtyFlag
		*/
		enum EPropertyFlags : std::uint64_t {
			Prop_None = 0,
			Prop_Edit = 0x0000000000000001,
			Prop_ConstParm = 0x0000000000000002,
			Prop_BlueprintVisible = 0x0000000000000004,
			Prop_ExportObject = 0x0000000000000008,
			Prop_BlueprintReadOnly = 0x0000000000000010,
			Prop_Net = 0x0000000000000020,
			Prop_EditFixedSize = 0x0000000000000040,
			Prop_Parm = 0x0000000000000080,
			Prop_OutParm = 0x0000000000000100,
			Prop_ZeroConstructor = 0x0000000000000200,
			Prop_ReturnParm = 0x0000000000000400,
			Prop_DisableEditOnTemplate = 0x0000000000000800,
			Prop_Transient = 0x0000000000002000,
			Prop_Config = 0x0000000000004000,
			Prop_DisableEditOnInstance = 0x0000000000010000,
			Prop_EditConst = 0x0000000000020000,
			Prop_GlobalConfig = 0x0000000000040000,
			Prop_InstancedReference = 0x0000000000080000,
			Prop_DuplicateTransient = 0x0000000000200000,
			Prop_SubobjectReference = 0x0000000000400000,
			Prop_SaveGame = 0x0000000001000000,
			Prop_NoClear = 0x0000000002000000,
			Prop_ReferenceParm = 0x0000000008000000,
			Prop_BlueprintAssignable = 0x0000000010000000,
			Prop_Deprecated = 0x0000000020000000,
			Prop_IsPlainOldData = 0x0000000040000000,
			Prop_RepSkip = 0x0000000080000000,
			Prop_RepNotify = 0x0000000100000000,
			Prop_Interp = 0x0000000200000000,
			Prop_NonTransactional = 0x0000000400000000,
			Prop_EditorOnly = 0x0000000800000000,
			Prop_NoDestructor = 0x0000001000000000,
			Prop_AutoWeak = 0x0000004000000000,
			Prop_ContainsInstancedReference = 0x0000008000000000,
			Prop_AssetRegistrySearchable = 0x0000010000000000,
			Prop_SimpleDisplay = 0x0000020000000000,
			Prop_AdvancedDisplay = 0x0000040000000000,
			Prop_Protected = 0x0000080000000000,
			Prop_BlueprintCallable = 0x0000100000000000,
			Prop_BlueprintAuthorityOnly = 0x0000200000000000,
			Prop_TextExportTransient = 0x0000400000000000,
			Prop_NonPIEDuplicateTransient = 0x0000800000000000,
			Prop_ExposeOnSpawn = 0x0001000000000000,
			Prop_PersistentInstance = 0x0002000000000000,
			Prop_UObjectWrapper = 0x0004000000000000,
			Prop_HasGetValueTypeHash = 0x0008000000000000,
			Prop_NativeAccessSpecifierPublic = 0x0010000000000000,
			Prop_NativeAccessSpecifierProtected = 0x0020000000000000,
			Prop_NativeAccessSpecifierPrivate = 0x0040000000000000,
			Prop_SkipSerialization = 0x0080000000000000,
		};

		/**
		* Representation of f.e. Varaibles of a UClass
		*/
		class UProperty : public UField {
		public:
			std::int32_t dim;
			std::int32_t elemSize;
			EPropertyFlags propFlags;
			std::uint16_t repIndex;
			std::uint8_t BPReplicCond;
			std::int32_t internalOffset;
			FName repNFunc;
			UProperty* nextProp;
			UProperty* nextRef;
			UProperty* nextDestruct;
			UProperty* nextConstruct;

			/**
			* Returns the pointer to the value of this property in the given instance
			*
			* @author Panakotta00
			*/
			template<typename T>
			inline T* getValue(void* container) {
				return (T*)((std::uint64_t)container + (std::uint64_t)internalOffset);
			}

			/**
			* Returns the UClass of UProperty
			*/
			SML_API static UClass* staticClass();
		};

		/**
		* Representation of a UObject* attribute of a UClass
		*/
		class UObjectProperty : public UProperty {
		public:
			UClass* objClass;
		};

		/**
		* Representation of a MulticastDelegate attribute of a UClass
		*/
		class UMulticastDelegateProperty : public UProperty {
		public:
			UFunction* sigFunc;
		};

		/**
		* Representation of a Bool attribute of a UClass
		*/
		class __declspec(align(8)) UBoolProperty : public UProperty {
		public:
			char fSize;
			char bOff;
			char bMask;
			char fMask;

			SML_API bool isSet(void* container);
		};

	}
}