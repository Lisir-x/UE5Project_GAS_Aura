


#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);	//检查初始化
	//从引擎中获取资产管理并转换成Aura资产管理
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//初始化原生游戏标签
	FAuraGameplayTags::InitializeNativeGameplayTags();
}
