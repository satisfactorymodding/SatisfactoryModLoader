#pragma once
#include "UnrealString.h"

#include "FGObjectReference.h"
#include "SaveErrors.generated.h"

/**
 * Errors we want to store to disc
 */
USTRUCT()
struct FACTORYGAME_API FErrors
{
	GENERATED_BODY()

	/** All unknown objects */
	TSet<FObjectReferenceDisc> UnknownObjects;

	/** All unknown levels */
	UPROPERTY()
	TSet<FString> UnknownLevels;

	/** All unknown classes */
	UPROPERTY()
	TSet<FString> UnknownClasses;
};

struct FACTORYGAME_API FSaveErrors
{
	/**
	 * Add a class that wasn't found
	 * 
	 * @param unknownClass - the class that we tried to find but didn't
	 */
	static void AddUnknownClass( const FString& unknowClass );

	/**
	 * Add a level that wasn't found
	 *
	 * @param unknownLevel - the level that we tried to find but didn't
	 */
	static void AddUnknownLevel( const FString& unknownLevel );

	/**
	 * Add a object reference that wasn't found
	 *
	 * @param unknownReference - the reference that we tried to find but didn't
	 */
	static void AddUnknownObject( const FObjectReferenceDisc& unknownReference );

	/**
	 * Dump all save errors we got during the load
	 */
	static void DumpSaveErrors();

	/** returns true if there are any errors on disc */
	static bool IsAnyErrorsOnDisc();

	/** Get all errors that's on disc so we can process them */
	static void GetErrorsFromDisc( FErrors& out_errors );

	/** For runtime updating the errors */
	static void SetSaveErrors( const FErrors& errors, bool save );

	/** Get the directory with the save errors */
	static FString GetSaveErrorDirectory();

	/** Get the file with the save errors */
	static FString GetSaveErrorFileName();
private:
	/** Dump all errors to a file */
	static void DumpErrorsToFile();	
private:
	/** All errors */
	static FErrors Errors;
};