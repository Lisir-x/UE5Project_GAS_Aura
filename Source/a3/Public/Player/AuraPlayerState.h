

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
	//属性复制函数
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//获取能力系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//获取属性集组件
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	//获取角色等级
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	
protected:
	//能力系统组件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//属性集组件
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
private:
	//角色等级
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	/*----------副本通知函数----------*/
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	/*------------------------------*/
};
