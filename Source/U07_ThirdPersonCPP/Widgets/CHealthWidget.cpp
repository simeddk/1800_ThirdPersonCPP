#include "CHealthWidget.h"
#include "Components/ProgressBar.h"

void UCHealthWidget::UpdateHealth_Implementation(float InCurrentHealth, float InMaxHealth)
{
	HealthBar->SetPercent(InCurrentHealth / InMaxHealth);
}