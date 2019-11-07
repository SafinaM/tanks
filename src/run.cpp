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
	Tank tank;
	tank.print();
	auto start = std::chrono::system_clock::now();
	PainterTanks painter;
	painter.hideCursor();
	
	painter.drawHead(" T A N K S ");
	int ch = getch();
	
	painter.clearScreen();
	
	const std::string gameOverStr = " GAME OVER! press Q - to quite! * - to repeate";
	noecho();
	
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
			tank.getPoints();
			painter.drawTank(tank, true, ' ');
			
			if (kbhit()) {
				ch = rlutil::getkey();
				switch (ch) {
					case 'w':
					case rlutil::KEY_UP:
					case rlutil::KEY_SPACE:
						break;
					case 'a':
					case rlutil::KEY_LEFT:
						
						break;
					case 'd':
					case rlutil::KEY_RIGHT:
						
						break;
					case 's':
					case rlutil::KEY_DOWN:
						
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
			
		} // one figure movement
		
	} // main cycle
	
	echo();
	
	return 0;
}



