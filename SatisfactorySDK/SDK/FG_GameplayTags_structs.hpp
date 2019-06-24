#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_Engine_classes.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum GameplayTags.EGameplayTagQueryExprType
enum class EGameplayTagQueryExprType : uint8_t
{
	Undefined                      = 0,
	AnyTagsMatch                   = 1,
	AllTagsMatch                   = 2,
	NoTagsMatch                    = 3,
	AnyExprMatch                   = 4,
	AllExprMatch                   = 5,
	NoExprMatch                    = 6,
	EGameplayTagQueryExprType_MAX  = 7
};


// Enum GameplayTags.EGameplayContainerMatchType
enum class EGameplayContainerMatchType : uint8_t
{
	Any                            = 0,
	All                            = 1,
	EGameplayContainerMatchType_MAX = 2
};


// Enum GameplayTags.EGameplayTagMatchType
enum class EGameplayTagMatchType : uint8_t
{
	Explicit                       = 0,
	IncludeParentTags              = 1,
	EGameplayTagMatchType_MAX      = 2
};


// Enum GameplayTags.EGameplayTagSelectionType
enum class EGameplayTagSelectionType : uint8_t
{
	None                           = 0,
	NonRestrictedOnly              = 1,
	RestrictedOnly                 = 2,
	All                            = 3,
	EGameplayTagSelectionType_MAX  = 4
};


// Enum GameplayTags.EGameplayTagSourceType
enum class EGameplayTagSourceType : uint8_t
{
	Native                         = 0,
	DefaultTagList                 = 1,
	TagList                        = 2,
	RestrictedTagList              = 3,
	DataTable                      = 4,
	Invalid                        = 5,
	EGameplayTagSourceType_MAX     = 6
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct GameplayTags.GameplayTag
// 0x0008
struct FGameplayTag
{
	struct FName                                       TagName;                                                  // 0x0000(0x0008) (Edit, ZeroConstructor, EditConst, SaveGame, IsPlainOldData)
};

// ScriptStruct GameplayTags.GameplayTagContainer
// 0x0020
struct FGameplayTagContainer
{
	TArray<struct FGameplayTag>                        GameplayTags;                                             // 0x0000(0x0010) (BlueprintVisible, ZeroConstructor, SaveGame)
	TArray<struct FGameplayTag>                        ParentTags;                                               // 0x0010(0x0010) (ZeroConstructor, Transient)
};

// ScriptStruct GameplayTags.GameplayTagQuery
// 0x0048
struct FGameplayTagQuery
{
	int                                                TokenStreamVersion;                                       // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0004(0x0004) MISSED OFFSET
	TArray<struct FGameplayTag>                        TagDictionary;                                            // 0x0008(0x0010) (ZeroConstructor)
	TArray<unsigned char>                              QueryTokenStream;                                         // 0x0018(0x0010) (ZeroConstructor)
	class FString                                      UserDescription;                                          // 0x0028(0x0010) (ZeroConstructor)
	class FString                                      AutoDescription;                                          // 0x0038(0x0010) (ZeroConstructor)
};

// ScriptStruct GameplayTags.GameplayTagSource
// 0x0020
struct FGameplayTagSource
{
	struct FName                                       SourceName;                                               // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	EGameplayTagSourceType                             SourceType;                                               // 0x0008(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0009(0x0007) MISSED OFFSET
	class UGameplayTagsList*                           SourceTagList;                                            // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
	class URestrictedGameplayTagsList*                 SourceRestrictedTagList;                                  // 0x0018(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct GameplayTags.GameplayTagTableRow
// 0x0018 (0x0020 - 0x0008)
struct FGameplayTagTableRow : public FTableRowBase
{
	struct FName                                       Tag;                                                      // 0x0008(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class FString                                      DevComment;                                               // 0x0010(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
};

// ScriptStruct GameplayTags.RestrictedGameplayTagTableRow
// 0x0008 (0x0028 - 0x0020)
struct FRestrictedGameplayTagTableRow : public FGameplayTagTableRow
{
	bool                                               bAllowNonRestrictedChildren;                              // 0x0020(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0021(0x0007) MISSED OFFSET
};

// ScriptStruct GameplayTags.GameplayTagCategoryRemap
// 0x0020
struct FGameplayTagCategoryRemap
{
	class FString                                      BaseCategory;                                             // 0x0000(0x0010) (Edit, ZeroConstructor)
	TArray<class FString>                              RemapCategories;                                          // 0x0010(0x0010) (Edit, ZeroConstructor)
};

// ScriptStruct GameplayTags.GameplayTagRedirect
// 0x0010
struct FGameplayTagRedirect
{
	struct FName                                       OldTagName;                                               // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FName                                       NewTagName;                                               // 0x0008(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct GameplayTags.RestrictedConfigInfo
// 0x0020
struct FRestrictedConfigInfo
{
	class FString                                      RestrictedConfigName;                                     // 0x0000(0x0010) (Edit, ZeroConstructor, Config)
	TArray<class FString>                              Owners;                                                   // 0x0010(0x0010) (Edit, ZeroConstructor, Config)
};

// ScriptStruct GameplayTags.GameplayTagCreationWidgetHelper
// 0x0001
struct FGameplayTagCreationWidgetHelper
{
	unsigned char                                      UnknownData00[0x1];                                       // 0x0000(0x0001) MISSED OFFSET
};

// ScriptStruct GameplayTags.GameplayTagReferenceHelper
// 0x0010
struct FGameplayTagReferenceHelper
{
	unsigned char                                      UnknownData00[0x10];                                      // 0x0000(0x0010) MISSED OFFSET
};

// ScriptStruct GameplayTags.GameplayTagNode
// 0x0050
struct FGameplayTagNode
{
	unsigned char                                      UnknownData00[0x50];                                      // 0x0000(0x0050) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
