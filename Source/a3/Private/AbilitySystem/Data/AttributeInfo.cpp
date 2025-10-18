


#include "AbilitySystem/Data/AttributeInfo.h"

//将游戏标签与属性信息绑定
FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	//遍历属性信息数组以寻找与给定游戏标签完全匹配的属性信息
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		//找到匹配项后立即返回
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	//如果没有找到匹配的属性信息，则记录一个错误日志，并返回空的属性信息对象
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."),
			*AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
