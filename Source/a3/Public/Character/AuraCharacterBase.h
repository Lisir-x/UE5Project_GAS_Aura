

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class A3_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	//获取能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//获取属性集组件
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

protected:
	virtual void BeginPlay() override;

	//武器骨骼网格体组件
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//能力系统组件
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//属性集组件
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//初始化角色信息
	virtual void InitAbilityActorInfo();
};
