#include "FGTextRenderer.h"

UFGTextRenderer::UFGTextRenderer() : Super() {
	this->mSignificanceRange = 5000.0;
	this->mBaseMaterial = nullptr;
	this->mMaterialInstance = nullptr;
	this->bHasDynamicText = false;
	this->PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;
	this->PrimaryComponentTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryComponentTick.bTickEvenWhenPaused = false;
	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryComponentTick.TickInterval = 0.0;
}
void UFGTextRenderer::BeginPlay(){ Super::BeginPlay(); }
void UFGTextRenderer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){ Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
void UFGTextRenderer::UpdateText(int32 ElementID, FString Text){  }
void UFGTextRenderer::SetPlaneSize(float SizeX, float SizeY){  }
void UFGTextRenderer::GenerateOrUpdateRenderResource(){  }
void UFGTextRenderer::SetupMaterial(){  }
void UFGTextRenderer::CleanupTempData(){  }