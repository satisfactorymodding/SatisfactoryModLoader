#include "FObjectAsReferenceIndexArchive.h"

FObjectAsReferenceIndexArchive::FObjectAsReferenceIndexArchive(FArchive& InParent, bool bInAttemptToLoadIfFindFails, UPackageMap* InPackageMap): FArchiveProxy(InParent) {  }
FObjectAsReferenceIndexArchive::FObjectAsReferenceIndexArchive(FArchive& InParent, bool bInAttemptToLoadIfFindFails, const APlayerController* InPlayerController): FArchiveProxy(InParent) {  }
FArchive& FObjectAsReferenceIndexArchive::operator<<(UObject*& Value){ return FArchiveProxy::operator<<(Value); }