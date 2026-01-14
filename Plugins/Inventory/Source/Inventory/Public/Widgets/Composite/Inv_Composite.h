// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inv_CompositeBase.h"
#include "Inv_Composite.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_Composite : public UInv_CompositeBase
{
	GENERATED_BODY()
public:
	virtual void ApplyFunction(FuncType InFunc) override;
	virtual void Collapse() override;
	
protected:
	virtual void NativeOnInitialized() override;
	
	
private:
	// 保存此 Widget 下的所有继承 UInv_CompositeBase 的子 Widget
	UPROPERTY()
	TArray<TObjectPtr<UInv_CompositeBase>> Children;
	
};
