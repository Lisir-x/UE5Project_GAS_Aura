

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

//宏定义：生成与游戏属性相关的访问器函数
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//结构体：存储与游戏效果相关的各种属性和上下文信息
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	//游戏效果上下文句柄
	FGameplayEffectContextHandle EffectContextHandle;

	//源能力系统组件
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	//源角色的AvatarActor
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	//源控制器
	UPROPERTY()
	AController* SourceController = nullptr;

	//源角色
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	//目标能力系统组件
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	//目标角色的AvatarActor
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	//目标控制器
	UPROPERTY()
	AController* TargetController = nullptr;

	//目标角色
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

//typedef是只针对FGameplayAttribute()的签名，但是TStaticFunPtr适用于任意签名
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class A3_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	//属性复制函数
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//预属性变化
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//游戏效果执行后
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	//游戏标签和属性的映射表(值为函数指针)
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/*----------关键属性----------*/
	//当前生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	//当前法力值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	/*--------------------------*/

	/*----------主要属性----------*/
	//力量：提升物理伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	//智力：提升法术伤害，决定法力恢复和最大法力值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	//韧性：提升护甲和护甲穿透
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	//活力：提升生命值，决定生命恢复和最大生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	/*--------------------------*/

	/*----------次要属性----------*/
	//护甲：减少受到的伤害，提升格挡率和暴击抗性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	//护甲穿透：无视部分护甲，提升暴击率和暴击伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	//格挡率：触发格挡的概率，触发时使受到的伤害减半
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	//暴击率：触发暴击的概率，触发时使伤害提高
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	//暴击伤害：触发暴击时伤害提高的幅度
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	//暴击抵抗：降低受到伤害时的暴击率
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	//生命恢复：每秒恢复的生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	//法力恢复：每秒恢复的法力值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	//最大生命值：角色的生命值上限
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	//最大法力值：角色的法力值上限
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	/*--------------------------*/

	/*----------抗性属性----------*/
	//火属性抗性：减少受到的火属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Resistance Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FireResistance);

	//水属性抗性：减少受到的水属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WaterResistance, Category = "Resistance Attributes")
	FGameplayAttributeData WaterResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, WaterResistance);

	//风属性抗性：减少受到的风属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WindResistance, Category = "Resistance Attributes")
	FGameplayAttributeData WindResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, WindResistance);

	//冰属性抗性：减少受到的冰属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IceResistance, Category = "Resistance Attributes")
	FGameplayAttributeData IceResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IceResistance);

	//雷属性抗性：减少受到的雷属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Resistance Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, LightningResistance);

	//岩属性抗性：减少受到的岩属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_GeoResistance, Category = "Resistance Attributes")
	FGameplayAttributeData GeoResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, GeoResistance);

	//草属性抗性：减少受到的草属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_GrassResistance, Category = "Resistance Attributes")
	FGameplayAttributeData GrassResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, GrassResistance);

	//光属性抗性：减少受到的光属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightResistance, Category = "Resistance Attributes")
	FGameplayAttributeData LightResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, LightResistance);

	//暗属性抗性：减少受到的暗属性伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DarkResistance, Category = "Resistance Attributes")
	FGameplayAttributeData DarkResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, DarkResistance);

	//物理抗性：减少受到的物理伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Resistance Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PhysicalResistance);
	/*--------------------------*/
	
	/*----------元属性----------*/
	//即将受到的伤害
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);
	/*-------------------------*/

	/*----------副本通知函数----------*/
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;
	
	UFUNCTION()
	void OnRep_WaterResistance(const FGameplayAttributeData& OldWaterResistance) const;
	
	UFUNCTION()
	void OnRep_WindResistance(const FGameplayAttributeData& OldWindResistance) const;
	
	UFUNCTION()
	void OnRep_IceResistance(const FGameplayAttributeData& OldIceResistance) const;
	
	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;
	
	UFUNCTION()
	void OnRep_GeoResistance(const FGameplayAttributeData& OldGeoResistance) const;
	
	UFUNCTION()
	void OnRep_GrassResistance(const FGameplayAttributeData& OldGrassResistance) const;
	
	UFUNCTION()
	void OnRep_LightResistance(const FGameplayAttributeData& OldLightResistance) const;
	
	UFUNCTION()
	void OnRep_DarkResistance(const FGameplayAttributeData& OldDarkResistance) const;
	
	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;
	/*------------------------------*/
	
private:
	//设置效果属性
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	//显示浮动文本
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
};
