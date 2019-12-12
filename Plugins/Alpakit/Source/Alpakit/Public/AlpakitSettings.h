#pragma once

#include "CoreMinimal.h"
#include "Editor/DetailCustomizations/Public/DetailCustomizations.h"
#include "Editor/PropertyEditor/Public/IDetailCustomization.h"
#include "DetailLayoutBuilder.h"
#include "AlpakitSettings.generated.h"

USTRUCT()
struct FAlpakitMod
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, config)
	FString Name;

	UPROPERTY(EditAnywhere, config)
	TArray<FString> OverwritePaths;
};

UCLASS(config = Game)
class UAlpakitSettings : public UObject
{
	GENERATED_BODY()

public:
	UAlpakitSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, config, Category = Config)
	FText SatisfactoryGamePath;
	
	UPROPERTY(EditAnywhere, config, Category = Mods)
	TArray<FAlpakitMod> Mods;
	
	UPROPERTY(EditAnywhere, config, Category = Config)
	bool StartGame;

};


#pragma once

class FAlpakitModDetails : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance()
	{
		return MakeShareable(new FAlpakitModDetails);
	}

	/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override
	{
		TSharedPtr<IPropertyHandle> SatisfactoryGamePathPropHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAlpakitSettings, SatisfactoryGamePath));
		TSharedPtr<IPropertyHandle> ModsPropHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAlpakitSettings, Mods));
		TSharedPtr<IPropertyHandle> StartGamePropHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAlpakitSettings, StartGame));
		SatisfactoryGamePathPropHandle->MarkHiddenByCustomization();
		StartGamePropHandle->MarkHiddenByCustomization();
	}
};