

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
	//抗性属性
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Water;
	FGameplayTag Attributes_Resistance_Wind;
	FGameplayTag Attributes_Resistance_Ice;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Geo;
	FGameplayTag Attributes_Resistance_Grass;
	FGameplayTag Attributes_Resistance_Light;
	FGameplayTag Attributes_Resistance_Dark;
	FGameplayTag Attributes_Resistance_Physical;

	//输入操作
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	//伤害
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Water;
	FGameplayTag Damage_Wind;
	FGameplayTag Damage_Ice;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Geo;
	FGameplayTag Damage_Grass;
	FGameplayTag Damage_Light;
	FGameplayTag Damage_Dark;
	FGameplayTag Damage_Physical;
	//伤害类型与抗性映射集
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	//受击反应
	FGameplayTag Effects_HitReact;
	/*---------------------------------*/
	
private:
	//游戏标签实例
	static FAuraGameplayTags GameplayTags;
	
};
