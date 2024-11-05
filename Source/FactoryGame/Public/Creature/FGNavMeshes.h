// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "NavMesh/RecastNavMesh.h"

#include "FGNavMeshes.generated.h"


UCLASS()
class AFGNavMeshBase : public ARecastNavMesh
{
	GENERATED_UCLASS_BODY()
};


UCLASS()
class AFGCritterNavMesh : public AFGNavMeshBase
{
	GENERATED_UCLASS_BODY()
};

UCLASS()
class AFGDefaultNavMesh : public AFGNavMeshBase
{
	GENERATED_UCLASS_BODY()
};

UCLASS()
class AFGAlphaNavMesh : public AFGNavMeshBase
{
	GENERATED_UCLASS_BODY()
};

UCLASS()
class AFGEliteNavMesh : public AFGNavMeshBase
{
	GENERATED_UCLASS_BODY()
};

UCLASS()
class AFGGiraffeNavMesh : public AFGNavMeshBase
{
	GENERATED_UCLASS_BODY()
};

UCLASS()
class AFGTurtleNavMesh : public AFGNavMeshBase
{
	GENERATED_UCLASS_BODY()
};