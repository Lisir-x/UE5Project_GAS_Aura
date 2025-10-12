

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class A3_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();

	//获取能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//获取属性集组件
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	
protected:
	//能力系统组件
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//属性集组件
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
