#include <Painter.h>
#include "Tank.h"
#include "PainterLocal.h"
#include "Brain.h"
#include "Map.h"
#include "Stages.h"

#include <thread>
#include <future>

// TODO noecho for windows
void noecho() {
	struct termios dt;
	tcgetattr(STDIN_FILENO, &dt);
	dt.c_lflag    &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &dt);
}

void echo() {
	struct termios dt;
	tcgetattr(STDIN_FILENO, &dt);
	dt.c_lflag    |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &dt);
}

int main() {
	
	using clock = std::chrono::high_resolution_clock;
	
	Tank tank(Tank::TankType::User1);
	constexpr uint32_t numberOfOpponents = 3;
	std::vector<Tank> opponents;
	opponents.reserve(numberOfOpponents);
	std::vector<Direction> directions;
	directions.reserve(numberOfOpponents);
	
	Brain brain;
	Map map(stageTest);
	
	for (uint32_t i = 0; i < numberOfOpponents; ++i) {
		Tank oppTank(Tank::TankType::EnemySimple);
		opponents.emplace_back(std::move(oppTank));
		// initialize directions of tanks
		directions[i] = brain.chooseDirection();
	}
	
	
	const auto testOriginX = 10;
	const auto testOriginY = 10;
	const auto delta = 5;
	
	auto tankTimeStampStart = clock::system_clock::now();
	auto ammoTimeStampStart = clock::system_clock::now();
	std::vector<clock::time_point> ammoTimeStampStarts;
	ammoTimeStampStarts.reserve(numberOfOpponents);
	for (uint32_t i = 0; i < numberOfOpponents; ++i) {
		ammoTimeStampStarts.push_back(clock::system_clock::now());
	}
	
	PainterLocal painter;
	painter.hideCursor();
	
	painter.drawHead(" T A N K S ");
	int ch = getch();
	painter.setScreenSize();
	painter.clearScreen();
	int w = painter.getWinWidth();
	int h = painter.getWinHeight();
	
//	std::cout << w << std::endl;
//	std::cout << h << std::endl;
	
	const std::string gameOverStr = " GAME OVER! press Q - to quite! * - to repeate";
	noecho();
	
	tank.setXY(testOriginX + delta - 2, testOriginY + delta -1 );
	painter.setXY(testOriginX, testOriginY);
	
	painter.clearScreen();
	painter.drawMap(map);
	
	for (uint32_t i = 0; i < numberOfOpponents; ++i) {
		opponents[i].setXY(testOriginX + i, testOriginY + i);
	}
	while(true) {
		if (ch == 'q')
			break;
		while (true) {
			bool wasStopped = false;
			painter.setScreenSize();
			w = painter.getWinWidth();
			h = painter.getWinHeight();
			
//			std::cout << w << std::endl;
//			std::cout << h << std::endl;
			if (ch == 'p') {
				painter.clearScreen();
				painter.drawHead("Pause! Press any key!");
				wasStopped = true;
				ch = getch();
			}
			if (!painter.isSizeOk()) {
				painter.clearScreen();
				painter.drawHead("SMALL WIN SIZE! Press any key!");
//				std::cout << "screen width = " << w << std::endl;
//				std::cout << "screen height = " << h << std::endl;
				getch();
				painter.clearScreen();
			}
			painter.drawTank(tank);
			for (uint32_t i = 0; i < numberOfOpponents; ++i) {
				if (opponents[i].isAlive)
					painter.drawTank(opponents[i]);
			}
			
			if (kbhit()) {
				painter.eraseTank(tank);
				ch = rlutil::getkey();
				switch (ch) {
					case rlutil::KEY_SPACE:
						tank.shoot();
						break;
					case 'w':
					case rlutil::KEY_UP:
						tank.rotate(Direction::Up);
						if (map.allowMove(Direction::Up, tank))
							tank.move(Direction::Up);
						break;
					case 's':
					case rlutil::KEY_DOWN:
						tank.rotate(Direction::Down);
						if (map.allowMove(Direction::Down, tank))
							tank.move(Direction::Down);
						break;
					case 'a':
					case rlutil::KEY_LEFT:
						tank.rotate(Direction::Left);
						if (map.allowMove(Direction::Left, tank))
							tank.move(Direction::Left);
						break;
					case 'd':
					case rlutil::KEY_RIGHT:
						tank.rotate(Direction::Right);
						if (map.allowMove(Direction::Right, tank))
							tank.move(Direction::Right);
						break;
					default:
						break;
				}
			}
			
			if (ch == 'q') {
				break;
			}
			
			tank.verifyIntersections(opponents);
			
			auto tankTimeStampEnd = clock::system_clock::now();
			auto ammoTimeStampEnd = clock::system_clock::now();
			std::vector<std::chrono::duration<double>> tankDiffs;
			std::vector<std::chrono::duration<double>> ammoDiffs;
			
			for (uint32_t i = 0; i < numberOfOpponents; ++i) {
				tankDiffs.push_back(tankTimeStampEnd - tankTimeStampStart);
				ammoDiffs.push_back(ammoTimeStampEnd - ammoTimeStampStarts[i]);
			}
			std::chrono::duration<double> ammoUserTankDiff = ammoTimeStampEnd - ammoTimeStampStart;
			
			painter.drawAmmo(tank, BackgroundColor::BC_YELLOW);
			if (ammoUserTankDiff.count() > tank.getAmmoSpeed()) {
				painter.eraseAmmo(tank);
				map.crossWithAmmo(tank);
				tank.moveAmmo();
				ammoTimeStampStart = clock::system_clock::now();
				ammoUserTankDiff.zero();
			}
			
//			brain.chooseActions(opponents);
			for (uint32_t i = 0; i < numberOfOpponents; ++i) {
				// we draw ammo even if tank is not alive
				painter.drawAmmo(opponents[i], BackgroundColor::BC_YELLOW);
				if (ammoDiffs[i].count() > opponents[i].getAmmoSpeed()) {
					painter.eraseAmmo(opponents[i]);
					map.crossWithAmmo(opponents[i]);
					opponents[i].moveAmmo();
					ammoTimeStampStarts[i] = clock::system_clock::now();
					ammoDiffs[i].zero();
					painter.drawMap(map);
				}
				if (!opponents[i].isAlive) {
					if (!opponents[i].isErased) {
						opponents[i].isErased = true;
						painter.eraseTank(opponents[i]);
					}
					continue;
				}
				if (tankDiffs[i].count() > opponents[i].getTankSpeed()) {
					tankTimeStampStart = clock::system_clock::now();
					tankDiffs[i].zero();
					painter.eraseTank(opponents[i]);
					
					if (map.allowMove(directions[i], opponents[i]))
						opponents[i].move(directions[i]);
					else {
						Action action = brain.chooseAction(tank);
						switch (action) {
							case Action::Move:
								continue;
							case Action::Shoot:
								if (brain.checkShoot(ShootProb::HighProb)) {
									opponents[i].shoot();
								}
								break;
							case Action::ChooseDirection:
								directions[i] = brain.chooseDirection();
								break;
						}
					}
					// shoot with high probability
					if (brain.checkShoot(ShootProb::AverageProb)) {
						opponents[i].shoot();
					}
				}
			}
			break;
//			painter.drawTank(tank);
		} // one figure movement
		
	} // main cycle
	
	painter.showCursor();
	painter.clearScreen();
	echo();
	
	return 0;
}



