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
	float AbsoluteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

	if(Data.EvaluatedData.Magnitude > 0)
	{
		if(Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() + AbsoluteMagnitude >= 100.0f)
		{
			SetArmor(100);
			return false;
		}

		if(Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() + AbsoluteMagnitude >= 100.0f)
		{
			SetHealth(100);
			return false;
		}
	}
	else
	{
		if(Data.EvaluatedData.Attribute == GetArmorAttribute() && AbsoluteMagnitude > GetArmor())
			Health.SetCurrentValue(Health.GetCurrentValue() - (AbsoluteMagnitude - GetArmor()));
	}
	
	return true;
}

