


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

//广播初始值
void UOverlayWidgetController::BroadcastInitialValues()
{
	//创建由AttributeSet转换的AuraAttributeSet
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
	//创建由AttributeSet转换的AuraAttributeSet
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	//绑定属性变化回调函数
	//生命值变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	//最大生命值变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	//法力值变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	//最大法力值变化
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	//绑定消息控件行委托
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			//遍历所有标签
			for (const FGameplayTag& Tag : AssetTags)
			{
				//创建一个名为"Message"的标签
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));	/*注：此处写死了父标签*/
				//检查Tag是否是"Message"子标签
				if (Tag.MatchesTag(MessageTag))
				{
					//从MessageWidgetDataTable根据Tag获取对应的UI控件行
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					//广播该行的数据
					MessageWidgetRow.Broadcast(*Row);
				}
			}
		}	
	);
}
