

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class A3_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	//静态获取资产管理函数
	static UAuraAssetManager& Get();

protected:
	//开始初始化加载
	virtual void StartInitialLoading() override;
};
