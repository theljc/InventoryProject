// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_InventoryItem.generated.h"

/**
 * 插槽中具体的物品数据
 */
UCLASS()
class INVENTORY_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// 动态创建的 Subobject 同步时，需要 IsSupportedForNetworking 返回 true
	virtual bool IsSupportedForNetworking() const override { return true; };
	
	void SetItemManifest(const FInv_ItemManifest& Manifest);
	const FInv_ItemManifest GetItemManifest() const { return ItemManifest.Get<FInv_ItemManifest>(); };
	const FInv_ItemManifest GetItemManifestMutable() { return ItemManifest.GetMutable<FInv_ItemManifest>(); };
	
private:
	UPROPERTY(VisibleAnywhere, meta=(BaseStruct="/Script/Inventory.Inv_ItemManifest"), Replicated)
	FInstancedStruct ItemManifest;
	
};

template<typename FragmentType>
const FragmentType* GetFragment(const UInv_InventoryItem* Item, const FGameplayTag& FragmentTag)
{
	if (!IsValid(Item)) return nullptr;
	const FInv_ItemManifest& ItemManifest = Item->GetItemManifest();
	return ItemManifest.GetFragmentOfTypeWithTag<FragmentType>(FragmentTag);
}
