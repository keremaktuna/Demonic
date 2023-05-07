// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemInterface.h"
#include "DemonicCharacter.generated.h"

UCLASS()
class DEMONIC_API ADemonicCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UDemonicAttributeSet* Attributes;

public:
	// Sets default values for this character's properties
	ADemonicCharacter();

	// Overriden from IAbilitySystemInterface.
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxArmor = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxBullets = 250;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	int MaxRockets = 20;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Effect that initializes our default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Demonic")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	// Array of starting abilities
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Demonic")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
};
