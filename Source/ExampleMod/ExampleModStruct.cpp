#include "ExampleModStruct.h"

bool FExampleModStruct::Serialize(FArchive& Ar) {
	Ar << ExampleField;
	Ar << ExampleVector;
	UE_LOG(LogTemp, Warning, TEXT("FExampleModStruct::Serialize called!"));
	return true;
}
