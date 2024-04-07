#include <iostream>
#include "clsLoginScreen.h"

#include "clsUtil.h"


int main() {

	// clsMainMenuScreen::ShowMainMenue();

	while(true){

		if (!clsLoginScreen::ShowLoginScreen()) {
			break;
	}
   }

	
    
	system("pause>0");
	return 0;

}