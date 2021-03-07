#pragma once
#include "UObject/Object.h"
#include "ObjectMetadata.generated.h"

UCLASS()
class UObjectMetadata : public UObject {
    GENERATED_BODY()
private:
    UPROPERTY()
    TMap<FString, UObject*> Subobjects;
    UPROPERTY()
    TArray<UObject*> StoredSubobjects;
public:
    template<typename T>
    T* GetOrCreateSubObject(const FString& Name) {
        UObject** Result = Subobjects.Find(Name);
        if (Result == NULL) {
            T* NewlyConstructedObject = NewObject<T>(this);
            Subobjects.Add(Name, NewlyConstructedObject);
            StoredSubobjects.Add(NewlyConstructedObject);
            return NewlyConstructedObject;
        }
        return Cast<T>(*Result);
    }
};
