// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_InfoMessage.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_InfoMessage : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void ShowMessage();

	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void HideMessage();
	
	void SetMessage(const FText& Message);

protected:
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_Message;

	UPROPERTY(EditAnywhere, Category="Inventory")
	float MessageLifetime = 3.f;

	FTimerHandle MessageTimerHandle;
	bool bIsMessageActive = false;
	
};
