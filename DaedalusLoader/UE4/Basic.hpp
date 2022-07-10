#pragma once

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
	#pragma warning( disable : 4200 )
#endif

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>
#include <windows.h>
#include "GameInfo/GameInfo.h"
#include "Utilities/Logger.h"
#include "Memory/mem.h"

namespace UE4
{
template<class T>
class TArray
{
	friend class FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	void Add(T InputData)
	{
		Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
		Data[Count++] = InputData;
		Max = Count;
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}

public:
	T* Data;
	int Count;
	int Max;
};

class UObject;

class FUObjectItem
{
public:
	UObject* Object;
	int Flags;
	int ClusterRootIndex;
	int SerialNumber;
};

class TUObjectArray
{
public:
	inline int Num() const
	{
		return NumElements;
	}

	inline FUObjectItem const& GetByIndex(int Index) const
	{
		return Objects[Index];
	}

	FUObjectItem * Objects;
	int MaxElements;
	int NumElements;
};

class FChunkedFixedUObjectArray
{
public:
	inline int Num() const
	{
		return NumElements;
	}

	inline FUObjectItem const* GetObjectPtr(int Index) const
	{
		auto ElementsPerChunk = MaxElements / MaxChunks;
		auto ChunkIndex = Index / ElementsPerChunk;
		auto WithinChunkIndex = Index % ElementsPerChunk;
		auto Chunk = Objects[ChunkIndex];
		return Chunk + WithinChunkIndex;
	}

	inline FUObjectItem const& GetByIndex(int Index) const
	{
		return *GetObjectPtr(Index);
	}

private:
	FUObjectItem** Objects;
	FUObjectItem* PreAllocatedObjects;
	int MaxElements;
	int NumElements;
	int MaxChunks;
	int NumChunks;
};

class FUObjectArray
{
public:
	int ObjFirstGCIndex;
	int ObjLastNonGCIndex;
	int MaxObjectsNotConsideredByGC;
	bool OpenForDisregardForGC;
	DWORD ObjObjects;

	inline TUObjectArray GetAsTUArray() const
	{
		return (TUObjectArray&)ObjObjects;
	}

	inline FChunkedFixedUObjectArray GetAsChunckArray() const
	{
		return (FChunkedFixedUObjectArray&)ObjObjects;
	}
};
//FNAMEPOOL STUFF
class FNamePoolFNameEntry
{
public:
	int16_t Key;

	union
	{
		char AnsiName[1024];
		wchar_t WideName[1024];
	};

	uint32_t GetLength() const
	{
		return Key >> 6;
	}

	bool IsWide() const
	{
		return Key & 1;
	}
	std::string GetAnsiName() const
	{
		auto len = GetLength();
		if (len > 1024) return "[Error: Overflow]";
		return std::string((const char*)AnsiName, len);
	}
	std::wstring GetWideName() const
	{
		auto len = GetLength();
		return std::wstring((const wchar_t*)WideName, len);
	}

	std::string GetName() const
	{
		return GetAnsiName();
	}
};

class FNamePoolFNameEntryAllocator
{
private:
	char frwLock[0x8];
public:
	int32_t CurrentBlock;
	int32_t CurrentByteCursor;
	uint8_t* Blocks[8192];

	int32_t NumBlocks() const
	{
		return CurrentBlock + 1;
	}

	FNamePoolFNameEntry* GetById(int32_t key) const
	{
		uint32_t block = key >> 16;
		uint16_t offset = (uint16_t)key;

		if (!IsValidIndex(key, block, offset))
			return reinterpret_cast<FNamePoolFNameEntry*>(Blocks[0] + 0); // "None"

		return reinterpret_cast<FNamePoolFNameEntry*>(Blocks[block] + (offset * 2));
	}

	bool IsValidIndex(int32_t key) const
	{
		uint32_t block = key >> 16;
		uint16_t offset = key;
		return IsValidIndex(key, block, offset);
	}

	bool IsValidIndex(int32_t key, uint32_t block, uint16_t offset) const
	{
		return (key >= 0 && block < NumBlocks() && offset * 2 < 0x1FFFE);
	}
};

class FNamePool
{
public:
	FNamePoolFNameEntryAllocator Allocator;
	uint32_t AnsiCount;
	uint32_t WideCount;

	FNamePoolFNameEntry* GetNext(uint32_t& lastFNameId)
	{
		// Key		=> NameID
		// Value	=> StringLen
		static std::unordered_map<int, int> namesCache;
		const auto initLastFNameId = lastFNameId;
	RePlay:
		uint16_t block = lastFNameId >> 16;
		uint16_t nameOffset = (uint16_t)lastFNameId;
		uint32_t newOffset = 0;

		// We hit last Name in last Block
		if (block > Allocator.CurrentBlock)
			return nullptr;

		// If found lastId then add 2 to calc offset correct
		auto it = namesCache.find(lastFNameId);
		if (it != namesCache.end())
			newOffset += (nameOffset * 2) + 2 + it->second;

		if (newOffset >= 65535 * 2 || block == Allocator.CurrentBlock && newOffset >= Allocator.CurrentByteCursor)
		{
			lastFNameId = MAKELONG(0, block + 1);
			goto RePlay;
		}

		lastFNameId = MAKELONG(((unsigned short)(newOffset / 2)), block);

		uintptr_t entryOffset = reinterpret_cast<uintptr_t>(Allocator.Blocks[block]) + newOffset;

		unsigned short nameEntry = *reinterpret_cast<unsigned short*>(entryOffset);

		int nameLength = nameEntry >> 6;

		// if odd number (odd numbers are aligned with 0x00)
		if (nameLength % 2 != 0)
			nameLength += 1;

		// Cache
		namesCache.emplace(lastFNameId, nameLength);

		return Allocator.GetById(lastFNameId);
	}

	inline size_t Num() const
	{
		return AnsiCount;
	}

	inline bool IsValidIndex(int32_t id) const
	{
		return Allocator.IsValidIndex(static_cast<int32_t>(id));
	}

	inline FNamePoolFNameEntry* GetById(int32_t key) const
	{
		return Allocator.GetById(key);
	}

	inline FNamePoolFNameEntry* operator[](int32_t id) const
	{
		return Allocator.GetById(static_cast<int32_t>(id));
	}
};

class FNameEntry
{
public:
	inline const char* GetAnsiName() const
	{
		return (char*)this + (GameProfile::SelectedGameProfile.IsUsing4_22 ? 0xC : 0x10);
	}
};

class TNameEntryArray
{
public:
	inline int Num() const
	{
		return GetNumElements();
	}

	inline bool IsValidIndex(int Index) const
	{
		return Index < Num() && Index >= 0;
	}

	inline FNameEntry const* const& operator[](int Index) const
	{
		return *GetItemPtr(Index);
	}

private:
	inline FNameEntry const* const* GetItemPtr(int Index) const
	{
		auto ChunkIndex = Index / 16384;
		auto WithinChunkIndex = Index % 16384;
		auto Chunk = Chunks[ChunkIndex];
		return Chunk + WithinChunkIndex;
	}
	int GetNumElements() const { return Read<int>((byte*)this + 0x8 + 0x4); };
	FNameEntry** Chunks[];
};

class FName
{
public:
	int ComparisonIndex;
	int Number;

	inline FName()
		: ComparisonIndex(0),
		  Number(0)
	{
	};

	inline FName(int i)
		: ComparisonIndex(i),
		  Number(0)
	{
	};

	FName(const char* nameToFind)
		: ComparisonIndex(0),
		  Number(0)
	{
		static std::unordered_set<int> cache;

		for (auto i : cache)
		{
			if (IsUsingNamePool())
			{
				if (!std::strcmp(GetFNamePool()[i]->GetAnsiName().c_str(), nameToFind))
				{
					ComparisonIndex = i;

					return;
				}
			}
			else
			{
				if (!std::strcmp(GetTNameArray()[i]->GetAnsiName(), nameToFind))
				{
					ComparisonIndex = i;

					return;
				}
			}
		}

		if (IsUsingNamePool())
		{
			for (auto i = 0; i < GetFNamePool().Num(); ++i)
			{
				if (GetFNamePool()[i] != nullptr)
				{
					if (!std::strcmp(GetFNamePool()[i]->GetAnsiName().c_str(), nameToFind))
					{
						cache.insert(i);

						ComparisonIndex = i;

						return;
					}
				}
			}
		}
		else
		{
			for (auto i = 0; i < GetTNameArray().Num(); ++i)
			{
				if (GetTNameArray()[i] != nullptr)
				{
					if (!std::strcmp(GetTNameArray()[i]->GetAnsiName(), nameToFind))
					{
						cache.insert(i);

						ComparisonIndex = i;

						return;
					}
				}
			}
		}
		
	};

	static DWORD*GNames;
	static inline DWORD& GetGlobalNames()
	{
		return *GNames;
	};

	static inline bool IsUsingNamePool()
	{
		return GameProfile::SelectedGameProfile.UsesFNamePool;
	};

	static inline TNameEntryArray& GetTNameArray()
	{
		return *(TNameEntryArray*)GNames;
	};

	static inline FNamePool& GetFNamePool()
	{
		return *(FNamePool*)GNames;
	};

	inline std::string GetName() const
	{
		if (IsUsingNamePool())
		{
			return GetFNamePool()[ComparisonIndex]->GetAnsiName();
		}
		else
		{
			return GetTNameArray()[ComparisonIndex]->GetAnsiName();
		}
	};

	inline bool operator==(const FName &other) const
	{
		return ComparisonIndex == other.ComparisonIndex;
	};
};

class FString : public TArray<wchar_t>
{
public:
	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? static_cast<int32_t>(std::wcslen(other)) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		const auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

template<class TEnum>
class TEnumAsByte
{
public:
	inline TEnumAsByte()
	{
	}

	inline TEnumAsByte(TEnum _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	explicit inline TEnumAsByte(int32_t _value)
		: value(static_cast<uint8_t>(_value))
	{
	}

	explicit inline TEnumAsByte(uint8_t _value)
		: value(_value)
	{
	}

	inline operator TEnum() const
	{
		return (TEnum)value;
	}

	inline TEnum GetValue() const
	{
		return (TEnum)value;
	}

public:
	uint8_t value;
};

class FTextData {
public:
	char UnknownData[0x28];
	wchar_t* Name;
	__int32 Length;
};

struct FText {
	FTextData* Data;
	char UnknownData[0x10];

	wchar_t* Get() const {
		if (Data)
			return Data->Name;

		return nullptr;
	}
};

template<typename Key, typename Value>
class TMap
{
	char UnknownData[0x50];
};

template<class T, class TBASE>
class TAutoPointer : public TBASE
{
public:
	inline operator T*() const
	{
		return TBASE::Get();
	}

	inline operator const T*() const
	{
		return (const T*)TBASE::Get();
	}

	explicit inline operator bool() const
	{
		return TBASE::Get() != nullptr;
	}
};


class UClass;

template<class TClass>
class TSubclassOf
{
public:
	TSubclassOf(UClass* Class) {
		this->Class = Class;
	}

	inline UClass* GetClass()
	{
		return Class;
	}
private:
	UClass* Class;
};

struct FActorSpawnParameters
{
	FActorSpawnParameters()
		: Name("")
		, Template(NULL)
		, Owner(NULL)
		, Instigator(NULL)
		, OverrideLevel(NULL)
		, bNoCollisionFail(false)
		, bRemoteOwned(false)
		, bNoFail(false)
		, bDeferConstruction(false)
		, bAllowDuringConstructionScript(false)
		, ObjectFlags(0x00000008)
	{
	}
	FName Name;
	class AActor* Template;
	class AActor* Owner;
	class AActor* Instigator;
	class	ULevel* OverrideLevel;
	int	bNoCollisionFail : 1;
	int	bRemoteOwned : 1;
	int	bNoFail : 1;
	int	bDeferConstruction : 1;
	int	bAllowDuringConstructionScript : 1;
	int ObjectFlags;
};

enum EInternalObjectFlags
{
	None = 0,
	ReachableInCluster = 1 << 23,
	ClusterRoot = 1 << 24,
	Native = 1 << 25,
	Async = 1 << 26,
	AsyncLoading = 1 << 27,
	Unreachable = 1 << 28,
	PendingKill = 1 << 29,
	RootSet = 1 << 30,
	GarbageCollectionKeepFlags = Native | Async | AsyncLoading,
	AllFlags = ReachableInCluster | ClusterRoot | Native | Async | AsyncLoading | Unreachable | PendingKill | RootSet,
};

struct FStaticConstructObjectParameters
{
	const UClass* Class;
	UObject* Outer;
	FName Name;
	unsigned int SetFlags = 0x00000000;
	EInternalObjectFlags InternalSetFlags = EInternalObjectFlags::None;
	bool bCopyTransientsFromClassDefaults = false;
	bool bAssumeTemplateIsArchetype = false;
	UObject* Template = nullptr;
	void* InstanceGraph = nullptr;
	void* ExternalPackage = nullptr;
};

struct FKey
{
	FName KeyName;
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
