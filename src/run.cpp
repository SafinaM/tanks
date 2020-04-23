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
	Tank oppTank(Tank::TankType::EnemySimple);
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
	
	std::cout << w << std::endl;
	std::cout << h << std::endl;
	
	const std::string gameOverStr = " GAME OVER! press Q - to quite! * - to repeate";
	noecho();
	tank.setXY(10, 15);
	oppTank.setXY(5, 10);
	while(true) {
		if (ch == 'q')
			break;
		
		while (true) {
			bool wasStopped = false;
			painter.setScreenSize();
			w = painter.getWinWidth();
			h = painter.getWinHeight();
			
			std::cout << w << std::endl;
			std::cout << h << std::endl;
			
			if (ch == 'p') {
				painter.clearScreen();
				painter.drawHead("Pause! Press any key!");
				wasStopped = true;
				ch = getch();
			}
			if (!painter.isSizeOk()) {
				painter.clearScreen();
				painter.drawHead("SMALL WIN SIZE! Press any key!");
				std::cout << "screen width = " << w << std::endl;
				std::cout << "screen height = " << h << std::endl;
				getch();
				painter.clearScreen();
			}
			painter.drawTank(tank);
			painter.drawTank(oppTank);
			
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
			
			
			if (ch == 'q')
				break;
			
//			Action action = brain.chooseAction(oppTank);
//			if (action == Action::ChooseDirection) {
//				direction = brain.chooseDirection();
//			} else

			auto tankTimeStampEnd = clock::system_clock::now();
			auto ammoTimeStampEnd = clock::system_clock::now();
			std::chrono::duration<double> tankDiff = tankTimeStampEnd - tankTimeStampStart;
			std::chrono::duration<double> ammoDiff = ammoTimeStampEnd - ammoTimeStampStart;
			
			painter.drawAmmo(tank, BackgroundColor::BC_YELLOW);
			if (ammoDiff.count() > tank.getAmmoSpeed()) {
				painter.eraseAmmo(tank);
				tank.moveAmmo();
				ammoTimeStampStart = clock::system_clock::now();
				ammoDiff.zero();
			}
			
			if (tankDiff.count() > oppTank.getTankSpeed()) {
				tankTimeStampStart = clock::system_clock::now();
				tankDiff.zero();
				Direction direction = brain.chooseDirection();
				if (direction == Direction::Down || direction == Direction::Right) {
					painter.eraseTank(oppTank);
					oppTank.move(direction);
				}
				break;
				
			}
//			painter.drawTank(tank);
		} // one figure movement
		
	} // main cycle
	
	painter.showCursor();
	painter.clearScreen();
	echo();
	
	return 0;
}



