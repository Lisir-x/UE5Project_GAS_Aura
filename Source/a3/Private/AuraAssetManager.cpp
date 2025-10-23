


#include "AuraAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AuraGameplayTags.h"

//静态获取资产管理函数
UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);	//检查初始化
	//从引擎中获取资产管理并转换成Aura资产管理
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

//开始初始化加载
void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//初始化原生游戏标签
	FAuraGameplayTags::InitializeNativeGameplayTags();
	
	//初始化全局数据
	UAbilitySystemGlobals::Get().InitGlobalData();
}
