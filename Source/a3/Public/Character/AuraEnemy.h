

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class A3_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	/*----------敌人接口----------*/
	//显示高亮
	virtual void HighlightActor() override;
	//取消高亮
	virtual void UnHighlightActor() override;
	/*--------------------------*/

	/*----------战斗接口----------*/
	//获取角色等级
	virtual int32 GetPlayerLevel() override;
	//死亡逻辑
	virtual void Die() override;
	/*--------------------------*/
	
	/*----------动态多播委托----------*/
	//生命值
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	//最大生命值
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	/*------------------------------*/

	//受击反应标签变化回调函数
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	//是否处于受击反应状态
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	//基础移动速度
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 250.f;

	//生命周期
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;
	
protected:
	virtual void BeginPlay() override;
	//初始化角色信息
	virtual void InitAbilityActorInfo() override;
	//初始化默认属性
	virtual void InitializeDefaultAttributes() const override;
	
	//角色等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	//角色职业类(默认为战士)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	//控件组件(血条)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
