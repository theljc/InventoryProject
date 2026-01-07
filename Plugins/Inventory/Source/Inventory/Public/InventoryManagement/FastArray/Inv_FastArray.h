#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "Inv_FastArray.generated.h"

struct FGameplayTag;
class UInv_ItemComponent;
class UInv_InventoryComponent;
class UInv_InventoryItem;


// Fast Array 中单个元素的数据结构
USTRUCT(BlueprintType)
struct FInv_InventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
private:
	friend struct FInv_InventoryFastArray;
	friend UInv_InventoryComponent;
	
	UPROPERTY()
	TObjectPtr<UInv_InventoryItem> Item = nullptr;
	
};

USTRUCT()
struct FInv_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()
	
	FInv_InventoryFastArray() : OwnerComponent(nullptr) {}
	FInv_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent) {}

public:
	TArray<UInv_InventoryItem*> GetAllItems() const;

	// FastArraySerializer
	void PreReplicatedRemove(const TArrayView<int32>& RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32>& AddedIndices, int32 FinalSize);
	// End FastArraySerializer

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaInfo)
	{
		return FastArrayDeltaSerialize<FInv_InventoryEntry, FInv_InventoryFastArray>(Entries, DeltaInfo, *this);
	}

	UInv_InventoryItem* AddEntry(UInv_ItemComponent* Component);
	UInv_InventoryItem* AddEntry(UInv_InventoryItem* Item);
	void RemoveEntry(UInv_InventoryItem* Item);
	UInv_InventoryItem* FindFirstItemByType(const FGameplayTag& ItemType);
	
private:
	friend UInv_InventoryComponent;

	UPROPERTY()
	TArray<FInv_InventoryEntry> Entries;
	
	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
	
};

// 告知反射系统 FInv_InventoryFastArray 需要被增量序列化
template<>
struct TStructOpsTypeTraits<FInv_InventoryFastArray> : public TStructOpsTypeTraitsBase2<FInv_InventoryFastArray>
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};