#pragma once

#include "Inv_GridTypes.generated.h"

class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_ItemCategory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};

// 单个槽位内容
USTRUCT()
struct FInv_SlotAvailability
{
	GENERATED_BODY()

	FInv_SlotAvailability() {}
	FInv_SlotAvailability(int32 InIndex, int32 InAmountToFill, bool InItemAtIndex) : Index(InIndex), AmountToFill(InAmountToFill), bItemAtIndex(InItemAtIndex) {}

	// 此槽位的索引
	int32 Index = INDEX_NONE;
	// 此槽位可放置的物品数量
	int32 AmountToFill = 0;
	// 此槽位是否有物品
	bool bItemAtIndex = false;
};

USTRUCT()
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()

	FInv_SlotAvailabilityResult() {}

	// 物品类型
	TWeakObjectPtr<UInv_InventoryItem> Item;
	// 物品占用的空间
	int32 TotalRoomToFill = 0;
	// 物品无法放置时，剩余多少数量不能放置
	int32 Remainder = 0;
	// 是否可堆叠
	bool bStackable = false;
	// 每个槽位的具体信息
	TArray<FInv_SlotAvailability> SlotAvailabilities;
	
};