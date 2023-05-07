// Fill out your copyright notice in the Description page of Project Settings.


#include "DemonicAttributeSet.h"

UDemonicAttributeSet::UDemonicAttributeSet()
{
	
}

void UDemonicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	NewValue = FMath::Clamp<float>(NewValue, 0.0f, 100.0f);
}

bool UDemonicAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	float ArmorDamage = FMath::Abs(Data.EvaluatedData.Magnitude);

	if(Data.EvaluatedData.Attribute == GetArmorAttribute() && ArmorDamage > GetArmor() && Data.EvaluatedData.Magnitude < 0)
		Health.SetCurrentValue(Health.GetCurrentValue() - (ArmorDamage - GetArmor()));

	return true;
}

