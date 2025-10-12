

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"


UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class A3_API IEnemyInterface
{
	GENERATED_BODY()

public:
	//是否显示高亮
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
