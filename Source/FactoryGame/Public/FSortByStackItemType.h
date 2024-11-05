// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FGInventoryComponent.h"
#include "FGItemCategory.h"
#include "Resources/FGEquipmentDescriptor.h"

struct FSortByStackItemType
{
	explicit FSortByStackItemType()
	{
	}

	static bool SortByName( const FString& A, const FString& B )
	{
		const FString sA = A.ToLower();
		const FString sB = B.ToLower();

		return sA.Compare( sB ) < 0;
	}

	bool operator() ( const FInventoryStack& A, const FInventoryStack& B ) const
	{
		const FString AName = UFGEquipmentDescriptor::GetItemName( A.Item.GetItemClass() ).ToString();
		const FString BName = UFGEquipmentDescriptor::GetItemName( B.Item.GetItemClass() ).ToString();
		const TSubclassOf< UFGCategory > ACategory = UFGEquipmentDescriptor::GetCategory( A.Item.GetItemClass() );
		const TSubclassOf< UFGCategory > BCategory = UFGEquipmentDescriptor::GetCategory( B.Item.GetItemClass() );
		const FString ACategoryName = ACategory ? UFGItemCategory::GetCategoryName( UFGEquipmentDescriptor::GetCategory( A.Item.GetItemClass() ) ).ToString() : "";
		const FString BCategoryName = BCategory ? UFGItemCategory::GetCategoryName( UFGEquipmentDescriptor::GetCategory( B.Item.GetItemClass() ) ).ToString() : "";

		// Checks whether the stack contains anything.
		if( !A.HasItems() || !B.HasItems() )
		{
			return A.HasItems();
		}

		// If both items are same class, sort on number of items in stack
		if( A.Item.GetItemClass() == B.Item.GetItemClass() )
		{
			return A.NumItems > B.NumItems;
		}
		else if( !ACategoryName.Equals(BCategoryName) )
		{
			// If the items belong to different categories, sort by category
			return SortByName( ACategoryName, BCategoryName );
		}
		else if( A.Item.GetItemClass()->IsChildOf<UFGEquipmentDescriptor>() && B.Item.GetItemClass()->IsChildOf<UFGEquipmentDescriptor>() )
		{
			// If both items are equipment, sort on name
			return SortByName( AName, BName );
		}
		else if( A.Item.GetItemClass()->IsChildOf<UFGEquipmentDescriptor>() || B.Item.GetItemClass()->IsChildOf<UFGEquipmentDescriptor>() )
		{
			// If any of the two items are equipment, prioritize equipment
			return A.Item.GetItemClass()->IsChildOf<UFGEquipmentDescriptor>();
		}

		// If not caught in any of the cases above, sort on name
		return SortByName( AName, BName );
	}
};
