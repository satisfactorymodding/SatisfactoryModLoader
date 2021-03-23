

#include "Utils/EditorBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Editor Utils 

TSharedPtr<FJsonObject> UEditorBlueprintFunctionLibrary::convertUStructToJsonObjectWithName(UStruct* Struct, void* ptrToStruct, FString Name) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	obj->SetStringField("Name", Name);
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		obj->SetField(prop->GetName(), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}

TSharedPtr<FJsonObject> UEditorBlueprintFunctionLibrary::convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		obj->SetField(prop->GetName(), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}

void UEditorBlueprintFunctionLibrary::convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		FString FieldName;
		FieldName = prop->GetName();
		auto field = json->TryGetField(FieldName);
		if (!field.IsValid()) continue;
		convertJsonValueToUProperty(field, *prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct));
	}
}

void UEditorBlueprintFunctionLibrary::convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		strProp->SetPropertyValue(ptrToProp, json->AsString());
	}
	else if (auto txtProp = Cast<UTextProperty>(prop)) {
		txtProp->SetPropertyValue(ptrToProp, FText::FromString(json->AsString()));
	}
	else if (auto nameProp = Cast<UNameProperty>(prop)) {
		nameProp->SetPropertyValue(ptrToProp, *json->AsString());
	}
	else if (auto fProp = Cast<UFloatProperty>(prop)) {
		fProp->SetPropertyValue(ptrToProp, json->AsNumber());
	}
	else if (auto iProp = Cast<UIntProperty>(prop)) {
		iProp->SetPropertyValue(ptrToProp, json->AsNumber());
	}
	else if (auto bProp = Cast<UBoolProperty>(prop)) {
		bProp->SetPropertyValue(ptrToProp, json->AsBool());
	}
	else if (auto eProp = Cast<UEnumProperty>(prop)) {
		UByteProperty* ByteProp = Cast<UByteProperty>(eProp->GetUnderlyingProperty());
		if (ByteProp)
		{
			ByteProp->SetIntPropertyValue(eProp->ContainerPtrToValuePtr<void>(ptrToProp), int64(json->AsNumber()));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Enum Property failed to Cast the underlyingProperty to a ByteProperty; Property Name : "), *eProp->GetName());
		}
	}
	else if (auto aProp = Cast<UArrayProperty>(prop)) {
		FScriptArrayHelper helper(aProp, ptrToProp);
		helper.EmptyValues();
		TArray<TSharedPtr<FJsonValue>> jsonArr = json->AsArray();
		for (int i = 0; i < jsonArr.Num(); i++) {
			int64 valueIndex = helper.AddValue();
			convertJsonValueToUProperty(jsonArr[i], aProp->Inner, helper.GetRawPtr(valueIndex));
		}
	}
	else if (auto mProp = Cast<UMapProperty>(prop)) {
		TArray<TSharedPtr<FJsonValue>> jsonArr = json->AsArray();
		FScriptMapHelper MapHelper(mProp, ptrToProp);
		for (int i = 0; i < jsonArr.Num(); i++) {
			const int32 Index = MapHelper.AddDefaultValue_Invalid_NeedsRehash();
			uint8* mapPtr = MapHelper.GetPairPtr(Index);

			if (jsonArr[i]->AsObject())
			{
				// Map Property
				if (jsonArr[i]->AsObject()->HasField("key") && jsonArr[i]->AsObject()->HasField("value"))
				{
					TSharedPtr<FJsonValue> keyvalue = jsonArr[i]->AsObject()->TryGetField("key");
					TSharedPtr<FJsonValue> valuevalue = jsonArr[i]->AsObject()->TryGetField("value");
					convertJsonValueToUProperty(keyvalue, mProp->KeyProp, mapPtr);
					convertJsonValueToUProperty(valuevalue, mProp->ValueProp, mapPtr + MapHelper.MapLayout.ValueOffset);
				}
				else
				{
					// Log error
					UE_LOG(LogTemp, Error, TEXT("Expected Fields Key & Value in Jsob Object for Property of Type Map"));

				}
			}

		}
		MapHelper.Rehash();

	}
	else if (auto cProp = Cast<UClassProperty>(prop)) {
		UObject* LoadedObject = FSoftObjectPath(json->AsString()).TryLoad();
		UClass * CastResult = Cast<UClass>(LoadedObject);
		cProp->SetPropertyValue(ptrToProp, CastResult);
	}
	else if (auto uProp = Cast<UObjectProperty>(prop)) {
		UObject* uObj = FSoftObjectPath(json->AsString()).TryLoad();
		uProp->SetPropertyValue(ptrToProp, uObj);
	}
	else if (auto sProp = Cast<UStructProperty>(prop)) {
		convertJsonObjectToUStruct(json->AsObject(), sProp->Struct, ptrToProp);
	}
}

TSharedPtr<FJsonValue> UEditorBlueprintFunctionLibrary::convertUPropToJsonValue(UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(strProp->GetPropertyValue(ptrToProp)));
	}
	if (auto txtProp = Cast<UTextProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(txtProp->GetPropertyValue(ptrToProp).ToString()));
	}
	if (auto nameProp = Cast<UNameProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(nameProp->GetPropertyValue(ptrToProp).ToString()));
	}
	else if (auto fProp = Cast<UFloatProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(fProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto iProp = Cast<UIntProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(iProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto bProp = Cast<UBoolProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueBoolean(bProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto eProp = Cast<UEnumProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(eProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(ptrToProp)));
	}
	else if (auto nProp = Cast<UNumericProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(nProp->GetUnsignedIntPropertyValue(ptrToProp)));
	}
	else if (auto aProp = Cast<UArrayProperty>(prop)) {
		auto& arr = aProp->GetPropertyValue(ptrToProp);
		TArray<TSharedPtr<FJsonValue>> jsonArr;
		for (int i = 0; i < arr.Num(); i++) {
			jsonArr.Add(convertUPropToJsonValue(aProp->Inner, (void*)((size_t)arr.GetData() + i * aProp->Inner->ElementSize)));
		}
		return TSharedPtr<FJsonValue>(new FJsonValueArray(jsonArr));
	}
	else if (auto cProp = Cast<UClassProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(cProp->GetPropertyValue(ptrToProp)->GetPathName()));
	}
	else if (auto oProp = Cast<UObjectProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(oProp->GetPropertyValue(ptrToProp)->GetPathName()));
	}
	else if (auto mProp = Cast<UMapProperty>(prop)) {
		FScriptMapHelper arr(mProp, ptrToProp);
		TArray<TSharedPtr<FJsonValue>> jsonArr;
		for (int i = 0; i < arr.Num(); i++) {
			TSharedPtr<FJsonValue> key = (convertUPropToJsonValue(mProp->KeyProp, arr.GetKeyPtr(i)));
			TSharedPtr<FJsonValue> value = (convertUPropToJsonValue(mProp->ValueProp, arr.GetValuePtr(i)));
			TSharedPtr<FJsonObject> JsonObject = TSharedPtr<FJsonObject>(new FJsonObject());
			JsonObject->SetField("key", key);
			JsonObject->SetField("value", value);
			TSharedPtr<FJsonValueObject> Obj = TSharedPtr<FJsonValueObject>(new FJsonValueObject(JsonObject));
			jsonArr.Add(Obj);
		}
		return TSharedPtr<FJsonValue>(new FJsonValueArray(jsonArr));
	}
	else if (auto sProp = Cast<UStructProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueObject(convertUStructToJsonObject(sProp->Struct, ptrToProp)));
	}
	else return TSharedPtr<FJsonValue>(new FJsonValueNull());
}

void UEditorBlueprintFunctionLibrary::InternalGetStructAsJson(UStructProperty *Structure, void* StructurePtr, FString &String, FString Name)
{
	TSharedPtr<FJsonObject> JsonObject;
	if (Name != "")
		JsonObject = convertUStructToJsonObjectWithName(Structure->Struct, StructurePtr, Name);
	else
		JsonObject = convertUStructToJsonObject(Structure->Struct, StructurePtr);

	FString write;
	TSharedRef<TJsonWriter<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>> JsonWriter = TJsonWriterFactory<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>::Create(&write); //Our Writer Factory
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	String = write;
}

FString UEditorBlueprintFunctionLibrary::SanitizeJsonString(FString write, bool some, bool RemoveOthers)
{
	using namespace std;
	// {\r\n\t\"Table\":
	FString VariableName = write;
	FString replace;
	VariableName.Split("[", nullptr, &replace, ESearchCase::IgnoreCase, ESearchDir::FromStart);
	replace.Split("]", &VariableName, nullptr, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

	if (some)
	{
		replace = "[";
		VariableName.Append("]");
	}
	else
	{
		replace = "";
	}
	replace.Append(*VariableName);
	using namespace std;
	string str = TCHAR_TO_UTF8(*replace);
	int size = str.length();
	for (int j = 0; j <= size; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			if (str[i] == ' ')
			{
				str.erase(str.begin() + i);
			}
		}
	}


	return str.c_str();
}

void UEditorBlueprintFunctionLibrary::InternalInsertIntoDataTable(UDataTable * DataTable, UStructProperty * Structure, void * StructurePtr, FString RowName)
{
	FString TableDump = DataTable->GetTableAsJSON(EDataTableExportFlags::UseJsonObjectsForStructs);

	FString Out = "{\"Table\":";
	TableDump.Append("}");
	Out.Append(TableDump);
	TableDump = Out;

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(TableDump);

	FString write;
	TSharedRef<TJsonWriter<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>> JsonWriter = TJsonWriterFactory<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>::Create(&write);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TSharedPtr<FJsonObject> JsonObjectArray = MakeShareable(new FJsonObject());
		TArray<TSharedPtr<FJsonValue>> Items = JsonObject->GetArrayField("Table");

		TSharedPtr<FJsonObject> NewItem = MakeShareable(new FJsonObject());

		NewItem = convertUStructToJsonObjectWithName(Structure->Struct, StructurePtr, RowName);

		TSharedPtr<FJsonValueObject> NewJsonValue = MakeShareable(new FJsonValueObject(NewItem));

		if (!NewJsonValue.IsValid())
		{
			return;
		}

		Items.Add(NewJsonValue);
		JsonObject->SetArrayField("Table", Items);



		FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);


		FString str = SanitizeJsonString(write, true);

		//Update the DataTabe from the new Json string.
		TArray<FString> errors = DataTable->CreateTableFromJSONString(str);

		for (auto e : errors)
		{
			UE_LOG(LogTemp, Warning, TEXT("Nested Object not Valid!"));
		}

	}
}

bool UEditorBlueprintFunctionLibrary::FileIO_GetFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext)
{
	if (RootFolderFullPath.Len() < 1) return false;

	FPaths::NormalizeDirectoryName(RootFolderFullPath);

	IFileManager& FileManager = IFileManager::Get();

	if (Ext == "")
	{
		Ext = "*.*";
	}
	else
	{
		Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
	}

	FString FinalPath = RootFolderFullPath + "/" + Ext;
	FileManager.FindFiles(Files, *FinalPath, true, false);
	return true;
}

UObject * UEditorBlueprintFunctionLibrary::CreateBlueprintOfClass(UClass * Class, FString Name, FString Path)
{
	if (Path.StartsWith("C:") || Path.StartsWith("D:"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Absolute Path is not valid ! CreateBlueprintOfClass expects relative Path like '/Game/FactoryGame/Buildable/' !"));

		return nullptr;
	}
	if (!Path.EndsWith("/"))
	{
		Path.Append("/");
	}
	Path.Append(Name);
	UPackage* TargetPackage = CreatePackage(nullptr, *Path);
	EBlueprintType BlueprintType = BPTYPE_Normal;
	UBlueprint * BP = FKismetEditorUtilities::CreateBlueprint(Class, TargetPackage, *Name, BlueprintType, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
	BP->MarkPackageDirty();
	return BP;
}

TArray<UObject *> UEditorBlueprintFunctionLibrary::GetBlueprintsFromPath(FString Path, UClass * Filter)
{
	UObjectLibrary * ItemLibrary = UObjectLibrary::CreateLibrary(UObject::StaticClass(), true, GIsEditor);
	if (Path == "")
		return TArray<UObject*>();
	if (!Path.StartsWith("/"))
	{
		FString newPath = "/";
		newPath.Append(Path);
		Path = newPath;
	}

	if (Path.EndsWith("/") || Path.EndsWith("'\'"))
	{
		Path.RightChop(1);
	}

	if (Path == "/Game" || Path == "'\'Game")
	{
		UE_LOG(LogTemp, Error, TEXT("You were about to Load everything in The Project ! This could potentially take Hours and lots of Computation.. Just Dont .."));
		return TArray<UObject*>();
	}

	ItemLibrary->LoadBlueprintsFromPath(Path);
	TArray<UBlueprintGeneratedClass *> ClassesArray;
	TArray<UObject *> BPArray;

	ItemLibrary->GetObjects<UBlueprintGeneratedClass>(ClassesArray);
	for (int32 i = 0; i < ClassesArray.Num(); i++)
	{
		if (Filter)
		{
			FString PathName = ClassesArray[i]->GetPathName();
			if (!PathName.EndsWith("_C"))
			{
				PathName.Append("_C");
			}
			UClass* InnerBPClass = LoadObject<UClass>(NULL, *PathName);
			if (InnerBPClass != Filter)
			{
				if (!InnerBPClass->IsChildOf(Filter))
					continue;
			}
		}
		if (!BPArray.Contains(ClassesArray[i]->ClassGeneratedBy))
			BPArray.Add(ClassesArray[i]->ClassGeneratedBy);
	}
	return BPArray;
}

UClass * UEditorBlueprintFunctionLibrary::GetClassGeneratedByBlueprint(UObject * Blueprint)
{
	if (!Cast<UBlueprint>(Blueprint))
	{
		UE_LOG(LogTemp, Warning, TEXT("Object is not a Blueprint"));
		return nullptr;
	}
	FString PathName = Cast<UBlueprint>(Blueprint)->GetPathName();
	if (!PathName.EndsWith("_C"))
	{
		PathName.Append("_C");
	}
	UClass* InnerBPClass = LoadObject<UClass>(NULL, *PathName);
	return InnerBPClass;
}
// Editor Utils  End


// Unlocks
// Unlocks End

// Schematic 

FSchematicStruct::FSchematicStruct()
{
	Class = nullptr;
	mDisplayName = "";
	mType = ESchematicType::EST_Custom;
	mTechTier = 0;
	mSchematicCategory = nullptr;
	mSubCategories = {};
	mTimeToComplete = 180.f;
	mSchematicIcon = FSlateBrush();
	mCost = {};
	mUnlocks = {};
	mSchematicDependencies = {};
}

FSchematicStruct::FSchematicStruct(TSubclassOf<class UFGSchematic> inClass)
{
	if (!inClass)
	{
		Class = nullptr;
		mDisplayName = "";
		mType = ESchematicType::EST_Custom;
		mTechTier = 0;
		mSchematicCategory = nullptr;
		mSubCategories = {};
		mTimeToComplete = 180.f;
		mSchematicIcon = FSlateBrush();
		mCost = {};
		mUnlocks = {};
		mSchematicDependencies = {};
	}

	Class = inClass;
	mDisplayName = inClass.GetDefaultObject()->mDisplayName.ToString();
	mType = inClass.GetDefaultObject()->mType;
	mTechTier = inClass.GetDefaultObject()->mTechTier;
	mSchematicCategory = inClass.GetDefaultObject()->mSchematicCategory;
	mSubCategories = inClass.GetDefaultObject()->mSubCategories;
	mTimeToComplete = inClass.GetDefaultObject()->mTimeToComplete;
	mSchematicIcon = inClass.GetDefaultObject()->mSchematicIcon;
	mCost = inClass.GetDefaultObject()->mCost;
	mUnlocks = inClass.GetDefaultObject()->mUnlocks;
	mSchematicDependencies = inClass.GetDefaultObject()->mSchematicDependencies;

}

void UEditorBlueprintFunctionLibrary::InitSchematicPurchaseDep(UFGSchematicPurchasedDependency * selfref, TArray<TSubclassOf<class UFGSchematic>> schematics, bool requireAllSchematicsToBePurchased)
{
	selfref->Init(schematics, requireAllSchematicsToBePurchased);
}

void UEditorBlueprintFunctionLibrary::GetSchematicDependencies(TSubclassOf<UFGSchematic> inClass, UPARAM(ref)TArray<UFGAvailabilityDependency*>& out_schematicDependencies)
{
	if (inClass)
		out_schematicDependencies = inClass.GetDefaultObject()->mSchematicDependencies;
	return;
}

void UEditorBlueprintFunctionLibrary::SetSchematicFromStruct(FSchematicStruct Struct)
{
	if (!Struct.Class)
		return;
	if (Struct == FSchematicStruct())
		return;
	if (Struct == Struct.Class)
		return;

	auto obj = Struct.Class.GetDefaultObject();

	obj->mDisplayName = FText::FromString(Struct.mDisplayName);
	obj->mType = Struct.mType;
	obj->mTechTier = Struct.mTechTier;
	obj->mSchematicCategory = Struct.mSchematicCategory;
	obj->mSubCategories = Struct.mSubCategories;
	obj->mTimeToComplete = Struct.mTimeToComplete;
	obj->mSchematicIcon = Struct.mSchematicIcon;
	obj->mCost = Struct.mCost;
	obj->mUnlocks = Struct.mUnlocks;
	obj->mSchematicDependencies = Struct.mSchematicDependencies;

	Struct.Class->MarkPackageDirty();
}

KISMET_MATH_FORCEINLINE
bool UEditorBlueprintFunctionLibrary::EqualEqual_FSchematicStructFSchematicStruct(FSchematicStruct A, FSchematicStruct B)
{
	return A == B;
}
KISMET_MATH_FORCEINLINE
bool UEditorBlueprintFunctionLibrary::EqualEqual_FSchematicStructUFGSchematic(FSchematicStruct A, TSubclassOf<class UFGSchematic> B)
{
	return A == B;
}

// Schemati End


// Recipes

FRecipeStruct::FRecipeStruct()
{
	Class = nullptr;
	Name = "";
	Ingredients = {};
	Products = {};
	ManufactoringDuration = 0.f;
	ManualManufacturingMultiplier = 0.f;
	mProducedIn = {};
}

FRecipeStruct::FRecipeStruct(TSubclassOf<class UFGRecipe> inClass)
{
	if (!inClass)
		return;
	Class = inClass;
	Name = inClass.GetDefaultObject()->mDisplayName.ToString();
	Ingredients = inClass.GetDefaultObject()->mIngredients;
	Products = inClass.GetDefaultObject()->mProduct;
	ManufactoringDuration = inClass.GetDefaultObject()->mManufactoringDuration;
	ManualManufacturingMultiplier = inClass.GetDefaultObject()->mManualManufacturingMultiplier;
	mProducedIn = inClass.GetDefaultObject()->mProducedIn;
}

TArray<TSoftClassPtr<UObject>> UEditorBlueprintFunctionLibrary::GetSoftClassFromObjects(TArray<UObject*>  In)
{
	TArray< TSoftClassPtr< UObject > > out;
	if (In.Num() > 0)
	{
		for (int j = 0; j < In.Num(); j++)
		{
			if (In[j]->IsValidLowLevel())
			{
				TSoftClassPtr< UObject >obj(In[j]->GetClass());
				out.Add(obj);
			}
		}
		return out;
	}
	else
		return TArray< TSoftClassPtr< UObject > >();
}

TArray<TSoftClassPtr<UObject>> UEditorBlueprintFunctionLibrary::GetSoftClass(TArray<UClass*>  In)
{
	TArray< TSoftClassPtr< UObject > > out;
	if (In.Num() > 0)
	{
		for (int j = 0; j < In.Num(); j++)
		{
			if (In[j]->IsValidLowLevel())
			{
				TSoftClassPtr< UObject >obj(In[j]);
				out.Add(obj);
			}
		}
		return out;
	}
	else
		return TArray< TSoftClassPtr< UObject > >();

}

TArray<UClass*> UEditorBlueprintFunctionLibrary::GetClassFromSoftPtr(TArray<TSoftClassPtr<UObject>>   In)
{
	TArray<UClass*>  out;
	if (In.Num() > 0)
	{
		for (int j = 0; j < In.Num(); j++)
		{
			if (In[j]->IsValidLowLevel())
			{
				UClass* obj = In[j].Get();
				out.Add(obj);
			}
		}
		return out;
	}
	else
		return TArray<UClass*>();
}

void UEditorBlueprintFunctionLibrary::SetRecipeFromStruct(TSubclassOf<UFGRecipe> inClass, FRecipeStruct Struct)
{
	if (!inClass)
		return;
	if (Struct == FRecipeStruct())
		return;
	if (Struct == inClass)
		return;

	inClass.GetDefaultObject()->mDisplayName = FText::FromString(Struct.Name);
	inClass.GetDefaultObject()->mIngredients = Struct.Ingredients;
	inClass.GetDefaultObject()->mProduct = Struct.Products;
	inClass.GetDefaultObject()->mManufactoringDuration = Struct.ManufactoringDuration;
	inClass.GetDefaultObject()->mManualManufacturingMultiplier = Struct.ManualManufacturingMultiplier;
	inClass.GetDefaultObject()->mProducedIn = Struct.mProducedIn;
	inClass->MarkPackageDirty();

}

KISMET_MATH_FORCEINLINE
bool UEditorBlueprintFunctionLibrary::EqualEqual_FRecipeStructFRecipeStruct(FRecipeStruct A, FRecipeStruct B)
{
	return A == B;
}

KISMET_MATH_FORCEINLINE
bool UEditorBlueprintFunctionLibrary::EqualEqual_FRecipeStructUFGRecipe(FRecipeStruct A, TSubclassOf<class UFGRecipe> B)
{
	return A == B;
}


// Recipes End


// Descriptor



FItemDescriptorStruct::FItemDescriptorStruct()
{
	Class = nullptr;
	Name = "";
	Form = EResourceForm::RF_INVALID;
	StackSize = EStackSize::SS_ONE;
	RememberPickUp = false;
	CanBeDiscarded = true;
	EnergyValue = 0.f;
	RadioactiveDecay = 0.f;
	FluidColor = FColor();
	Category = nullptr;
	IconSmall = nullptr;
	IconBig = nullptr;
}

FItemDescriptorStruct::FItemDescriptorStruct(TSubclassOf<class UFGItemDescriptor> inClass)
{
	if (!inClass)
	{
		Class = nullptr;
		Name = "";
		Form = EResourceForm::RF_INVALID;
		StackSize = EStackSize::SS_ONE;
		RememberPickUp = false;
		CanBeDiscarded = true;
		EnergyValue = 0.f;
		RadioactiveDecay = 0.f;
		FluidColor = FColor();
		Category = nullptr;
		IconSmall = nullptr;
		IconBig = nullptr;
		return;
	}


	Class = inClass;
	Name = inClass.GetDefaultObject()->mDisplayName.ToString();
	Form = inClass.GetDefaultObject()->mForm;
	StackSize = inClass.GetDefaultObject()->mStackSize;
	RememberPickUp = inClass.GetDefaultObject()->mRememberPickUp;
	CanBeDiscarded = inClass.GetDefaultObject()->mCanBeDiscarded;
	EnergyValue = inClass.GetDefaultObject()->mEnergyValue;
	RadioactiveDecay = inClass.GetDefaultObject()->mRadioactiveDecay;
	FluidColor = inClass.GetDefaultObject()->mFluidColor;
	Category = inClass.GetDefaultObject()->mItemCategory;
	IconSmall = inClass.GetDefaultObject()->mSmallIcon;
	IconBig = inClass.GetDefaultObject()->mPersistentBigIcon;
}

void UEditorBlueprintFunctionLibrary::SetDescriptorFromStruct(TSubclassOf<UFGItemDescriptor> inClass, FItemDescriptorStruct Struct)
{
	if (!inClass)
		return;
	if (FItemDescriptorStruct() == Struct)
		return;
	if (Struct == inClass)
		return;

	inClass.GetDefaultObject()->mDisplayName = FText::FromString(Struct.Name);
	inClass.GetDefaultObject()->mForm = Struct.Form;
	inClass.GetDefaultObject()->mStackSize = Struct.StackSize;
	inClass.GetDefaultObject()->mRememberPickUp = Struct.RememberPickUp;
	inClass.GetDefaultObject()->mCanBeDiscarded = Struct.CanBeDiscarded;
	inClass.GetDefaultObject()->mEnergyValue = Struct.EnergyValue;
	inClass.GetDefaultObject()->mRadioactiveDecay = Struct.RadioactiveDecay;
	inClass.GetDefaultObject()->mFluidColor = Struct.FluidColor;
	inClass.GetDefaultObject()->mItemCategory = Struct.Category;
	inClass.GetDefaultObject()->mSmallIcon = Struct.IconSmall;
	inClass.GetDefaultObject()->mPersistentBigIcon = Struct.IconBig;

	inClass->MarkPackageDirty();

}

KISMET_MATH_FORCEINLINE
bool UEditorBlueprintFunctionLibrary::EqualEqual_FDescriptorStructFDescriptorStruct(FItemDescriptorStruct A, FItemDescriptorStruct B)
{
	return A == B;
}

KISMET_MATH_FORCEINLINE
bool UEditorBlueprintFunctionLibrary::EqualEqual_FDescriptorStructUFGItemDescriptor(FItemDescriptorStruct A, TSubclassOf<class UFGItemDescriptor> B)
{
	return A == B;
}


// Descriptor End

void UEditorBlueprintFunctionLibrary::CalculateRoadPosition(FVector2D Start, FVector2D End, float Thickness, FVector2D & CanvasStart, FVector2D & Size, float & RenderAngle, float & InvertedRenderAngle)
{
	FVector From = FVector(Start.X, Start.Y, 0.f);
	FVector To = FVector(End.X, End.Y, 0.f);

	FRotator direction = UKismetMathLibrary::FindLookAtRotation(From, To);

	RenderAngle = direction.Yaw;
	float distance = FVector2D::Distance(Start, End);
	Size = FVector2D(FMath::Clamp(distance, Thickness / 2, 1000.f), Thickness);
	CanvasStart = FVector2D(((Start.X + End.X) / 2) - (distance / 2), ((Start.Y + End.Y) / 2));
	InvertedRenderAngle = direction.GetInverse().Yaw;
	return;
}
