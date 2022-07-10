#pragma once

#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

#include "CoreUObject_structs.hpp"
#include "GameInfo/GameInfo.h"
#include "Memory/mem.h"

namespace UE4
{
	//---------------------------------------------------------------------------
	//Classes
	//---------------------------------------------------------------------------
	class UObject
	{
	public:
		static FUObjectArray* GObjects;
		int32_t GetIndex() const;
		UClass* GetClass() const;
		UObject* GetOuter() const;

		static inline bool IsChunkedArray()
		{
			return GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray;
		}

		std::string GetName() const;

		std::string GetFullName() const;

		template<typename T>
		static T* FindObject(const std::string& name)
		{
			if (IsChunkedArray())
			{
				for (int i = 0; i < GObjects->GetAsChunckArray().Num(); ++i)
				{
					auto object = GObjects->GetAsChunckArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->GetFullName() == name)
					{
						return static_cast<T*>(object);
					}
				}
				return nullptr;
			}
			else
			{
				for (int i = 0; i < GObjects->GetAsTUArray().Num(); ++i)
				{
					auto object = GObjects->GetAsTUArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->GetFullName() == name)
					{
						return static_cast<T*>(object);
					}
				}
				return nullptr;
			}
		}

		template<typename T>
		static std::vector<T*> GetAllObjectsOfType(UClass* Class, bool filterDefualts)
		{
			if (IsChunkedArray())
			{
				std::vector<T*> ret;
				//auto v = T::StaticClass();
				for (int i = 0; i < GObjects->GetAsChunckArray().Num(); ++i)
				{
					auto object = GObjects->GetAsChunckArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->IsA(Class))
					{
						if (filterDefualts)
						{
							if (object->GetName().find("Default__") != std::string::npos) {
								continue;
							}
						}
						ret.push_back(static_cast<T*>(object));
					}
				}
				return ret;
			}
			else
			{
				std::vector<T*> ret;
				for (int i = 0; i < GObjects->GetAsTUArray().Num(); ++i)
				{
					auto object = GObjects->GetAsTUArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->IsA(Class))
					{
						if (filterDefualts)
						{
							if (object->GetName().find("Default__") != std::string::npos) {
								continue;
							}
						}
						ret.push_back(static_cast<T*>(object));
					}
				}
				return ret;
			}
		}

		template<typename T>
		static T* GetDefaultObjectFromArray(UClass* Class)
		{
			if (IsChunkedArray())
			{
				for (int i = 0; i < GObjects->GetAsChunckArray().Num(); ++i)
				{
					auto object = GObjects->GetAsChunckArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->IsA(Class))
					{
						if (object->GetName().find("Default__") != std::string::npos) 
						{
							return static_cast<T*>(object);
						}
					}
				}
				return nullptr;
			}
			else
			{
				for (int i = 0; i < GObjects->GetAsTUArray().Num(); ++i)
				{
					auto object = GObjects->GetAsTUArray().GetByIndex(i).Object;

					if (object == nullptr)
					{
						continue;
					}

					if (object->IsA(Class))
					{
						if (object->GetName().find("Default__") != std::string::npos) 
						{
							return static_cast<T*>(object);
						}
					}
				}
				return nullptr;
			}
		}

		static UClass* FindClass(const std::string& name)
		{
			return FindObject<UClass>(name);
		}

		bool IsA(UClass* cmp) const;

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Object");
			return ptr;
		}

		bool DoesObjectContainFunction(std::string Function);

		class UFunction* GetFunction(std::string Function);

		void ProcessEvent(class UFunction* function, void* parms);

		static UObject* StaticLoadObject(class UClass* uclass, UObject* InOuter, const wchar_t* InName, const wchar_t* Filename, unsigned int LoadFlags, void* Sandbox, bool bAllowObjectReconciliation);

		static class UObject* StaticConstructObject_Internal(class UClass* Class, class UObject* InOuter, class FName Name, unsigned int SetFlags, EInternalObjectFlags InternalSetFlags, class UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype);

		bool CallFunctionByNameWithArguments(const wchar_t* Str, void* Ar, UE4::UObject* Executor, bool bForceCallWithNonExec);

		void ExecuteUbergraph(int EntryPoint);
	};

	class UField : public UObject
	{
	public:
		UField* GetNext() const;

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Field");
			return ptr;
		}

	};

	class UStruct : public UField
	{
	public:
		UStruct* GetSuperField() const;
		UField* GetChildren() const;
		int32_t GetPropertySize() const;
		
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Struct");
			return ptr;
		}

	};

	class UClass : public UStruct
	{
	public:
		template<typename T>
		inline T* CreateDefaultObject()
		{
			if (GameProfile::SelectedGameProfile.bIsDefaultObjectArrayed == true)
			{
				return UE4::UObject::GetDefaultObjectFromArray<T>(this);
			}
			return static_cast<T*>(CreateDefaultObject());
		}

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Class");
			return ptr;
		}

		inline UObject* CreateDefaultObject()
		{

			if (GameProfile::SelectedGameProfile.bIsDefaultObjectArrayed == true)
			{
				return UE4::UObject::GetDefaultObjectFromArray<UObject>(this);
			}
			else
			{
				return reinterpret_cast<UObject * (*)(UClass*)>(this, GameProfile::SelectedGameProfile.CreateDefaultObject)(this);
			}
		}

		static UClass* LoadClassFromString(const wchar_t* InName, bool bAllowObjectReconciliation);

	};

	class UFunction : public UStruct
	{
	public:
		int32_t GetFunctionFlags() const;
		void* GetFunction() const;
		
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class CoreUObject.Function");
			return ptr;
		}

	};
	// UE4.25 AND UP
	class FField
	{
	public:
		//FName* GetClass() const;
		FField* GetNext() const;
		std::string GetName() const;
	};

	class UEProperty
	{
	public:
		FField* GetParentFProperty() { return (FField*)this; }
		UField* GetParentUProperty() { return (UField*)this; }
		int32_t GetArrayDim() const;
		//int32_t GetElementSize() const;
		int32_t GetOffset() const;
	};

	class ULevel : public UObject
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.Level");
			return ptr;
		}
	};

	class UWorld : public UObject
	{
	public:
		AActor* SpawnActor(UClass* uclass, const  FTransform* transform, const FActorSpawnParameters* params);

		static UWorld** GWorld;
		static inline UWorld* GetWorld()
		{
			return *GWorld;
		};

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.World");
			return ptr;
		}
	};

	class AActor : public UObject
	{
	public:
		// WARNING TENDS TO CRASH AND I HAVE NO FUCKING CLUE WHY
		FTransform GetTransform();

		FRotator GetActorRotation();

		FVector GetActorLocation();

		FVector GetActorScale3D();

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.Actor");
			return ptr;
		}
	};

	class APlayerController : public AActor
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.PlayerController");
			return ptr;
		}
	};

	class AGameModeBase : public AActor
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.GameModeBase");
			return ptr;
		}
	};

	class AGameMode : public AActor
	{
	public:

	};

	class AGameState : public AActor
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.GameState");
			return ptr;
		}
	};

	class UGameInstance : public UObject
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.GameInstance");
			return ptr;
		}
	};

	class APawn : public AActor
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.Pawn");
			return ptr;
		}
	};

	class ACustomClass : public UObject
	{
	public:
		static UClass* StaticClass(std::string Class)
		{
			static auto ptr = UObject::FindClass(Class);
			return ptr;
		}
	};

	class UBlueprintFunctionLibrary : public UObject
	{
	public:
		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.BlueprintFunctionLibrary");
			return ptr;
		}
	};

	class UGameplayStatics : public UBlueprintFunctionLibrary
	{
	public:

		static class AActor* BeginDeferredActorSpawnFromClass(class UClass* ActorClass, const struct FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod CollisionHandlingOverride, class AActor* Owner);

		static class FString GetCurrentLevelName(bool bRemovePrefixString);

		static class AGameState* GetGameState();
		static class AGameMode* GetGameMode();
		static class UGameInstance* GetGameInstance();
		static class APawn* GetPlayerPawn(int PlayerIndex);
		static class APlayerController* GetPlayerController(int PlayerIndex);

		static void ExecuteConsoleCommand(const class FString& Command, class APlayerController* SpecificPlayer);

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Engine.GameplayStatics");
			return ptr;
		}
	};

	static UE4::UEProperty* _dummy_foobar = nullptr;
	template<typename T>
	bool GetVariable(UE4::UObject* Object, std::string Name, T& Variable, UE4::UEProperty*& Property = _dummy_foobar)
	{
		UE4::UClass* ObjectClass = Object->GetClass();
		if (GameProfile::SelectedGameProfile.bIsFProperty)
		{
			auto Children = (UE4::FField*)ObjectClass->GetChildren();
			bool VarFound = false;
			while (!VarFound)
			{
				if (!Children)
					break;
				if (Children->GetName() == Name)
				{
					VarFound = true;
					auto varProperty = (UE4::UEProperty*)Children;
					Property = varProperty;
					Variable= Read<T>((byte*)Object + varProperty->GetOffset());
					return true;
				}
				Children = Children->GetNext();
			}
			
		}
		else
		{
			auto Children = (UE4::UField*)ObjectClass->GetChildren();
			bool VarFound = false;
			while (!VarFound)
			{
				if (!Children)
					break;
				if (Children->GetName() == Name)
				{
					VarFound = true;
					auto varProperty = (UE4::UEProperty*)Children;
					Property = varProperty;
					Variable = Read<T>((byte*)Object + varProperty->GetOffset());
					return true;
				}
				Children = Children->GetNext();
			}
		}
		return false;
	}

	template<typename T>
	bool SetVariable(UE4::UObject* Object, std::string Name, T Value)
	{
		UE4::UClass* ObjectClass = Object->GetClass();
		if (GameProfile::SelectedGameProfile.bIsFProperty)
		{
			auto Children = (UE4::FField*)ObjectClass->GetChildren();
			bool VarFound = false;
			while (!VarFound)
			{
				if (!Children)
					break;
				if (Children->GetName() == Name)
				{
					VarFound = true;
					auto varProperty = (UE4::UEProperty*)Children;
					Write<T>((byte*)Object + varProperty->GetOffset(), Value);
					return true;
				}
				Children = Children->GetNext();
			}

		}
		else
		{
			auto Children = (UE4::UField*)ObjectClass->GetChildren();
			bool VarFound = false;
			while (!VarFound)
			{
				if (!Children)
					break;
				if (Children->GetName() == Name)
				{
					VarFound = true;
					auto varProperty = (UE4::UEProperty*)Children;
					Write<T>((byte*)Object + varProperty->GetOffset(), Value);
					return true;
				}
				Children = Children->GetNext();
			}
		}
		return false;
	}

	class FOutParmRec
	{
	public:
		UEProperty* Property; //0x0000 
		void* PropAddr; //0x0008 
		FOutParmRec* NextOutParm; //0x0010 

	}; //Size=0x0018

	class FFrame
	{
	public:
		char pad_0x0000[0x10]; //0x0000
		UFunction* Node; //0x0010 
		UObject* Object; //0x0018 
		uint8_t* Code; //0x0020 
		uint8_t* Locals; //0x0028
		char pad_0x0030[0x48]; //0x0030
		FOutParmRec* OutParms; //0x0078 

		template<typename T>
		bool SetOutput(std::string OutputName, T Value)
		{
			if (GameProfile::SelectedGameProfile.bIsFProperty)
			{
				auto CurrentOutParam = OutParms;
				while (true)
				{
					if (!CurrentOutParam->Property)
					{
						break;
					}
					if (CurrentOutParam->Property->GetParentFProperty()->GetName() == OutputName)
					{
						Write<T>((byte*)CurrentOutParam->PropAddr, Value);
						return true;
					}
					CurrentOutParam = CurrentOutParam->NextOutParm;
				}
				return false;
			}
			else
			{
				auto CurrentOutParam = OutParms;
				while (true)
				{
					if (!CurrentOutParam->Property)
					{
						break;
					}
					if (CurrentOutParam->Property->GetParentUProperty()->GetName() == OutputName)
					{
						Write<T>((byte*)CurrentOutParam->PropAddr, Value);
						return true;
					}
					CurrentOutParam = CurrentOutParam->NextOutParm;
				}
				return false;
			}
		}

		template<typename T>
		T* GetInputParams() { return (T*)Locals; }
	};
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
