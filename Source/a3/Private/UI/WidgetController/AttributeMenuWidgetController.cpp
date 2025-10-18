


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
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
		//创建属性信息并将映射表键的游戏标签与属性信息绑定
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		//将映射表值中的属性值赋给属性信息
		Info.AttributeValue = Pair.Value().GetNumericValue(AuraAttributeSet);
		//广播属性信息委托
		AttributeInfoDelegate.Broadcast(Info);
	}
}

//绑定回调到依赖项
void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{

}
