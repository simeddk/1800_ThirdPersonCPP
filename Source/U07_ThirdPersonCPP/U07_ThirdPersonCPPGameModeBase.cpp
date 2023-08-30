#include "U07_ThirdPersonCPPGameModeBase.h"
#include "Global.h"
#include "GameFramework/HUD.h"

AU07_ThirdPersonCPPGameModeBase::AU07_ThirdPersonCPPGameModeBase()
{
	CHelpers::GetClass(&DefaultPawnClass, "/Game/Player/BP_CPlayer");
	CHelpers::GetClass(&HUDClass, "/Game/BP_CHUD");
}