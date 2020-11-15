#include "ClassGenerator.h"
#include "Class.h"
#include "UObjectAllocator.h"

#pragma optimize("", off)

UClass* FClassGenerator::GenerateSimpleClass(const TCHAR* PackageName, const TCHAR* ClassName, UClass* ParentClass) {
	//Flags to assign to newly created class
	const EClassFlags ParamsClassFlags = CLASS_Native|CLASS_MatchedSerializers;

	//Code below is taken from GetPrivateStaticClassBody
	//Allocate memory from ObjectAllocator for class object and call class constructor directly
    UClass* ConstructedClassObject = (UClass*) GUObjectAllocator.AllocateUObject(sizeof(UClass), alignof(UClass), true);
    ::new (ConstructedClassObject)UClass(
        EC_StaticConstructor,
        ClassName,
        ParentClass->GetStructureSize(),
        CLASS_Intrinsic,
        CASTCLASS_None,
        UObject::StaticConfigName(),
        EObjectFlags(RF_Public | RF_Standalone | RF_Transient | RF_MarkAsNative | RF_MarkAsRootSet),
        ParentClass->ClassConstructor,
        ParentClass->ClassVTableHelperCtorCaller,
        ParentClass->ClassAddReferencedObjects);

	//Set super structure and ClassWithin (they are required prior to registering)
	FCppClassTypeInfoStatic TypeInfoStatic = {false};
	ConstructedClassObject->SetSuperStruct(ParentClass);
	ConstructedClassObject->ClassWithin = UObject::StaticClass();
	ConstructedClassObject->SetCppTypeInfoStatic(&TypeInfoStatic);

	//Register pending object, apply class flags, set static type info and link it
	ConstructedClassObject->RegisterDependencies();
	ConstructedClassObject->DeferredRegister(UClass::StaticClass(), PackageName, ClassName);

	//Mark class as Constructed and perform linking
	ConstructedClassObject->ClassFlags |= (EClassFlags)(ParamsClassFlags | CLASS_Constructed);
	ConstructedClassObject->AssembleReferenceTokenStream(true);
	ConstructedClassObject->StaticLink();

    //Make sure default class object is initialized
    ConstructedClassObject->GetDefaultObject();
    return ConstructedClassObject;
}

#pragma optimize("", on)
