#include <thread>
#include <Painter.h>
#include "Tank.h"
#include "PainterTanks.h"
#include "Brain.h"

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
	Tank tank(Tank::Type::User1);
	Tank oppTank(Tank::Type::EnemySimple);
	Brain brain;
	
	auto start = std::chrono::system_clock::now();
	PainterTanks painter;
	painter.hideCursor();
	
	painter.drawHead(" T A N K S ");
	int ch = getch();
	painter.setScreenSize();
	
	painter.clearScreen();
	int w = painter.getWinWidth();
	int h = painter.getWinHeight();

	const std::string gameOverStr = " GAME OVER! press Q - to quite! * - to repeate";
	noecho();
	tank.setXY(10, 15);
	oppTank.setXY(5, 10);
	while(true) {
		if (ch == 'q')
			break;
		
		while (true) {
			bool wasStopped = false;
			int w = painter.getWinWidth();
			int h = painter.getWinHeight();
			painter.setScreenSize();
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
					case rlutil::KEY_SPACE:
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

			
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = end-start;
			if (diff.count() > 0.1) {
				start = std::chrono::system_clock::now();
				diff.zero();
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



