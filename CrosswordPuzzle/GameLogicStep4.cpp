
#include "ScreenOutput.h"

#include "GameLogicStep4.h"

GameLogicStep4::GameLogicStep4(GameDataInterface *gameDataInterface)
{
	mGameDataInterface = gameDataInterface;
}

bool GameLogicStep4::checkContinue()
{
	return ScreenOutput::printContinue();
}