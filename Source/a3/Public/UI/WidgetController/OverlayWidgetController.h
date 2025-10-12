

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

//创建动态多播委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

UCLASS(BlueprintType, Blueprintable)
class A3_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	//广播初始值
	virtual void BroadcastInitialValues() override;
	//绑定回调到依赖项
	virtual void BindCallbacksToDependencies() override;
	
	/*----------动态多播委托----------*/
	//生命值
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	//最大生命值
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	//法力值
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	//最大法力值
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
	/*------------------------------*/

protected:
	/*----------属性回调函数----------*/
	//生命值
	void HealthChanged(const FOnAttributeChangeData& Date) const;
	//最大生命值
	void MaxHealthChanged(const FOnAttributeChangeData& Date) const;
	//法力值
	void ManaChanged(const FOnAttributeChangeData& Date) const;
	//最大法力值
	void MaxManaChanged(const FOnAttributeChangeData& Date) const;
	/*------------------------------*/
};
