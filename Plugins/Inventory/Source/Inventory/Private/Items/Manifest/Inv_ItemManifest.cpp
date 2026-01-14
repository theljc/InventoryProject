#include "Items/Manifest/Inv_ItemManifest.h"

#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Items/Fragments/Inv_ItemFragment.h"
#include "Widgets/Composite/Inv_CompositeBase.h"

UInv_InventoryItem* FInv_ItemManifest::Manifest(UObject* NewOuter)
{
	UInv_InventoryItem* NewItem = NewObject<UInv_InventoryItem>(NewOuter, UInv_InventoryItem::StaticClass());
	NewItem->SetItemManifest(*this);

	for (auto& Fragment : NewItem->GetItemManifestMutable().GetFragmentsMutable())
	{
		Fragment.GetMutable().Manifest();
	}
	ClearFragments();
	
	return NewItem;
}

void FInv_ItemManifest::SpawnPickUpActor(const UObject* WorldContext, const FVector& SpawnLocation,
	const FRotator& SpawnRotation)
{
	if (!IsValid(WorldContext) or !IsValid(PickUpActorClass)) return;

	AActor* SpawnedActor = WorldContext->GetWorld()->SpawnActor<AActor>(PickUpActorClass, SpawnLocation, SpawnRotation);
	if (!IsValid(SpawnedActor)) return;

	UInv_ItemComponent* ItemComponent = SpawnedActor->FindComponentByClass<UInv_ItemComponent>();
	check(ItemComponent);

	ItemComponent->InitItemManifest(*this);
}

void FInv_ItemManifest::AssimilateInventoryFragments(UInv_CompositeBase* Composite) const
{
	const auto& InventoryItemFragments = GetAllFragmentsOfType<FInv_InventoryItemFragment>();
	for (const auto* Fragment : InventoryItemFragments)
	{
		Composite->ApplyFunction([Fragment](UInv_CompositeBase* Widget)
		{
			Fragment->Assimilate(Widget);
		});
	}
}

void FInv_ItemManifest::ClearFragments()
{
	for (auto& Fragment : Fragments)
	{
		Fragment.Reset();
	}
	Fragments.Empty();
}
