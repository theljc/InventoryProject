// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Inv_HighlightStaticMesh.h"


void UInv_HighlightStaticMesh::Highlight_Implementation()
{
	SetOverlayMaterial(HighlightMaterial);
}

void UInv_HighlightStaticMesh::UnHighlight_Implementation()
{
	SetOverlayMaterial(nullptr);
}
