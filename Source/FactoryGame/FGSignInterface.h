// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGSignInterface.generated.h"


UENUM( BlueprintType )
enum class EHorizontalSignTextAlignment : uint8
{
	EHSTA_Left			UMETA( DisplayName = "Left" ),
	EHSTA_Center		UMETA( DisplayName = "Center" ),
	EHSTA_Right			UMETA( DisplayName = "Right" )
};


UENUM( BlueprintType )
enum class ESignElementType : uint8
{
	ESET_Scene			UMETA( DisplayName = "Scene Component" ),
	ESET_Text			UMETA( DisplayName = "Text Input" ),
	ESET_SpriteIcon		UMETA( DisplayName = "Image")
};


USTRUCT( BlueprintType )
struct FSignElementConstraints
{
	GENERATED_BODY()
	
	FSignElementConstraints() :
		MinTranslationOffset( FVector2D( -100.f, 100.f ) ),
		MaxTranslationOffset( FVector2D( 100.f, 100.f) ),
		MinScale ( 0.1f ),
		MaxScale ( 5.f )
	{}
	
	UPROPERTY( EditDefaultsOnly, Category = "SignData" )
	FVector2D MinTranslationOffset;
	UPROPERTY( EditDefaultsOnly, Category = "SignData" )
	FVector2D MaxTranslationOffset;
	UPROPERTY( EditDefaultsOnly, Category = "SignData" )
	float MinScale;
	UPROPERTY( EditDefaultsOnly, Category = "SignData" )
	float MaxScale;

};

UCLASS(BlueprintType)
class FACTORYGAME_API UFGSignElementData : public UObject
{
	GENERATED_BODY()

public:
	UFGSignElementData()
	{
		SignElementID = 0;
		ColorIndex = 0;
		TranslationOffset = FVector2D::ZeroVector;
		Rotation = 0.f;
		Scale = 1.f;
	}
	
	UFGSignElementData( int32 uniqueID )
	{
		SignElementID = uniqueID;
		ColorIndex = 0;
		TranslationOffset = FVector2D::ZeroVector;
		Rotation = 0.f;
		Scale = 1.f;
	}

	/** unique id to identify this element by buildable signs */
	UPROPERTY( SaveGame )
	int32 SignElementID;

	/** Index pointing to a location in the FGSignSettings Color Array */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	int32 ColorIndex;

	/** Position offset from center */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	FVector2D TranslationOffset;

	/** Roll Rotation */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	float Rotation;

	/** Global uniform scale factor */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	float Scale;

};

UCLASS( BlueprintType )
class FACTORYGAME_API UFGSignTextData : public UFGSignElementData
{
	GENERATED_BODY()

public:
	UFGSignTextData() : Super()
	{
		SignText = "Sign Text";
		FontSize = 18;
		TextAlignmentHorizontal = EHorizontalSignTextAlignment::EHSTA_Center;
	}
	
	UFGSignTextData( int32 uniqueID ) : Super( uniqueID )
	{
		SignText = "Sign Text";
		FontSize = 18;
		TextAlignmentHorizontal = EHorizontalSignTextAlignment::EHSTA_Center;
	}
	
	/** Text field to be displayed on the sign */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	FString SignText;

	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	int32 FontSize;
	
	/** Text align horizontal */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	EHorizontalSignTextAlignment TextAlignmentHorizontal;

};

UCLASS( BlueprintType )
class FACTORYGAME_API UFGSignIconData : public UFGSignElementData
{
	GENERATED_BODY()

public:
	UFGSignIconData() : Super()
	{
		IconIndex = 0;
	}

	UFGSignIconData( int32 uniqueID ) : Super( uniqueID )
	{
		IconIndex = 0;
	}
	
	// Index pointing to a location in the FGSignSettings Icon array
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	int32 IconIndex;
};


USTRUCT( BlueprintType )
struct FSignData
{
	GENERATED_BODY()

	FSignData( ) :
		BackgroundColorIndex( 0 )
	{
	}

	FSignData( TArray<UFGSignElementData*> elementData, int32 backgroundColorIndex )
	{
		for( UFGSignElementData* data : elementData )
		{
			SignElementData.Add( DuplicateObject( data, nullptr ) );
		}

		BackgroundColorIndex = BackgroundColorIndex;
	}

	// Copy Constructor (no outer is specified so DuplicateObject will only perform a shallow copy)
	// This is as intended as their are not pointer references in the UFGSignElementData class
	FSignData( const FSignData& data )
	{
		for( UFGSignElementData* elementData : data.SignElementData )
		{
			SignElementData.Add( Cast<UFGSignElementData>( DuplicateObject( elementData, nullptr ) ) );
		}

		BackgroundColorIndex = BackgroundColorIndex;
	}

	template<typename ElementType>
	void GetAllElementsOfType( TArray<ElementType*>& out_Elements )
	{
		for(UFGSignElementData* elem : SignElementData )
		{
			if( Cast<ElementType>( elem ) )
			{
				out_Elements.Add( Cast<ElementType>( elem ) );
			}
		}
	}

	UFGSignElementData* GetElementWithId( int32 id, UFGSignElementData& out_elementData ) const
	{
		for( UFGSignElementData* elem : SignElementData )
		{
			if( elem->SignElementID == id )
			{
				return elem;
			}
		}

		return nullptr;
	}

	/** All sign elements in this sign */
	UPROPERTY( SaveGame, BlueprintReadOnly, Category = "SignData" )
	TArray<UFGSignElementData*> SignElementData;

	/** Index of the selected color for the background from the FGSignSettings color data array  */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	int32 BackgroundColorIndex;
};


// Sign Interface
UINTERFACE( MinimalAPI, Blueprintable )
class UFGSignInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for Sign Buildables to be able to communicate with UI
 */
class FACTORYGAME_API IFGSignInterface
{
	GENERATED_BODY()

public:
	/** Sets the sign data with optional update parameter */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	void SetSignData( const FSignData& data, bool bUpdate = true );

	/** Returns the implementing classes current sign data*/
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	FSignData GetSignData();

	/** Return a valid unique ID specifier used when adding a new sign element
	*	@note Unique is the key word there. It must be.
	*/
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	int32 GetAvailableElementID();

	/** Get the world scale dimensions (width / height) of the sign
	* @note from world space Y maps to X and Z maps to Y in the return value
	*/
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData")
	FVector2D GetSignDimensions();


};
