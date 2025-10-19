


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

//广播初始值
void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//将属性集转换为Aura属性集
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);	//检查初始化
	//遍历游戏标签和属性的映射表
	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		//广播映射表属性信息
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

//绑定回调到依赖项
void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	//将属性集转换为Aura属性集
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);	//检查初始化
	//遍历游戏标签和属性的映射表
	for (auto& Pair : AS->TagsToAttributes)
	{
		//属性变化时绑定属性信息委托
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		}
		);
	}
}

//广播属性信息
void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	//创建属性信息并将游戏标签与属性信息绑定
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	//将属性值赋给属性信息
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	//广播属性信息委托
	AttributeInfoDelegate.Broadcast(Info);
}
