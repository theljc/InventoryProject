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

// 用于确定拖拽时鼠标所在槽位的象限
UENUM(BlueprintType)
enum class EInv_TileQuadrant : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	None
};

// 插槽的参数
USTRUCT(BlueprintType)
struct FInv_TileParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FIntPoint TileCoordinates;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 TileIndex = INDEX_NONE;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EInv_TileQuadrant TileQuadrant = EInv_TileQuadrant::None;
	
};

inline bool operator==(const FInv_TileParameters& LHS, const FInv_TileParameters& RHS)
{
	return LHS.TileCoordinates == RHS.TileCoordinates &&
		LHS.TileQuadrant == RHS.TileQuadrant &&
		LHS.TileIndex == RHS.TileIndex;
}

// 拖拽时，检查物品是否可以放置
USTRUCT()
struct FInv_SpaceQueryResult
{
	GENERATED_BODY()

	// 当前插槽中是否有物品
	bool bHasSpace{false};

	// 如果有物品，那么这个物品是什么
	TWeakObjectPtr<UInv_InventoryItem> ValidItem = nullptr;

	// 如果有物品，那么这个物品的左上角索引（起始位置）是多少
	int32 UpperLeftIndex{INDEX_NONE};
};
