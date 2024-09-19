#include "Utils/EditorBlueprintFunctionLibrary.h"
#include "Engine/ObjectLibrary.h"
#include "Kismet2/KismetEditorUtilities.h"

UObject * UEditorBlueprintFunctionLibrary::CreateBlueprintOfClass(UClass * Class, FString Name, FString Path) {
	if (Path.StartsWith("C:") || Path.StartsWith("D:")){
		UE_LOG(LogTemp, Warning, TEXT("Absolute Path is not valid! CreateBlueprintOfClass expects relative path like '/Game/FactoryGame/Buildable/'"));
		return nullptr;
	}
	if (!Path.EndsWith("/")){
		Path.Append("/");
	}
	Path.Append(Name);
	UPackage* TargetPackage = CreatePackage(*Path);
	EBlueprintType BlueprintType = BPTYPE_Normal;
	UBlueprint * BP = FKismetEditorUtilities::CreateBlueprint(Class, TargetPackage, *Name, BlueprintType, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
	BP->MarkPackageDirty();
	return BP;
}

TArray<UObject *> UEditorBlueprintFunctionLibrary::GetBlueprintsFromPath(FString Path, UClass * Filter) {
	UObjectLibrary * ItemLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, GIsEditor);
	if (Path == "")
		return TArray<UObject*>();
	if (!Path.StartsWith("/")) {
		FString NewPath = "/";
		NewPath.Append(Path);
		Path = NewPath;
	}

	if (Path.EndsWith("/") || Path.EndsWith("'\'")) {
		Path = Path.RightChop(1);
	}

	if (Path == "/Game" || Path == "'\'Game") {
		UE_LOG(LogTemp, Error, TEXT("You were about to load everything in the project! This could potentially take hours and lots of Computation... Returning nothing instead."));
		return TArray<UObject*>();
	}

	ItemLibrary->LoadBlueprintsFromPath(Path);
	TArray<UBlueprintGeneratedClass *> ClassesArray;
	TArray<UObject *> BPArray;

	ItemLibrary->GetObjects<UBlueprintGeneratedClass>(ClassesArray);
	for (int32 i = 0; i < ClassesArray.Num(); i++) {
		if (Filter){
			FString PathName = ClassesArray[i]->GetPathName();
			
			if (!PathName.EndsWith("_C"))
				PathName.Append("_C");
			
			UClass* InnerBPClass = LoadObject<UClass>(NULL, *PathName);
			
			if (InnerBPClass != Filter)
				if (!InnerBPClass->IsChildOf(Filter))
					continue;
		}
		if (!BPArray.Contains(ClassesArray[i]->ClassGeneratedBy))
			BPArray.Add(ClassesArray[i]->ClassGeneratedBy);
	}
	return BPArray;
}

UClass * UEditorBlueprintFunctionLibrary::GetClassGeneratedByBlueprint(UObject * Blueprint)
{
	if (!Cast<UBlueprint>(Blueprint)){
		UE_LOG(LogTemp, Warning, TEXT("Object is not a Blueprint"));
		return nullptr;
	}
	FString PathName = Cast<UBlueprint>(Blueprint)->GetPathName();
	if (!PathName.EndsWith("_C")){
		PathName.Append("_C");
	}
	UClass* InnerBPClass = LoadObject<UClass>(NULL, *PathName);
	return InnerBPClass;
}

void UEditorBlueprintFunctionLibrary::Editor_MarkDefaultDirty(UClass* Class)
{
	if (IsValid(Class))
	{
		Class->MarkPackageDirty();
		Class->GetDefaultObject()->MarkPackageDirty();
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("Tried to mark an invalid Class as Dirty!"));
}
