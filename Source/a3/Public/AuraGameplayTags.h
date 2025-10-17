

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * 这是一个包含原生游戏标签的单例
 * 标签由C++内部创建并可在C++内部使用，也可在编辑器和蓝图中使用
 */

struct FAuraGameplayTags
{
public:
	//静态获取游戏标签实例
	static  const FAuraGameplayTags& Get() { return GameplayTags; }
	//初始化原生游戏标签
	static void InitializeNativeGameplayTags();

	//声明游戏标签变量
	FGameplayTag Attributes_Secondary_Armor;

protected:
	
private:
	//游戏标签实例
	static FAuraGameplayTags GameplayTags;
	
};
