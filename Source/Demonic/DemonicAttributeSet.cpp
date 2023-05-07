// Fill out your copyright notice in the Description page of Project Settings.


#include "DemonicAttributeSet.h"

#include "DemonicCharacter.h"

UDemonicAttributeSet::UDemonicAttributeSet()
{
	
}

void UDemonicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	ADemonicCharacter* DemonicCharacter = Cast<ADemonicCharacter>(GetOwningActor());

	if(Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, DemonicCharacter->MaxHealth);
	else if(Attribute == GetArmorAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, DemonicCharacter->MaxArmor);
	else if(Attribute == GetBulletsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, DemonicCharacter->MaxBullets);
	else if(Attribute == GetRocketsAttribute())
		NewValue = FMath::Clamp<float>(NewValue, 0, DemonicCharacter->MaxRockets);
}

bool UDemonicAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	float AbsoluteMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude);

	ADemonicCharacter* DemonicCharacter = Cast<ADemonicCharacter>(GetOwningActor());

	if(Data.EvaluatedData.Magnitude > 0)
	{
		if(Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() + AbsoluteMagnitude >= DemonicCharacter->MaxArmor)
		{
			SetArmor(DemonicCharacter->MaxArmor);
			return false;
		}
		else if(Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() + AbsoluteMagnitude >= DemonicCharacter->MaxHealth)
		{
			SetHealth(DemonicCharacter->MaxHealth);
			return false;
		}
		else if(Data.EvaluatedData.Attribute == GetBulletsAttribute() && GetBullets() + AbsoluteMagnitude >= DemonicCharacter->MaxBullets)
		{
			SetBullets(DemonicCharacter->MaxBullets);
			return false;
		}
		else if(Data.EvaluatedData.Attribute == GetRocketsAttribute() && GetRockets() + AbsoluteMagnitude >= DemonicCharacter->MaxRockets)
		{
			SetRockets(DemonicCharacter->MaxRockets);
			return false;
		}
	}
	else if(Data.EvaluatedData.Magnitude < 0)
	{
		if(Data.EvaluatedData.Attribute == GetArmorAttribute() && AbsoluteMagnitude > GetArmor())
			Health.SetCurrentValue(Health.GetCurrentValue() - (AbsoluteMagnitude - GetArmor()));
	}
	
	return true;
}

void UDemonicAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if(Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth()< 0)
		SetHealth(0);
	else if(Data.EvaluatedData.Attribute == GetArmorAttribute() && GetArmor() < 0)
		SetArmor(0);
	else if(Data.EvaluatedData.Attribute == GetBulletsAttribute() && GetBullets() < 0)
		SetBullets(0);
	else if(Data.EvaluatedData.Attribute == GetRocketsAttribute() && GetRockets() < 0)
		SetRockets(0);
}

