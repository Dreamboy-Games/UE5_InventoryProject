
#include "InventoryManagement/FastArray/Inv_FastArray.h"

#include "LandscapeGizmoActiveActor.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Compnents/Inv_ItemComponent.h"
#include "Items/Inv_InventoryItem.h"

TArray<UInv_InventoryItem*> FInv_InventoryFastArray::GetAllItems() const
{
	TArray<UInv_InventoryItem*> Results;
	Results.Reserve(Entries.Num());
	for (const FInv_InventoryEntry& Entry : Entries)
	{
		if (!IsValid(Entry.Item))
		{
			Results.Add(Entry.Item);
		}
	}
	return Results;
}

void FInv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemoveIndices, int32 FinalSize)
{
	const UInv_InventoryComponent* InvComp = Cast<UInv_InventoryComponent>(OwnerComponent);
	if (!IsValid(InvComp)) return;
	
	for (const int32 Index : RemoveIndices)
	{
		InvComp->OnItemRemoved.Broadcast(Entries[Index].Item);
	}
}

void FInv_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddIndices, int32 FinalSize)
{
	const UInv_InventoryComponent* InvComp = Cast<UInv_InventoryComponent>(OwnerComponent);
	if (!IsValid(InvComp)) return;
	
	for (const int32 Index : AddIndices)
	{
		InvComp->OnItemAdded.Broadcast(Entries[Index].Item);
	}
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_ItemComponent* ItemComponent)
{
	// TODO: Implement once ItemComponet is more complete.
	return nullptr;
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_InventoryItem* Item)
{
	check(OwnerComponent);
	const AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	
	FInv_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = Item;
	
	MarkItemDirty(NewEntry);
	return Item;
}

void FInv_InventoryFastArray::RemoveEntry(UInv_InventoryItem* Item)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FInv_InventoryEntry& Entry = *EntryIt;
		if (Entry.Item == Item)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}
