// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FGSignPixelInstanceManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTORYGAME_API UFGSignPixelInstanceManager : public USceneComponent
{
	GENERATED_BODY()

public:	
	UFGSignPixelInstanceManager();

	struct FSignHandle
	{
	private: 
		friend UFGSignPixelInstanceManager;

		TArray< int32 > PixelHandles;
	};

protected:

	virtual void BeginPlay() override;

	FSignHandle AddPixelSign( class AFGBuildablePixelSign* pixelSign );
	void RemovePixelSign( const FSignHandle& signHandle );

private:
	friend class AFGSignSubsystem;
	friend class AFGBuildablePixelSign;

	void CreateHierarchicalInstancingComponent( UStaticMesh* staticMesh );
	void CreateInstancesForSign( class AFGBuildablePixelSign* pixelSign );
	void SetColorDataForPixelIndex( FSignHandle& signHandle, int32 pixelIndex, FLinearColor& newColor );


public:	
	UPROPERTY()
	class UHierarchicalInstancedStaticMeshComponent* mInstanceComponent;

	TSet< FSignHandle* > mSignHandles;
};
