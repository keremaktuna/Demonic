// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolComp.h"

// Sets default values for this component's properties
UObjectPoolComp::UObjectPoolComp()
{
}

// Called when the game starts
void UObjectPoolComp::BeginPlay()
{
	Super::BeginPlay();

	if(PooledObjectSubclass != nullptr)
	{
		UWorld* const World = GetWorld();

		if(World != nullptr)
		{
			for(int i = 0; i < PoolSize; i++)
			{
				APooledObjects* PoolableActor = World->SpawnActor<APooledObjects>(PooledObjectSubclass, FVector().ZeroVector, FRotator().ZeroRotator);

				if(PoolableActor != nullptr)
				{
					PoolableActor->SetActive(false);
					PoolableActor->SetPoolIndex(i);
					PoolableActor->OnPooledObjectDespawn.AddDynamic(this, &UObjectPoolComp::OnPooledObjectDespawn);
					ObjectPool.Add(PoolableActor);
				}
			}
		}
	}
}

APooledObjects* UObjectPoolComp::SpawnPooledObject()
{
	for(APooledObjects* PoolableActor : ObjectPool)
	{
		if(PoolableActor != nullptr && !PoolableActor->IsActive())
		{
			PoolableActor->TeleportTo(FVector(0,0,0), FRotator(0,0,0));
			PoolableActor->SetLifeSpan(PooledObjectLifeSpan);
			PoolableActor->SetActive(true);
			SpawnedPoolIndexes.Add(PoolableActor->GetPoolIndex());

			return PoolableActor;
		}
	}

	return nullptr;
}

void UObjectPoolComp::OnPooledObjectDespawn(APooledObjects* PoolActor)
{
	SpawnedPoolIndexes.Remove(PoolActor->GetPoolIndex());
}


