

#pragma once

#include "CoreMinimal.h"
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

	/*----------敌人接口----------*/
	//获取角色等级
	virtual int32 GetPlayerLevel() override;
	/*--------------------------*/
	
	/*----------动态多播委托----------*/
	//生命值
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	//最大生命值
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	/*------------------------------*/
	
protected:
	virtual void BeginPlay() override;

	//初始化角色信息
	virtual void InitAbilityActorInfo() override;
	
	//角色等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	//控件组件(血条)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
