// This file has been automatically generated by the Unreal Header Implementation tool

#include "BlueprintObjectReaderFName.h"

FBlueprintObjectReaderFName::FBlueprintObjectReaderFName(UObject* Obj, TArray<uint8>& InBytes, int32 saveVersion,  UWorld* world, FPackageFileVersion version) : FObjectReader(Obj, InBytes) { }
FBlueprintObjectReaderFName& FBlueprintObjectReaderFName::operator<<( UObject*& Res){ return *(this); }
FArchive& FBlueprintObjectReaderFName::operator<<( FName& N){ return *(new FArchive); }
FArchive& FBlueprintObjectReaderFName::operator<<(FObjectPtr& Res){ return *(new FArchive); }
