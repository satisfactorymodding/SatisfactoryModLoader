// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "UObject/Interface.h"
#include "Buildables/FGBuildable.h"
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
	ESET_SpriteIcon		UMETA( DisplayName = "Image" )
};


USTRUCT( BlueprintType )
struct FACTORYGAME_API FSignElementConstraints
{
	GENERATED_BODY()

		FSignElementConstraints() :
		MinTranslationOffset( FVector2D( -100.f, 100.f ) ),
		MaxTranslationOffset( FVector2D( 100.f, 100.f ) ),
		MinScale( 0.1f ),
		MaxScale( 5.f )
	{}

	UPROPERTY( EditDefaultsOnly, Category = "SignData" )
	FVector2D MinTranslationOffset;
	UPROPERTY( EditDefaultsOnly, Category = "SignData" )
	FVector2D MaxTranslationOffset;
	UPROPERTY( EditDefaultsOnly, Category = "SignData" )
	float MinScale;
	UPROPERTY( EditDefaultsOnly, Category = "SignData" )
	float MaxScale;


public:
	FORCEINLINE ~FSignElementConstraints() = default;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSignPixelColumn
{
	GENERATED_BODY()
	
	FSignPixelColumn()
	{}
	
	FSignPixelColumn( int32 size ) 
	{
		Column.SetNum( size );
	}
	
	UPROPERTY( SaveGame )
	TArray< class UFGSignPixelData* > Column;

	class UFGSignPixelData* operator[]( int32 index )
	{
		if( Column.IsValidIndex( index ) )
		{
			return Column[ index ];
		}
		else
		{
			return nullptr;
		}
	}

public:
	FORCEINLINE ~FSignPixelColumn() = default;
};

UCLASS( BlueprintType )
class FACTORYGAME_API UFGSignLayer : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
	
public:

	UFGSignLayer()
	{
	}

	// Begin IFGSaveInterface
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	void Init( int32 layerID, FVector2D canvasDimensions, FVector2D pixelDimensions )
	{
		mLayerID = layerID;
		mPixelDimensions = pixelDimensions;
		mPixelColumns.SetNum( ( int32 )( canvasDimensions.X / pixelDimensions.X ) );
		for( int i = 0; i < ( int32 )( canvasDimensions.X / pixelDimensions.X ); ++i )
		{
			mPixelColumns[ i ] = FSignPixelColumn( ( int32 )( canvasDimensions.Y / pixelDimensions.Y ) );
		}
	}

	// Layer index, used to determine sorting. Layer 0 is the background layer
	UPROPERTY( SaveGame )
	uint8 mLayerID;

	UPROPERTY( SaveGame )
	TArray< FSignPixelColumn > mPixelColumns;

	UPROPERTY( SaveGame )
	TArray< class UFGSignElementData* > mLayerElements;

	UPROPERTY( SaveGame )
	FVector2D mPixelDimensions;


public:
	FORCEINLINE ~UFGSignLayer() = default;
};

//@todoSigns : Change all blueprint read / write properties over to getters / setters where applicable
UCLASS( BlueprintType )
class FACTORYGAME_API UFGSignElementData : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	UFGSignElementData()
	{
		mSignElementID = 0;
		mColorIndex = 0;
		mTranslationOffset = FVector2D::ZeroVector;
		mRotation = 0.f;
		mScale = 1.f;
	}

	UFGSignElementData( int32 uniqueID )
	{
		mSignElementID = uniqueID;
		mColorIndex = 0;
		mTranslationOffset = FVector2D::ZeroVector;
		mRotation = 0.f;
		mScale = 1.f;
	}

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** unique id to identify this element by buildable signs */
	UPROPERTY( SaveGame )
	int32 mSignElementID;

	/** Index pointing to a location in the FGSignSettings Color Array */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	int32 mColorIndex;

	/** Position offset from center */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	FVector2D mTranslationOffset;

	/** Roll Rotation */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	float mRotation;

	/** Global uniform scale factor */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	float mScale;

	/** If embedded, this indicates that the element should not be given its own element list widget ( tex. the background pixels in layers ) */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	bool mEmbeddedInLayer;

	UPROPERTY( BlueprintReadOnly, Category = "SignData" )
	bool mIsElementStatic;

public:
	FORCEINLINE ~UFGSignElementData() = default;
};

UCLASS( BlueprintType )
class FACTORYGAME_API UFGSignPixelData : public UFGSignElementData
{
	GENERATED_BODY()
	
public:

	UFGSignPixelData()
	{}

	UFGSignPixelData( int32 uniqueID ) : Super( uniqueID )
	{
	}
	
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	FVector2D mDimensions;


public:
	FORCEINLINE ~UFGSignPixelData() = default;
};


UCLASS( BlueprintType )
class FACTORYGAME_API UFGSignTextData : public UFGSignElementData
{
	GENERATED_BODY()

public:
	UFGSignTextData() : Super()
	{
		mSignText = "Sign Text";
		mFontSize = 24;
		mTextAlignmentHorizontal = EHorizontalSignTextAlignment::EHSTA_Center;
	}

	UFGSignTextData( int32 uniqueID ) : Super( uniqueID )
	{
		mSignText = "Sign Text";
		mFontSize = 24;
		mTextAlignmentHorizontal = EHorizontalSignTextAlignment::EHSTA_Center;
	}

	/** Text field to be displayed on the sign */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	FString mSignText;

	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	int32 mFontSize;

	/** Text align horizontal */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	EHorizontalSignTextAlignment mTextAlignmentHorizontal;


public:
	FORCEINLINE ~UFGSignTextData() = default;
};

UCLASS( BlueprintType )
class FACTORYGAME_API UFGSignIconData : public UFGSignElementData
{
	GENERATED_BODY()

public:
	UFGSignIconData() : Super()
	{
		mIconIndex = 0;
	}

	UFGSignIconData( int32 uniqueID ) : Super( uniqueID )
	{
		mIconIndex = 0;
	}

	// Index pointing to a location in the FGSignSettings Icon array
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	int32 mIconIndex;

public:
	FORCEINLINE ~UFGSignIconData() = default;
};


USTRUCT( BlueprintType )
struct FACTORYGAME_API FSignData
{
	GENERATED_BODY()

	FSignData() :
		BackgroundColorIndex( 0 )
	{
	}

	// Copy Constructor, outer is set to ensure proper save integration (thus the copy must contain a valid reference to the buildable as outer)
	FSignData( const FSignData& data );

	template<typename ElementType>
	void GetAllElementsOfType( TArray<ElementType*>& out_Elements )
	{
		for( UFGSignElementData* elem : SignElementData )
		{
			if( Cast<ElementType>( elem ) )
			{
				out_Elements.Add( Cast<ElementType>( elem ) );
			}
		}
	}

	/** First time Initialization. Should be called by owning buildable to prepare the data elements neccessary */
	void Init( class IFGSignInterface* signInterface );

	/** Function called when serializing this struct to a FArchive. */
	bool Serialize( FArchive& ar );
	friend FArchive& operator<<( FArchive& ar, FSignData& item );

	UFGSignElementData* GetElementWithId( int32 id, UFGSignElementData& out_elementData ) const;

	/** All additional layers in this sign. Each layer holds an array of all elements in that layer */
	UPROPERTY( SaveGame, BlueprintReadOnly, Category = "SignData" )
	TArray< UFGSignLayer* > SignLayers;

	/** All sign elements in this sign */
	UPROPERTY( SaveGame, BlueprintReadOnly, Category = "SignData" )
	TArray<UFGSignElementData*> SignElementData;

	/** Index of the selected color for the background from the FGSignSettings color data array  */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "SignData" )
	int32 BackgroundColorIndex;



public:
	FORCEINLINE ~FSignData() = default;
};

/** Enable custom serialization of FRailroadTrackPosition */
template<>
struct FACTORYGAME_API TStructOpsTypeTraits< FSignData > : public TStructOpsTypeTraitsBase2< FSignData >
{
	enum
	{
		WithSerializer = true
	};

public:
	FORCEINLINE ~TStructOpsTypeTraits< FSignData >() = default;
};


// Sign Interface
UINTERFACE( MinimalAPI, Blueprintable )
class UFGSignInterface : public UInterface
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGSignInterface() = default;
};

/**
 * Interface for Sign Buildables to be able to communicate with UI
 */
class FACTORYGAME_API IFGSignInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	AFGBuildable* GetBuildable();
	

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
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	FVector2D GetSignDimensions();

	/** Get the dimensions of the grid size ( the size of 1 grid square )
	*	Is used for creating "pixel" layouts on each layer
	*/
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "SignData" )
	FVector2D GetGridSquareDimensions();


public:
	FORCEINLINE IFGSignInterface() = default;
};
