// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "Inv_ItemComponent.generated.h"


// 此组件挂载在可拾取物品上
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UInv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_ItemComponent();

	FString GetPickUpMessage() const { return PickUpMessage; }
	FInv_ItemManifest GetItemManifest() const { return ItemManifest; }
	void InitItemManifest(FInv_ItemManifest CopyOfItemManifest);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void PickUp();
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void OnPickedUp();

private:
	UPROPERTY(Replicated, EditAnywhere, Category="Inventory")
	FInv_ItemManifest ItemManifest;
	
	UPROPERTY(EditAnywhere, Category="Inventory")
	FString PickUpMessage;

};
