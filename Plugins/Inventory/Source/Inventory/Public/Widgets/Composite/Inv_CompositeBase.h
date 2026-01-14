// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Inv_CompositeBase.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_CompositeBase : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetFragmentTag(FGameplayTag InFragmentTag) { FragmentTag = InFragmentTag; }
	FGameplayTag GetFragmentTag() const { return FragmentTag; }

	using FuncType = TFunction<void(UInv_CompositeBase*)>;
	virtual void ApplyFunction(FuncType InFunc) {}
	virtual void Collapse();
	void Expand();
	
private:
	UPROPERTY(EditAnywhere, Category="Inventory")
	FGameplayTag FragmentTag;
	
};
