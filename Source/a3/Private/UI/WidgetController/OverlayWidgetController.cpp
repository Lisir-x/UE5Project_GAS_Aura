


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

//广播初始值
void UOverlayWidgetController::BroadcastInitialValues()
{
	//创建由 AttributeSet 转换的 AuraAttributeSet
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	//广播当前生命值和最大生命值
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	//广播当前法力值和最大法力值
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

//绑定回调到依赖项
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	//创建由 AttributeSet 转换的 AuraAttributeSet
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	//绑定属性回调函数
	//生命值变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	//最大生命值变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	//法力值变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	//最大法力值变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

//生命值回调函数
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Date) const
{
	OnHealthChanged.Broadcast(Date.NewValue);
}

//最大生命值回调函数
void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Date) const
{
	OnMaxHealthChanged.Broadcast(Date.NewValue);
}

//法力值回调函数
void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Date) const
{
	OnManaChanged.Broadcast(Date.NewValue);
}

//最大法力值回调函数
void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Date) const
{
	OnMaxManaChanged.Broadcast(Date.NewValue);
}
