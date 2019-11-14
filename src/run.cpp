#include <thread>
#include <Painter.h>
#include "Tank.h"
#include "PainterTanks.h"

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
	auto start = std::chrono::system_clock::now();
	PainterTanks painter;
	painter.hideCursor();
	
	painter.drawHead(" T A N K S ");
	int ch = getch();
	
	painter.clearScreen();
	
	const std::string gameOverStr = " GAME OVER! press Q - to quite! * - to repeate";
	noecho();
	tank.setXY(10, 15);
	while(true) {
		if (ch == 'q')
			break;
		
		while (true) {
			bool wasStopped = false;
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
				getch();
			}
			painter.drawTank(tank);
			
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

					default:
						break;
				}
			}
			if (ch == 'q')
				break;
			
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = end-start;
			if (diff.count() > 0.1) {
				start = std::chrono::system_clock::now();
				diff.zero();
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



