#include <filesystem>
#include <iostream>
#include <memory>
#include "routing.h"

using namespace http;

int main() {
	Player player(0,0);
	Routing r;
	r.Run(player);

	return 0;
}