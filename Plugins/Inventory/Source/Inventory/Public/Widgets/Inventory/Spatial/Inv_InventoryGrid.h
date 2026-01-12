// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"

class UInv_ItemPopUp;
enum class EInv_GridSlotState : uint8;
class UInv_HoverItem;
struct FGameplayTag;
struct FInv_GridFragment;
struct FInv_ImageFragment;
class UInv_SlottedItem;
struct FInv_ItemManifest;
class UInv_ItemComponent;
class UInv_InventoryComponent;
class UCanvasPanel;
class UInv_GridSlot;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()
	
public:
	EInv_ItemCategory GetItemCategory() const { return ItemCategory; }
	FInv_SlotAvailabilityResult HasRoomForItem(const UInv_ItemComponent* ItemComponent);
	FInv_SlotAvailabilityResult HasRoomForItem(const FInv_ItemManifest& ItemManifest);
	void ShowCursor();
	void HideCursor();
	void SetOwningCanvas(UCanvasPanel* OwningCanvas);
	void DropItem();
	bool HasHoverItem() const;
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	void ConstructGrid();
	
	FInv_SlotAvailabilityResult HasRoomForItem(const UInv_InventoryItem* Item);
	bool MatchesCategory(const UInv_InventoryItem* Item) const;
	// 绘制 Item 的大小
	FVector2D GetDrawSize(const FInv_GridFragment* GridFragment) const;
	void SetSlottedItemImage(const UInv_SlottedItem* SlottedItem, const FInv_GridFragment* GridFragment, const FInv_ImageFragment* ImageFragment) const;
	void AddItemAtIndex(UInv_InventoryItem* Item, const int32 Index, const bool bStackable, const int32 StackAmount);
	UInv_SlottedItem* CreateSlottedItem(UInv_InventoryItem* Item,
		const bool bStackable,
		const int32 StackAmount,
		const FInv_GridFragment* GridFragment,
		const FInv_ImageFragment* ImageFragment,
		const int32 Index);
	
	UFUNCTION()
	void AddItem(UInv_InventoryItem* Item);
	void AddItemToIndices(const FInv_SlotAvailabilityResult& SlotAvailabilityResult, UInv_InventoryItem* Item);
	// 将 Item 添加到 CanvasPanel 中
	void AddSlottedItemToCanvas(const int32 Index, const FInv_GridFragment* GridFragment, UInv_SlottedItem* SlottedItem) const;

	// 更新插槽的状态
	void UpdateGridSlots(UInv_InventoryItem* NewItem, const int32 Index, bool bStackableItem, const int32 StackAmount);

	bool IsIndexClaimed(const TSet<int32>& CheckedIndices, const int32 Index) const;
	bool HasRoomAtIndex(const UInv_GridSlot* GridSlot, const FIntPoint& Dimensions,
		const TSet<int32>& CheckedIndices, TSet<int32>& OutTentativelyClaimed,
		const FGameplayTag& ItemType, const int32 MaxStackSize);
	// 检查物品占用范围内的所有子插槽是否可用
	bool CheckSlotConstraints(const UInv_GridSlot* GridSlot, const UInv_GridSlot* SubGridSlot,
		const TSet<int32>& CheckedIndices, TSet<int32>& OutTentativelyClaimed,
		const FGameplayTag& ItemType, const int32 MaxStackSize) const;
	// 获得物品占用的插槽大小
	FIntPoint GetItemDimensions(const FInv_ItemManifest& Manifest) const;
	// 判断插槽中是否已经包含了物品
	bool HasValidItem(const UInv_GridSlot* GridSlot) const;
	bool IsUpperLeftSlot(const UInv_GridSlot* GridSlot, const UInv_GridSlot* SubGridSlot) const;
	bool DoesItemTypeMatch(const UInv_InventoryItem* Item, const FGameplayTag& ItemType) const;
	// 判断物品是否在网格边界内
	bool IsInGridBounds(const int32 StartIndex, const FIntPoint& ItemDimensions) const;
	// 确定需要堆叠到插槽的物品数量
	int32 DetermineFillAmountForSlot(const bool bStackable, const int32 MaxStackSize, const int32 AmountToFill, const UInv_GridSlot* GridSlot) const;
	// 获取插槽中物品的堆叠数量
	int32 GetStackAmount(const UInv_GridSlot* GridSlot) const;
	bool IsRightClick(const FPointerEvent& MouseEvent);
	bool IsLeftClick(const FPointerEvent& MouseEvent);
	void PickUp(UInv_InventoryItem* ClickInventoryItem, const int32 GridIndex);
	void AssignHoverItem(UInv_InventoryItem* InventoryItem);
	void AssignHoverItem(UInv_InventoryItem* InventoryItem, const int32 GridIndex, const int32 PreviousGridIndex);
	void RemoveItemFromGrid(UInv_InventoryItem* InventoryItem, const int32 GridIndex);
	void UpdateTileParameters(const FVector2D& CanvasPosition, const FVector2D& MousePosition);
	FIntPoint CalcHoverCoordinates(const FVector2D& CanvasPosition, const FVector2D& MousePosition) const;
	EInv_TileQuadrant CalcTileQuadrant(const FVector2D& CanvasPosition, const FVector2D& MousePosition) const;
	void OnTileParametersUpdated(const FInv_TileParameters& Parameters);
	FIntPoint CalculateStartingCoordinate(const FIntPoint& Coordinate, const FIntPoint& Dimensions, const EInv_TileQuadrant Quadrant) const;
	FInv_SpaceQueryResult CheckHoverPosition(const FIntPoint& Position, const FIntPoint& Dimensions);
	bool CursorExitedCanvas(const FVector2D& BoundaryPos, const FVector2D& BoundarySize, const FVector2D& Location);
	void HighlightSlots(const int32 Index, const FIntPoint& Dimensions);
	void UnHighlightSlots(const int32 Index, const FIntPoint& Dimensions);
	void ChangeHoverType(const int32 Index, const FIntPoint& Dimensions, EInv_GridSlotState GridSlotState);
	void PutDownOnIndex(const int32 Index);
	void ClearHoverItem();
	UUserWidget* GetVisibleCursorWidget();
	UUserWidget* GetHiddenCursorWidget();
	bool IsSameStackable(const UInv_InventoryItem* ClickedInventoryItem) const;
	void SwapWithHoverItem(UInv_InventoryItem* ClickedInventoryItem, const int32 GridIndex);
	bool ShouldSwapStackCounts(const int32 RoomInClickedSlot, const int32 HoveredStackCount, const int32 MaxStackSize) const;
	void SwapStackCounts(const int32 ClickedStackCount, const int32 HoveredStackCount, const int32 Index);
	bool ShouldConsumeHoverItemStacks(const int32 HoveredStackCount, const int32 RoomInClickedSlot) const;
	void ConsumeHoverItemStacks(const int32 ClickedStackCount, const int32 HoveredStackCount, const int32 Index);
	bool ShouldFillInStack(const int32 RoomInClickedSlot, const int32 HoveredStackCount) const;
	void FillInStack(const int32 FillAmount, const int32 Remainder, const int32 Index);
	void CreateItemPopUp(const int32 GridIndex);
	
	UFUNCTION()
	void AddStacks(const FInv_SlotAvailabilityResult& Result);

	UFUNCTION()
	void OnSlottedItemClicked(int32 GridIndex, const FPointerEvent& MouseEvent);

	UFUNCTION()
	void OnGridSlotClicked(int32 GridIndex, const FPointerEvent& MouseEvent);

	UFUNCTION()
	void OnGridSlotHovered(int32 GridIndex, const FPointerEvent& MouseEvent);

	UFUNCTION()
	void OnGridSlotUnhovered(int32 GridIndex, const FPointerEvent& MouseEvent);

	UFUNCTION()
	void OnPopUpMenuSplit(int32 SplitAmount, int32 Index);

	UFUNCTION()
	void OnPopUpMenuDrop(int32 Index);

	UFUNCTION()
	void OnPopUpMenuConsume(int32 Index);

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UInv_ItemPopUp> ItemPopUpClass;
	
	UPROPERTY()
	TObjectPtr<UInv_ItemPopUp> ItemPopUp;
	
	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UUserWidget> VisibleCursorWidgetClass;

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UUserWidget> HiddenCursorWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> VisibleCursorWidget;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> HiddenCursorWidget;
	
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	TWeakObjectPtr<UCanvasPanel> OwningCanvasPanel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="Inventory")
	EInv_ItemCategory ItemCategory;

	UPROPERTY()
	TArray<TObjectPtr<UInv_GridSlot>> GridSlots;

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UInv_GridSlot> GridSlotClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UInv_SlottedItem> SlottedItemClass;

	// 插槽中 Item 的索引和对应的 Item
	UPROPERTY()
	TMap<int32, TObjectPtr<UInv_SlottedItem>> SlottedItems;
	
	UPROPERTY(EditAnywhere, Category="Inventory")
	int32 Rows;

	UPROPERTY(EditAnywhere, Category="Inventory")
	int32 Columns;

	UPROPERTY(EditAnywhere, Category="Inventory")
	float TileSize;

	UPROPERTY(EditAnywhere, Category="Inventory")
	TSubclassOf<UInv_HoverItem> HoverItemClass;

	UPROPERTY()
	TObjectPtr<UInv_HoverItem> HoverItem;

	// 保存上一帧和当前帧的插槽参数，用于确定插槽是否切换
	FInv_TileParameters TileParameters;
	FInv_TileParameters LastTileParameters;
	// 物品拖拽时的当前插槽索引
	int32 ItemDropIndex = INDEX_NONE;
	FInv_SpaceQueryResult CurrentQueryResult;
	bool bMouseWithinCanvas;
	bool bLastMouseWithinCanvas;
	int32 LastHighlightIndex;
	FIntPoint LastHighlightDimensions;
	
};
