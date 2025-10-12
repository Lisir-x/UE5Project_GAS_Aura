

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

	//当前生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	//最大生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	//当前法力值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	//最大法力值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	/*---------- Rep Notify ----------*/
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
private:
	//设置效果属性
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
