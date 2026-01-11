#include "Items/Manifest/Inv_ItemManifest.h"

#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"

UInv_InventoryItem* FInv_ItemManifest::Manifest(UObject* NewOuter)
{
	UInv_InventoryItem* NewItem = NewObject<UInv_InventoryItem>(NewOuter, UInv_InventoryItem::StaticClass());
	NewItem->SetItemManifest(*this);
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
