


#include "UI/Widget/AuraUserWidget.h"

//设置控件控制器函数
void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
