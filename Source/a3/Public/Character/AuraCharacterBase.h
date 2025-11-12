

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UAnimMontage;
class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class A3_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	//获取能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//获取属性集组件
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	/*----------战斗接口----------*/
	//获取受击反应蒙太奇
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	//死亡逻辑
	virtual void Die() override;
	/*--------------------------*/
	
	//死亡多播句柄
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

protected:
	virtual void BeginPlay() override;

	//武器骨骼网格体组件
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//武器尖端插槽名称
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	//获取战斗插槽的位置
	virtual FVector GetCombatSocketLocation() override;

	//能力系统组件
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//属性集组件
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//初始化角色信息
	virtual void InitAbilityActorInfo();

	//关键属性游戏效果
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	//主要属性游戏效果
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	//次要属性游戏效果
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	//抗性属性游戏效果
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultResistanceAttributes;

	//应用效果到自身
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	//初始化默认属性
	virtual void InitializeDefaultAttributes() const;

	//添加角色技能
	void AddCharacterAbilities();
	
	/*----------溶解效果----------*/
	//溶解逻辑
	void Dissolve();

	//启用溶解时间轴
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	//启用武器溶解时间轴
	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	//溶解材质实例
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	//武器溶解材质实例
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
	/*--------------------------*/

private:
	//游戏技能类数组
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	//受击反应蒙太奇
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
