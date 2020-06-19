#include "Map.h"
#include "Stages.h"

#include <Painter.h>

int main() {
	
	Map map(stageTest);
	map.debugPrint(map.buffer);
	
	map.buildWave(Point(11, 3), Point(5, 17));
	
	return 0;
}

