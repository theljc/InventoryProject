// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Composite/Inv_Composite.h"

#include "Blueprint/WidgetTree.h"

void UInv_Composite::ApplyFunction(FuncType InFunc)
{
	for (auto Child : Children)
	{
		Child->ApplyFunction(InFunc);
	}
}

void UInv_Composite::Collapse()
{
	for (auto Child : Children)
	{
		Child->Collapse();
	}
}

void UInv_Composite::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	WidgetTree->ForEachWidget([this](UWidget* Widget)
	{
		UInv_CompositeBase* CompositeWidget = Cast<UInv_CompositeBase>(Widget);
		if (IsValid(CompositeWidget))
		{
			Children.Add(CompositeWidget);
			CompositeWidget->Collapse();
		}
	});
}
