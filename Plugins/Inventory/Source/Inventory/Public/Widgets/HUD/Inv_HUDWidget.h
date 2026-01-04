// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HUDWidget.generated.h"

class UInv_InfoMessage;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_HUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void ShowPickUpMessage(const FString& Message);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void HidePickUpMessage();

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnNoRoom();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInv_InfoMessage> InfoMessage;
	
};
