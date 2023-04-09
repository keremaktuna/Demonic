// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObjects.h"

// Sets default values
APooledObjects::APooledObjects()
{
	
}

void APooledObjects::SetActive(bool IsActive)
{
	Active = IsActive;
	SetActorHiddenInGame(!IsActive);
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this ,&APooledObjects::Deactive, LifeSpan, false);
}

void APooledObjects::SetLifeSpan(float InLifespan)
{
	LifeSpan = InLifespan;
}

void APooledObjects::SetPoolIndex(int Index)
{
	PoolIndex = Index;
}

void APooledObjects::Deactive()
{
	SetActive(false);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	OnPooledObjectDespawn.Broadcast(this);
}

bool APooledObjects::IsActive()
{
	return Active;
}

int APooledObjects::GetPoolIndex()
{
	return PoolIndex;
}
