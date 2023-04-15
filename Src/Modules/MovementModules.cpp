#include "MovementModules.h"
#include "../Memory.hpp"
#include "../Gui.h"

#include <iostream>
#include <thread>

void MovementModules::StartMovementModules() noexcept {
	while (Gui::IsRunning) {
		StartBhopModule();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void MovementModules::StartBhopModule() noexcept {
	
}