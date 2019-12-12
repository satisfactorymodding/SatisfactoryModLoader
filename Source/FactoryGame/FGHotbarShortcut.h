#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "Styling/SlateBrush.h"
#include "FGHotbarShortcut.generated.h"

UCLASS(abstract,Blueprintable)
class UFGHotbarShortcut : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override{ return true; }

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent,Category="Shortcut")
	void Execute( class AFGPlayerController* owner );

	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Shortcut" )
	bool IsValidShortcut( class AFGPlayerController* owner ) const;

	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Shortcut" )
	UTexture2D* GetDisplayImage() const;

	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Shortcut" )
	bool IsActive( class AFGPlayerController* owner ) const;
protected:
	/** Get the buildgun from a controller */
	class AFGBuildGun* GetBuildGun( class AFGPlayerController* playerController ) const;

	/** Get a valid player that can use the shortcut, will be null if it's not allowed for some reason */
	class AFGCharacterPlayer* GetValidPlayerCharacter( class AFGPlayerController* playerController ) const;
};