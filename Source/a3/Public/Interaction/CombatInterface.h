

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UAnimMontage;

/**
 * 
 */
class A3_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//获取等级
	virtual int32 GetPlayerLevel();
	//获取战斗插槽的位置
	virtual FVector GetCombatSocketLocation();

	//面向目标(蓝图可实现、可调用)
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	/*----------动画蒙太奇----------*/
	//受击反应
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();
	/*----------------------------*/

	//死亡逻辑
	virtual void Die() = 0;
};
