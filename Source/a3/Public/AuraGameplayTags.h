

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * 这是一个包含原生游戏标签的单例
 * 标签由C++内部创建并可在C++内部使用，也可在编辑器和蓝图中使用
 */

struct FAuraGameplayTags
{
public:
	//静态获取游戏标签实例
	static  const FAuraGameplayTags& Get() { return GameplayTags; }
	//初始化原生游戏标签
	static void InitializeNativeGameplayTags();

	/*----------声明游戏标签变量----------*/
	//主要属性
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	//次要属性
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

protected:
	//输入操作
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	/*---------------------------------*/
	
private:
	//游戏标签实例
	static FAuraGameplayTags GameplayTags;
	
};
