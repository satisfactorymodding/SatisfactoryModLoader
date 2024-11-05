// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/StructOnScope.h"
#include "FGDynamicStruct.generated.h"

class FStructOnScope;
/**
 * Dynamic struct is a container struct that can contain other struct value inside of it with
 * a dynamic type that depends on the particular instance of FGDynamicStruct
 * Reflection visible and blueprint visible so it can be passed around a lot of code paths without any problems
 */
USTRUCT( BlueprintType, meta = (HasNativeMake = "/Script/FactoryGame.FGBlueprintFunctionLibrary.MakeDynamicStruct", HasNativeBreak = "/Script/FactoryGame.FGBlueprintFunctionLibrary.BreakDynamicStruct") )
struct FACTORYGAME_API FFGDynamicStruct
{
	GENERATED_BODY()
private:
	TObjectPtr<UScriptStruct> ScriptStruct;
	void* StructInstance;
public:
	// Constructor and assignment operator overrides
	FFGDynamicStruct();
	FFGDynamicStruct( const FFGDynamicStruct& other );
	FFGDynamicStruct( FFGDynamicStruct&& other ) noexcept;
	~FFGDynamicStruct();

	// Convenience constructor to construct from a struct type
	template<typename T>
	FORCEINLINE explicit FFGDynamicStruct( const T& inStruct ) : FFGDynamicStruct()
	{
		InitializeAs( inStruct );
	}

	FFGDynamicStruct& operator=( const FFGDynamicStruct& other );
	FFGDynamicStruct& operator=( FFGDynamicStruct&& other ) noexcept;
public:
	// Actual data accessor functions
	void InitializeAsRaw(UScriptStruct* inStruct, const void* inStructData = nullptr );
	void Destroy();
	
	template<typename T>
	FORCEINLINE void InitializeAs(const T& inStructValue)
	{
		UScriptStruct* structType = T::StaticStruct();
		InitializeAsRaw( structType, &inStructValue );
	}
	
	FORCEINLINE UScriptStruct* GetStruct() const { return ScriptStruct; }
	FORCEINLINE const void* GetStructValueRaw() const { return StructInstance; }
	FORCEINLINE void* GetStructValueRaw() { return StructInstance; }
	
	FORCEINLINE bool IsValid() const { return ScriptStruct != nullptr && StructInstance != nullptr; }

	/** Converts the underlying struct to the string, using the UScriptStruct::ExportText */
	FString ToString() const;
	/** @return true if two structs are identical. Identity is defined by the underlying struct type, and requires both structs to have the same underlying type. */
	bool Identical( const FFGDynamicStruct& otherStruct, uint32 portFlags = PPF_None ) const;
	
	/**
	 * Attempts to retrieve the value of the struct as the provided type
	* Keep in mind that it will work for subtypes as well, so if you do something like
	 * *Struct->GetValuePtr() = FMyStruct(), it might result in unintended struct slicing!
	 */
	template<typename T>
	FORCEINLINE T* GetValuePtr()
	{
		const UScriptStruct* expectedStruct = T::StaticStruct();
		const UScriptStruct* currentStruct = GetStruct();
		if ( currentStruct != nullptr && currentStruct->IsChildOf( expectedStruct ) )
		{
			return static_cast<T*>(GetStructValueRaw());
		}
		return nullptr;
	}

	/**
	 * Attempts to retrieve the value of the struct as the provided type
	 * Keep in mind that it will work for subtypes as well, so if you do something like
	 * *Struct->GetValuePtr() = FMyStruct(), it might result in unintended struct slicing!
	 */
	template<typename T>
	FORCEINLINE const T* GetValuePtr() const
	{
		const UScriptStruct* expectedStruct = T::StaticStruct();
		const UScriptStruct* currentStruct = GetStruct();
		if ( currentStruct != nullptr && currentStruct->IsChildOf( expectedStruct ) )
		{
			return static_cast<const T*>(GetStructValueRaw());
		}
		return nullptr;
	}

	/** Same as GetValuePtr(), but asserts if the struct value is not valid */
	template<typename T>
	FORCEINLINE const T& GetValueChecked() const
	{
		const UScriptStruct* expectedStruct = T::StaticStruct();
		const T* structValue = GetValuePtr<T>();
		checkf( structValue != nullptr, TEXT("Cast of DynamicStruct %s to Struct %s failed"), *GetStruct()->GetPathName(), *expectedStruct->GetPathName() );
		return *structValue;
	}

	/** Same as GetValuePtr(), but asserts if the struct value is not valid */
	template<typename T>
	FORCEINLINE T& GetValueChecked()
	{
		const UScriptStruct* expectedStruct = T::StaticStruct();
		T* structValue = GetValuePtr<T>();
		checkf( structValue != nullptr, TEXT("Cast of DynamicStruct %s to Struct %s failed"), *GetStruct()->GetPathName(), *expectedStruct->GetPathName() );
		return *structValue;
	}

	/** Attempts to retrieve the value of the struct as the provided type, otherwise returns the default */
	template<typename T>
	FORCEINLINE T GetValueOrDefault() const
	{
		const T* currentValuePtr = GetValuePtr<T>();
		if ( currentValuePtr )
		{
			return *currentValuePtr;
		}
		return T{};
	}

	void AddStructReferencedObjects(class FReferenceCollector& Collector);
	bool Serialize(FArchive& Ar);

	friend FArchive& operator<<( FArchive& Ar, FFGDynamicStruct& DynamicStruct )
	{
		DynamicStruct.Serialize( Ar );
		return Ar;
	}
};

template<>
struct TStructOpsTypeTraits<FFGDynamicStruct> : TStructOpsTypeTraitsBase2<FFGDynamicStruct>
{
	enum
	{
		WithCopy = true,
		WithAddStructReferencedObjects = true,
		WithSerializer = true,
	};
};
