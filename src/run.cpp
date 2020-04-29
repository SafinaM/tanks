#include <Painter.h>
#include "Tank.h"
#include "PainterTanks.h"
#include "Brain.h"

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

void shoot(Tank& tank) {
	if (kbhit()) {
		char ch = rlutil::getkey();
		if (ch == rlutil::KEY_SPACE) {
			tank.shoot();
		}
	}
}

int main() {
	
	using clock = std::chrono::high_resolution_clock;
	
	Tank tank(Tank::TankType::User1);
	constexpr uint32_t numberOfOpponents = 10;
	std::vector<Tank> opponents;
	opponents.reserve(numberOfOpponents);
	for (uint32_t i = 0; i < numberOfOpponents; ++i) {
		Tank oppTank(Tank::TankType::EnemySimple);
		opponents.emplace_back(std::move(oppTank));
	}
	Brain brain;
	
	auto tankTimeStampStart = clock::system_clock::now();
	auto ammoTimeStampStart = clock::system_clock::now();
	PainterTanks painter;
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
	tank.setXY(10, 15);
	
	for (uint32_t i = 0; i < numberOfOpponents; ++i) {
		opponents[i].setXY(5 + i, 10 + i);
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
						tank.move(Direction::Up);
						break;
					case 's':
					case rlutil::KEY_DOWN:
						tank.move(Direction::Down);
						break;
					case 'a':
					case rlutil::KEY_LEFT:
						tank.move(Direction::Left);
						break;
					case 'd':
					case rlutil::KEY_RIGHT:
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
			for (uint32_t i = 0; i < numberOfOpponents; ++i) {
				tankDiffs.emplace_back(tankTimeStampEnd - tankTimeStampStart);
			}
			std::chrono::duration<double> ammoDiff = ammoTimeStampEnd - ammoTimeStampStart;
			
			painter.drawAmmo(tank, BackgroundColor::BC_YELLOW);
			if (ammoDiff.count() > tank.getAmmoSpeed()) {
				painter.eraseAmmo(tank);
				tank.moveAmmo();
				ammoTimeStampStart = clock::system_clock::now();
				ammoDiff.zero();
			}
			
			for (uint32_t i = 0; i < numberOfOpponents; ++i) {
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
					Direction direction = brain.chooseDirection();
					if (direction == Direction::Down || direction == Direction::Right) {
						painter.eraseTank(opponents[i]);
						opponents[i].move(direction);
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



