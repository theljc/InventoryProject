// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/HUD/Inv_HUDWidget.h"
#include "Inv_PlayerController.generated.h"

class UInv_InventoryComponent;
class UInputAction;
class UInputMappingContext;
DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);

/**
 * 
 */
UCLASS()
class INVENTORY_API AInv_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AInv_PlayerController();

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

protected:
	void BeginPlay() override;
	void SetupInputComponent() override;
	void Tick(float DeltaTime) override;

	void PrimaryInteract();
	void CreateHUDWidget();
	void TraceForItem();

private:
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TObjectPtr<UInputMappingContext> DefaultIMC;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TObjectPtr<UInputAction> ToggleInventoryAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UInv_HUDWidget> HUDWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	double TraceLength;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

	TWeakObjectPtr<AActor> LastActor;
	TWeakObjectPtr<AActor> ThisActor;
	
};
