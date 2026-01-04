// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagement/Components/Inv_InventoryComponent.h"

#include "Net/UnrealNetwork.h"
#include "Widgets/Inventory/InventoryBase/Inv_InventoryBase.h"


UInv_InventoryComponent::UInv_InventoryComponent() : InventoryList(this)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
	bInventoryMenuOpen = false;
}

void UInv_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass, InventoryList);
	
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	if (bInventoryMenuOpen)
	{
		CloseInventoryMenu();
	}
	else
	{
		OpenInventoryMenu();
	}
}

void UInv_InventoryComponent::AddRepSubObj(UObject* Object)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && IsValid(Object))
	{
		AddReplicatedSubObject(Object);
	}
}

void UInv_InventoryComponent::TryAddItem(UInv_ItemComponent* ItemComponent)
{
	FInv_SlotAvailabilityResult Result = InventoryMenu->HasRoomForItem(ItemComponent);
	if (Result.TotalRoomToFill == 0)
	{
		NoRoomInInventory.Broadcast();
		return;
	}

	if (Result.Item.IsValid() and Result.bStackable)
	{
		// 物品已存在，尝试堆叠
		Server_AddStackToItem(ItemComponent, Result.TotalRoomToFill, Result.Remainder);
	}
	else if (Result.TotalRoomToFill > 0)
	{
		// 物品不存在，尝试添加
		Server_AddNewItem(ItemComponent, Result.bStackable ? Result.TotalRoomToFill : 0);
	}
	
}

void UInv_InventoryComponent::Server_AddNewItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount)
{
	UInv_InventoryItem* NewItem = InventoryList.AddEntry(ItemComponent);
	if (GetOwner()->GetNetMode() == NM_ListenServer || GetOwner()->GetNetMode() == NM_Standalone)
	{
		OnItemAdded.Broadcast(NewItem);
	}
	
}

void UInv_InventoryComponent::Server_AddStackToItem_Implementation(UInv_ItemComponent* ItemComponent, int32 StackCount,
	int32 Remainder)
{
	
}

void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ConstructInventory();
	
}

void UInv_InventoryComponent::ConstructInventory()
{
	OwningController = Cast<APlayerController>(GetOwner());
	
	checkf(OwningController.IsValid(), TEXT("此组件所在的玩家控制器无效"));
	if (!OwningController->IsLocalController()) return;

	// CreateWidget 不能使用 WeakObjectPtr
	InventoryMenu = CreateWidget<UInv_InventoryBase>(OwningController.Get(), InventoryMenuClass);
	if (IsValid(InventoryMenu))
	{
		InventoryMenu->AddToViewport();
	}

	// 创建后隐藏
	CloseInventoryMenu();
}

void UInv_InventoryComponent::OpenInventoryMenu()
{
	if (!IsValid(InventoryMenu)) return;
	if (!OwningController.IsValid()) return;

	InventoryMenu->SetVisibility(ESlateVisibility::Visible);
	bInventoryMenuOpen = true;

	FInputModeGameAndUI InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(true);
	
}

void UInv_InventoryComponent::CloseInventoryMenu()
{
	if (!IsValid(InventoryMenu)) return;
	if (!OwningController.IsValid()) return;

	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
	bInventoryMenuOpen = false;

	FInputModeGameOnly InputMode;
	OwningController->SetInputMode(InputMode);
	OwningController->SetShowMouseCursor(false);
}



