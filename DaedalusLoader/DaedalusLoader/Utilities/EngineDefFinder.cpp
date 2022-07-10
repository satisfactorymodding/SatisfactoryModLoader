#include "../UE4/Ue4.hpp"
#include "Utilities/Logger.h"
namespace ClassDefFinder
{
	bool FindUObjectIndexDefs(UE4::UObject* CoreUObject, UE4::UObject* UEObject)
	{
		Log::Info("Scanning For UObject Index Def. (CoreUObject: 0x%p, UEObject: 0x%p)", CoreUObject, UEObject);
		bool HasIndexNotBeenFound = true;

		while (HasIndexNotBeenFound)
		{
			if (Read<int32_t>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Index) == 1)
			{
				if (Read<int32_t>((byte*)UEObject + GameProfile::SelectedGameProfile.defs.UObject.Index) == 2)
				{
					HasIndexNotBeenFound = false;
				}
			}
			GameProfile::SelectedGameProfile.defs.UObject.Index = GameProfile::SelectedGameProfile.defs.UObject.Index + 1;
		}
		Log::Info("UObject Index Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UObject.Index);
		return true;
	};

	bool FindUObjectNameDefs(UE4::UObject* CoreUObject)
	{
		bool HasNameNotBeenFound = true;
		bool HasHardNameCheck = false;
		Log::Info("Scanning For UObject Name Def.");
		while (HasNameNotBeenFound)
		{
			UE4::FName Name;
			if (HasHardNameCheck == false)
			{
				GameProfile::SelectedGameProfile.defs.UObject.Name = 0x18;
				HasHardNameCheck = true;
			}
			Name = *reinterpret_cast<UE4::FName*>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Name);
			if (GameProfile::SelectedGameProfile.UsesFNamePool)
			{
				if (UE4::FName::GetFNamePool().IsValidIndex(Name.ComparisonIndex))
				{
					if (Name.GetName() == "Object")
					{
						HasNameNotBeenFound = false;
					}
				}
			}
			else
			{
				if (UE4::FName::GetTNameArray().IsValidIndex(Name.ComparisonIndex))
				{
					if (Name.GetName() == "Object")
					{
						HasNameNotBeenFound = false;
					}
				}
			}
			if (HasNameNotBeenFound == true)
			{
				GameProfile::SelectedGameProfile.defs.UObject.Name = GameProfile::SelectedGameProfile.defs.UObject.Name + 0x8;
			}
		}
		Log::Info("UObject Name Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UObject.Name);
		return true;
	}

	bool FindUObjectClassDefs(UE4::UObject* CoreUObject)
	{
		bool HasClassNotBeenFound = true;
		bool HasFinishedHardCheck = false;
		Log::Info("Scanning For UObject Class Def.");
		while (HasClassNotBeenFound)
		{
			UE4::UClass* Class;
			if (HasFinishedHardCheck == false)
			{
				GameProfile::SelectedGameProfile.defs.UObject.Class = 0x10;
				Class = Read<UE4::UClass*>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Class);
				HasFinishedHardCheck = true;
			}
			else
			{
				Class = Read<UE4::UClass*>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Class);
			}
			
			auto ClassIndex = Class->GetIndex();
			UE4::UObject* ClassCheck;
			if (GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray)
			{
				ClassCheck = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(ClassIndex).Object;
			}
			else
			{
				ClassCheck = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(ClassIndex).Object;
			}

			if (ClassCheck != nullptr)
			{
				if (ClassCheck->GetName() == "Class")
				{
					HasClassNotBeenFound = false;
				}
			}
			if (HasClassNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UObject.Class = GameProfile::SelectedGameProfile.defs.UObject.Class + 0x8;
			}
		}
		Log::Info("UObject Class Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UObject.Class);
		return true;
	}

	bool FindUObjectOuterDefs(UE4::UObject* CoreUObject)
	{
		bool HasOuterNotBeenFound = true;
		Log::Info("Scanning For UObject Outer Def.");
		while (HasOuterNotBeenFound)
		{
			auto Outer = Read<UE4::UObject*>((byte*)CoreUObject + GameProfile::SelectedGameProfile.defs.UObject.Outer);
			UE4::UObject* ObjectCheck;
			if (GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray)
			{
				ObjectCheck = UE4::UObject::GObjects->GetAsChunckArray().GetByIndex(0).Object;
			}
			else
			{
				ObjectCheck = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(0).Object;
			}

			if (Outer == ObjectCheck)
			{
				HasOuterNotBeenFound = false;
			}
			if (HasOuterNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UObject.Outer = GameProfile::SelectedGameProfile.defs.UObject.Outer + 0x8;
			}
		}
		Log::Info("UObject Outer Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UObject.Outer);
		return true;
	}

	bool FindUObjectDefs(UE4::UObject* CoreUObject, UE4::UObject* UEObject)
	{
		if (FindUObjectIndexDefs(CoreUObject, UEObject) && FindUObjectNameDefs(CoreUObject) && FindUObjectClassDefs(CoreUObject) && FindUObjectOuterDefs(CoreUObject))
		{
			Log::Info("UObject Defined");
			return true;
		}
		else
		{
			Log::Error("UObject could not be defined. Try Manually Defining in the game profile file.");
		}
		return false;
	}

	bool FindUFieldNextDef()
	{
		Log::Info("Scanning For UField Next Def.");
		bool HasNextNotBeenFound = true;
		auto UserConstructionScript = UE4::UObject::FindObject<UE4::UFunction>("Function Engine.Actor.UserConstructionScript");
		GameProfile::SelectedGameProfile.defs.UField.Next = GameProfile::SelectedGameProfile.defs.UObject.Outer; // Prevents scanning same area over and over.
		while (HasNextNotBeenFound)
		{
			auto NextObject = Read<UE4::UField*>((byte*)UserConstructionScript + GameProfile::SelectedGameProfile.defs.UField.Next);
			if (NextObject && NextObject->GetOuter() == UserConstructionScript->GetOuter())
			{
				HasNextNotBeenFound = false;
			}
			if (HasNextNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UField.Next = GameProfile::SelectedGameProfile.defs.UField.Next + 0x8;
			}
		}
		Log::Info("UField Next Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UField.Next);
		return true;
	}

	//bool FindUFieldNextDef()
	//{
	//	Log::Info("Scanning For UField Next Def.");
	//	bool HasNextNotBeenFound = true;
	//	auto WasRecentlyRendered = UE4::UObject::FindObject<UE4::UFunction>("Function Engine.Actor.WasRecentlyRendered");
	//	GameProfile::SelectedGameProfile.defs.UField.Next = GameProfile::SelectedGameProfile.defs.UObject.Outer; // Prevents scanning same area over and over.
	//	while (HasNextNotBeenFound)
	//	{
	//		auto NextObject = Read<UE4::UField*>((byte*)WasRecentlyRendered + GameProfile::SelectedGameProfile.defs.UField.Next);
	//		if (NextObject && NextObject->GetIndex() == WasRecentlyRendered->GetIndex() - 1)
	//		{
	//			HasNextNotBeenFound = false;
	//		}
	//		if (HasNextNotBeenFound)
	//		{
	//			GameProfile::SelectedGameProfile.defs.UField.Next = GameProfile::SelectedGameProfile.defs.UField.Next + 0x8;
	//		}
	//	}
	//	Log::Info("UField Next Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UField.Next);
	//	return true;
	//}

	bool FindUFieldDefs()
	{
		if (FindUFieldNextDef())
		{
			Log::Info("UField Defined");
			return true;
		}
		else
		{
			Log::Error("UField could not be defined. Try Manually Defining in the game profile file.");
		}
		return false;
	}

	bool FindUStructSuperFieldDef()
	{
		Log::Info("Scanning For UStruct SuperField Def.");
		auto StructObject = UE4::UObject::FindObject<UE4::UStruct>("Class CoreUObject.Struct");
		auto FieldObject = UE4::UObject::FindObject<UE4::UField>("Class CoreUObject.Field");
		bool HasSuperFieldNotBeenFound = true;
		GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct = GameProfile::SelectedGameProfile.defs.UField.Next; // Prevents scanning same area over and over.
		while (HasSuperFieldNotBeenFound)
		{
			auto SuperFieldObject = Read<UE4::UObject*>((byte*)StructObject + GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct);
			if (SuperFieldObject == FieldObject)
			{
				HasSuperFieldNotBeenFound = false;
			}
			if (HasSuperFieldNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct = GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct + 0x8;
			}
		}
		Log::Info("UStruct SuperField Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct);
		return true;
	}

	bool FindUStructChildrenDef()
	{
		Log::Info("Scanning For UStruct Children Def.");
		auto VectorObject = UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
		auto VectorFirstChildObject = UE4::UObject::FindObject<UE4::UObject>("FloatProperty CoreUObject.Vector.X");
		bool HasChildrenNotBeenFound = true;
		GameProfile::SelectedGameProfile.defs.UStruct.Children = GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct;
		while (HasChildrenNotBeenFound)
		{
			auto ChildObject = Read<UE4::UObject*>((byte*)VectorObject + GameProfile::SelectedGameProfile.defs.UStruct.Children);
			if (VectorFirstChildObject)
			{
				if (VectorFirstChildObject == ChildObject)
				{
					HasChildrenNotBeenFound = false;
				}
				if (HasChildrenNotBeenFound)
				{
					GameProfile::SelectedGameProfile.defs.UStruct.Children = GameProfile::SelectedGameProfile.defs.UStruct.Children + 0x8;
				}
			}
			else
			{
				if (auto Class = ChildObject->GetClass())
				{
					if (Class->GetName() == "FloatProperty" || "Vector")
					{
						HasChildrenNotBeenFound = false;
					}
					else
					{
						GameProfile::SelectedGameProfile.defs.UStruct.Children = GameProfile::SelectedGameProfile.defs.UStruct.Children + 0x8;
					}
				}
				else
				{
					GameProfile::SelectedGameProfile.defs.UStruct.Children = GameProfile::SelectedGameProfile.defs.UStruct.Children + 0x8;
				}
			}
		}
		Log::Info("UStruct Children Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UStruct.Children);
		return true;
	}

	bool FindUStructPropertySizeDef()
	{
		Log::Info("Scanning For UStruct PropertySize Def.");
		auto VectorObject = UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
		while (Read<int32_t>((byte*)VectorObject + GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize) != 12)
		{
			GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize = GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize + 0x4;
		}
		Log::Info("UStruct PropertySize Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize);
		return true;
	}

	int GetOverallUStructSize()
	{
		auto UStruct = UE4::UObject::FindObject<UE4::UStruct>("Class CoreUObject.Struct");
		if (UStruct)
		{
			return UStruct->GetPropertySize();
		}
	}

	bool FindUStructDefs()
	{
		if (FindUStructSuperFieldDef() && FindUStructChildrenDef() && FindUStructPropertySizeDef())
		{
			GameProfile::SelectedGameProfile.defs.UStruct.OverallUStructSize = GetOverallUStructSize();
			Log::Info("UStruct Size: %i", GameProfile::SelectedGameProfile.defs.UStruct.OverallUStructSize);
			Log::Info("UStruct Defined");
			return true;
		}
		else
		{
			Log::Error("UStruct could not be defined. Try Manually Defining in the game profile file.");
		}
		return false;
	}

	bool FindUFunctionFunctionFlagsDef()
	{
		Log::Info("Scanning For UFunction FunctionFlags Def.");
		bool HasFunctionFlagsNotBeenFound = true;
		auto WasRecentlyRendered = UE4::UObject::FindObject<UE4::UFunction>("Function Engine.Actor.WasRecentlyRendered");
		GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags = GameProfile::SelectedGameProfile.defs.UStruct.OverallUStructSize; // Prevents scanning same area over and over.
		while (HasFunctionFlagsNotBeenFound)
		{
			auto FunctionFlags = Read<int>((byte*)WasRecentlyRendered + GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags);
			if (FunctionFlags == 1409418241)
			{
				HasFunctionFlagsNotBeenFound = false;
			}
			if (HasFunctionFlagsNotBeenFound)
			{
				GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags = GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags + 0x4;
			}
		}
		Log::Info("UFunction FunctionFlags Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags);
		return true;
	}

	bool FindUFunctionFunc()
	{
		auto UFunction = UE4::UObject::FindObject<UE4::UFunction>("Class CoreUObject.Function");
		if (UFunction)
		{
			GameProfile::SelectedGameProfile.defs.UFunction.Func = UFunction->GetPropertySize() - 0x8;
			Log::Info("UFunction Func: 0x%p", GameProfile::SelectedGameProfile.defs.UFunction.Func);
			return true;
		}
		return false;
	}

	bool FindUFunctionDefs()
	{
		if (FindUFunctionFunctionFlagsDef() && FindUFunctionFunc())
		{
			Log::Info("UFunction Defined");
			return true;
		}
		else
		{
			Log::Error("UFunction could not be defined. Try Manually Defining in the game profile file.");
		}
		return false;
	}

	bool FindFField()
	{
		auto VectorObject = (UE4::UStruct*)UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
		auto FieldChild = (UE4::FField*)VectorObject->GetChildren();
		bool NameFound = false;
		bool NextFound = false;
		while (!NameFound)
		{
			auto Name = *reinterpret_cast<UE4::FName*>((byte*)FieldChild + GameProfile::SelectedGameProfile.defs.FField.Name);
			if (UE4::FName::GetFNamePool().IsValidIndex(Name.ComparisonIndex))
			{
				if (Name.GetName() == "X")
				{
					NameFound = true;
				}
			}
			if (NameFound == false)
			{
				GameProfile::SelectedGameProfile.defs.FField.Name = GameProfile::SelectedGameProfile.defs.FField.Name + 0x8;
			}
		}
		Log::Info("FField Name Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.FField.Name);
		while (!NextFound)
		{
			// 9 times out of 10, its right behind the Name, so we do that check to save possible issues
			auto NextField = Read<UE4::FField*>((byte*)FieldChild + GameProfile::SelectedGameProfile.defs.FField.Name - 0x8);
			if (NextField && NextField->GetName() == "Y")
			{
				NextFound = true;
				GameProfile::SelectedGameProfile.defs.FField.Next = GameProfile::SelectedGameProfile.defs.FField.Name - 0x8;
				break;
			}

			NextField = Read<UE4::FField*>((byte*)FieldChild + GameProfile::SelectedGameProfile.defs.FField.Next);
			if (NextField && NextField->GetName() == "Y")
			{
				NextFound = true;
			}
			if (NextFound == false)
			{
				GameProfile::SelectedGameProfile.defs.FField.Next = GameProfile::SelectedGameProfile.defs.FField.Next + 0x8;
			}
		}
		Log::Info("FField Next Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.FField.Next);
		return true;
	}

	bool FindUEPropertyDefs()
	{
		auto VectorObject = (UE4::UStruct*)UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
		bool ArrayDimFound = false;
		bool OffsetFound = false;
		if (GameProfile::SelectedGameProfile.bIsFProperty)
		{
			auto FieldChild = (UE4::FField*)VectorObject->GetChildren();
			while (!ArrayDimFound)
			{
				if (Read<int64_t>((byte*)FieldChild + GameProfile::SelectedGameProfile.defs.Property.ArrayDim) == 17179869185) // Array Dim and Element Size are Side By Side
				{
					ArrayDimFound = true;
				}

				if(ArrayDimFound == false)
				{ 
					GameProfile::SelectedGameProfile.defs.Property.ArrayDim = GameProfile::SelectedGameProfile.defs.Property.ArrayDim + 0x8;
				}
			}
			Log::Info("FProperty Array Dim Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.Property.ArrayDim);

			auto FieldChildY = FieldChild->GetNext();
			auto FieldChildZ = FieldChildY->GetNext();
			GameProfile::SelectedGameProfile.defs.Property.Offset = GameProfile::SelectedGameProfile.defs.Property.ArrayDim + 0x8;
			while (!OffsetFound)
			{
				if (Read<int32_t>((byte*)FieldChildY + GameProfile::SelectedGameProfile.defs.Property.Offset) == 4 && Read<int32_t>((byte*)FieldChildZ + GameProfile::SelectedGameProfile.defs.Property.Offset) == 8)
				{
					OffsetFound = true;
				}
				if (OffsetFound == false)
				{
					GameProfile::SelectedGameProfile.defs.Property.Offset = GameProfile::SelectedGameProfile.defs.Property.Offset + 0x4;
				}
			}
			Log::Info("FProperty Offset Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.Property.Offset);
			
		}
		else
		{
			auto FieldChild = (UE4::UField*)VectorObject->GetChildren();
			while (!ArrayDimFound)
			{
				if (Read<int64_t>((byte*)FieldChild + GameProfile::SelectedGameProfile.defs.Property.ArrayDim) == 17179869185) // Array Dim and Element Size are Side By Side
				{
					ArrayDimFound = true;
				}

				if (ArrayDimFound == false)
				{
					GameProfile::SelectedGameProfile.defs.Property.ArrayDim = GameProfile::SelectedGameProfile.defs.Property.ArrayDim + 0x8;
				}
			}
			Log::Info("UProperty Array Dim Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.Property.ArrayDim);
			auto FieldChildY = FieldChild->GetNext();
			auto FieldChildZ = FieldChildY->GetNext();
			GameProfile::SelectedGameProfile.defs.Property.Offset = GameProfile::SelectedGameProfile.defs.Property.ArrayDim + 0x8;
			while (!OffsetFound)
			{
				if (Read<int32_t>((byte*)FieldChildY + GameProfile::SelectedGameProfile.defs.Property.Offset) == 4 && Read<int32_t>((byte*)FieldChildZ + GameProfile::SelectedGameProfile.defs.Property.Offset) == 8)
				{
					OffsetFound = true;
				}
				if (OffsetFound == false)
				{
					GameProfile::SelectedGameProfile.defs.Property.Offset = GameProfile::SelectedGameProfile.defs.Property.Offset + 0x4;
				}
			}
			Log::Info("UProperty Offset Def located at: 0x%p", GameProfile::SelectedGameProfile.defs.Property.Offset);
		}
		return true;
	}

	bool FindUEProperty()
	{
		Log::Info("Scanning For UEProperty");
		auto VectorObject = (UE4::UStruct*)UE4::UObject::FindObject<UE4::UObject>("ScriptStruct CoreUObject.Vector");
		
		if (!VectorObject->GetChildren()->IsA(UE4::UObject::StaticClass()))
		{
			GameProfile::SelectedGameProfile.bIsFProperty = true;
			Log::Info("UEProperty is a FProperty");
			if (FindFField())
			{
				GameProfile::SelectedGameProfile.defs.Property.ArrayDim = GameProfile::SelectedGameProfile.defs.FField.Name;
				FindUEPropertyDefs();
			}
		}
		else
		{
			GameProfile::SelectedGameProfile.bIsFProperty = false;
			Log::Info("UEProperty is a UProperty");
			GameProfile::SelectedGameProfile.defs.Property.ArrayDim = GameProfile::SelectedGameProfile.defs.UField.Next;
			FindUEPropertyDefs();
		}
		return true;
	}
};