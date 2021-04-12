#pragma once
#include "CoreMinimal.h"

/**
 * Used to generate UClasses inheriting other classes in runtime
 * It can be used for generating recipes, items, or schematics in runtime
 * Since Satisfactory handles these as default objects of class types, separate class for type is required
 * You can use it for other purposes, or look at implementation and try to
 * generate something moore advanced though
 */
class SML_API FClassGenerator {
public:
    /**
     * Generates UClass object inheriting passed parent class with specified name inside specified package
     * It will create package if it does not exist
     * Make sure that you only call it once with same parameters, because it won't check for that
     * Generated class will have layout completely equal to it's parent, without any new functions/properties
     * Customize it by accessing it's ClassDefaultObject
     */
    static UClass* GenerateSimpleClass(const TCHAR* PackageName, const TCHAR* ClassName, UClass* ParentClass);
};
