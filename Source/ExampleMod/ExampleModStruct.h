#pragma once
#include "GameFramework/Actor.h"
#include "ExampleModStruct.generated.h"

USTRUCT(BlueprintType)
struct EXAMPLEMOD_API FExampleModStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ExampleField;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ExampleVector;
	
	/** Function called when serializing this struct to a FArchive. */
	bool Serialize(FArchive& ar);
};

//Enable custom serialization
template<>
struct EXAMPLEMOD_API TStructOpsTypeTraits<FExampleModStruct> : public TStructOpsTypeTraitsBase2<FExampleModStruct> {
	enum {
		WithSerializer = true,
		WithCopy = true
	};
};