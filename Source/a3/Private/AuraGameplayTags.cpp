


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	//给游戏标签赋予属性
	/*----------主要属性----------*/
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("力量：提升物理伤害"));

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("智力：提升法术伤害，决定法力恢复和最大法力值"));

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("韧性：提升护甲和护甲穿透"));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("活力：提升生命值，决定生命恢复和最大生命值"));
	
	/*----------次要属性----------*/
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("护甲：减少受到的伤害，提升格挡率和暴击抗性"));

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("护甲穿透：无视部分护甲，提升暴击率和暴击伤害"));

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("格挡率：触发格挡的概率，触发时使受到的伤害减半"));

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("暴击率：触发暴击的概率，触发时使伤害提高"));

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("暴击伤害：触发暴击时伤害提高的幅度"));

	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("暴击抵抗：降低受到伤害时的暴击率"));

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("生命恢复：每秒恢复的生命值"));

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("法力恢复：每秒恢复的法力值"));

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("最大生命值：角色的生命值上限"));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("最大法力值：角色的法力值上限"));

	/*----------抗性属性----------*/
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		FString("火属性抗性：减少受到的火属性伤害"));
	
	GameplayTags.Attributes_Resistance_Water = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Water"),
		FString("水属性抗性：减少受到的水属性伤害"));
	
	GameplayTags.Attributes_Resistance_Wind = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Wind"),
		FString("风属性抗性：减少受到的风属性伤害"));
	
	GameplayTags.Attributes_Resistance_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Ice"),
		FString("冰属性抗性：减少受到的冰属性伤害"));
	
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		FString("雷属性抗性：减少受到的雷属性伤害"));
	
	GameplayTags.Attributes_Resistance_Geo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Geo"),
		FString("岩属性抗性：减少受到的岩属性伤害"));
	
	GameplayTags.Attributes_Resistance_Grass = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Grass"),
		FString("草属性抗性：减少受到的草属性伤害"));
	
	GameplayTags.Attributes_Resistance_Light = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Light"),
		FString("光属性抗性：减少受到的光属性伤害"));
	
	GameplayTags.Attributes_Resistance_Dark = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Dark"),
		FString("暗属性抗性：减少受到的暗属性伤害"));
	
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"),
		FString("物理抗性：减少受到的物理伤害"));
	
	/*----------输入操作----------*/
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button"));

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key"));

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key"));

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key"));

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key"));

	/*----------伤害及伤害类型----------*/
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage"));

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"),
		FString("火属性伤害"));

	GameplayTags.Damage_Water = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Water"),
		FString("水属性伤害"));

	GameplayTags.Damage_Wind = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Wind"),
		FString("风属性伤害"));

	GameplayTags.Damage_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Ice"),
		FString("冰属性伤害"));

	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"),
		FString("雷属性伤害"));

	GameplayTags.Damage_Geo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Geo"),
		FString("岩属性伤害"));
	
	GameplayTags.Damage_Grass = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Grass"),
		FString("草属性伤害"));
	
	GameplayTags.Damage_Light = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Light"),
		FString("光属性伤害"));
	
	GameplayTags.Damage_Dark = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Dark"),
		FString("暗属性伤害"));
	
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("物理伤害"));

	/*----------伤害类型与抗性映射----------*/
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Fire,
		GameplayTags.Attributes_Resistance_Fire);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Water,
		GameplayTags.Attributes_Resistance_Water);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Wind,
		GameplayTags.Attributes_Resistance_Wind);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Ice,
		GameplayTags.Attributes_Resistance_Ice);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Lightning,
		GameplayTags.Attributes_Resistance_Lightning);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Geo,
		GameplayTags.Attributes_Resistance_Geo);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Grass,
		GameplayTags.Attributes_Resistance_Grass);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Light,
		GameplayTags.Attributes_Resistance_Light);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Dark,
		GameplayTags.Attributes_Resistance_Dark);
	
	GameplayTags.DamageTypesToResistances.Add(
		GameplayTags.Damage_Physical,
		GameplayTags.Attributes_Resistance_Physical);

	/*----------受击反应----------*/
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Tag granted when Hit Reacting"));
}
