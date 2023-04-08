// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PooledObjects.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDesapawn, APooledObjects*, PoolActor);

UCLASS()
class DEMONIC_API APooledObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooledObjects();

	FOnPooledObjectDesapawn OnPooledObjectDespawn;

	UFUNCTION(BlueprintCallable, Category = "Pooled Object")
	void Deactive();

	void SetActive(bool IsActive);
	void SetLifeSpan(float InLifespan);
	void SetPoolIndex(int Index);

	bool IsActive();
	int GetPoolIndex();

protected:

	bool Active;
	float LifeSpan = 0.0f;
	int PoolIndex;

	FTimerHandle LifeSpanTimer;
};
