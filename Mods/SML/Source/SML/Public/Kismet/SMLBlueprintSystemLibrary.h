#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SMLBlueprintSystemLibrary.generated.h"

UCLASS()
class SML_API USMLBlueprintSystemLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	/** Returns true if we are running the editor */
	UFUNCTION(BlueprintPure, Category = "Utilities | Project")
	static bool IsGEditor();

	/** Returns the game of the current game project we are running */
	UFUNCTION(BlueprintPure, Category = "Utilities | Project")
	static FString GetProjectName();

	/** Returns the name of the application we are running */
	UFUNCTION(BlueprintPure, Category = "Utilities | Project")
	static FString GetAppName();

	/** Returns build branch of the project */
	UFUNCTION(BlueprintPure, Category = "Utilities | Project")
	static FString GetBuildBranch();

	/** Returns build date of the project */
	UFUNCTION(BlueprintPure, Category = "Utilities | Project")
	static FString GetBuildDate();

	/** Returns the name of the configuration we are built in */
	UFUNCTION(BlueprintPure, Category = "Utilities | Project")
	static FString GetBuildConfiguration();

	/** Returns the type of the target we are running */
	UFUNCTION(BlueprintPure, Category = "Utilities | Project")
	static FString GetBuildTargetType();
};
