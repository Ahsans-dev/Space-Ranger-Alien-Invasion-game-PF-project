#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;

////////////moeen updation
int boss_bullets[5][2] = { 0 };
int boss_health = 20;

void checkPlayerCollision();
void checkBossCollision();

string name;

// Constants for map dimensions
const int ROW = 30;
const int COL = 40;

int dis = 0;
int score = 0;
int lives = 3;
int level = 2;

// For time
int MIN = 3;
int SEC = 0;
int MSEC = 0;

// Spaceship coordinates
int spaceship_x = COL / 2;
int spaceship_y = ROW - 3;

// Map grid
char map[ROW][COL];

int enemy_x[2], enemy_y[2], enemy_direction[2];
bool enemy_alive[2];

int boss_x = COL / 2; // Boss's horizontal position
int boss_y = 3; // Boss's vertical position
int boss_direction = 1; // 1 for moving right, -1 for moving left

// Initialize the map with empty spaces
void initMap();
// Timer function to update time left
void timer();
// Draw boundaries for the game map
void mapBoundary();
// Start screen and user selection
int start();
// Display the main menu
int menu();
// Draw the game map
void drawMap();
// Add a random star to the map
void stars(int count);
// Move stars down the map
void moveStars();
// Add a random asteroid to the map
void asteroid(int count);
// Move asteroids down the map
void moveAsteroids();
// Draw the spaceship on the map
void drawSpaceship();
// Remove the spaceship from its current position
void removeSpaceship();
// Handle spaceship movement based on user input
void moveSpaceship(char input);
// Main game logic
void enemyLevel(int time);
// Main game logic for boss level
void bossLevel(int time);
// Handle user shooting
void shoot();
// Handle collision
void collisionAsteroid(int i, int j);
void collisionStar(int i, int j);

// Enemy functions
void spawnEnemy();
void moveEnemyShips();
void enemybullets();
void moveEnemyBullets();
void enemyRespawn();
void bulletsCollisions();

// Game over screen
void gameOver(int a);
void showInstructions();
void playGame();

void spawnBoss();
void moveBoss();
void bossShoot();
void moveBossBullets();

void saveScore(const string name, int score);
void displayScore();

int main() {
	srand(time(0)); ////moeen updation
	playGame();
	system("pause");
	return 0;
}

void playGame() {
	system("cls");
	int time = 200;
	level = 1;
	switch (start()) {
	case 1:
		do {
			lives = 3;
			system("cls");
			if (level % 2 != 0) {
				enemyLevel(time);
			}
			else {
				bossLevel(time);
				time -= 30;
			}
			level++;
		} while (true);
		break;
	case 2:
		system("cls");
		displayScore();
		_getch();
		system("cls");
		menu();
		break;
	case 3:
		showInstructions();
		break;
	case 4:
		system("cls");
		cout << right << setw(70) << "============================\n";
		cout << right << setw(62) << "ABOUT DEVELOPERS\n";
		cout << right << setw(70) << "============================\n";
		cout << right << setw(62) << "Developed by:\n";
		cout << right << setw(62) << "1. Ahsan Shafqat\n";
		cout << right << setw(62) << "2. Muhammad Moeen\n";
		cout << right << setw(70) << "============================\n";
		cout << "\nPress any key to return to the menu.";
		_getch();
		system("cls");
		menu();
		break;
	default:
		break;
	}
}
int start() {
	char selection;
	cout << right << setw(70) << "============================\n";
	cout << right << setw(62) << "Space Ranger\n";
	cout << right << setw(70) << "============================\n";
	cout << right << setw(68) << "Aliens are on their way\n" << right << setw(68) << " to invade Earth-will you\n" << right << setw(68) << "rises as our Ranger &\n" << right << setw(68) << "stand as the last hope \n" << right << setw(68) << "to save Humanity?   \n";
	cout << "\n\n" << right << setw(70) << "Enter Yes or No (y/n) : ";
	cin >> selection;
	if ((selection == 'Y') || (selection == 'y')) {
		system("cls");
		cout << "Nice Choice Ranger Enter Your Good name : ";
		cin >> name;
		system("cls");
		return menu();
	}
	else if ((selection == 'N') || (selection == 'n')) {
		system("cls");
		return 0;
	}
	else {
		cout << "\nInvalid Choice\n";
		start();
	}
}

void showInstructions() {
	system("cls");
	cout << "=================================================\n";
	cout << "INSTRUCTIONS\n";
	cout << "=================================================\n";
	cout << "1. Use 'A' or 'a' to move left.\n";
	cout << "2. Use 'D' or 'd' to move right.\n";
	cout << "3. Use 'W' or 'w' to move up.\n";
	cout << "4. Use 'S' or 's' to move down.\n";
	cout << "5. Use 'J' or 'j' to jump.\n";
	cout << "6. Press 'Space' to shoot.\n";
	cout << "7. Avoid asteroids and enemy bullets.\n";
	cout << "8. Shoot enemies and collect stars for points.\n";
	cout << "9. Defeat the boss to advance to the next level.\n";
	cout << "10. Press 'e' to exit the instructions.\n";
	cout << "==================================================\n";
	cout << "Press any key to return to the menu.";
	_getch();
	system("cls");
	menu();
}

int menu() {
	int choice;
	cout << right << setw(70) << "============================\n";
	cout << right << setw(62) << "MENU     \n";
	cout << right << setw(70) << "============================\n";
	cout << right << setw(70) << "1.Start Game      \n";
	cout << right << setw(70) << "2.Rangerboard     \n";
	cout << right << setw(70) << "3.Instructions    \n";
	cout << right << setw(70) << "4.About Developers\n";
	cout << right << setw(70) << "5.Exit           \n\n";
	cout << right << setw(45) << "So, " << name << " what is your choice (1-5) : ";
	cin >> choice;
	if (choice < 1 || choice > 5) {
		cout << "\nInvalid Choice\n";
		menu();
	}
	else if (choice == 2) {
		system("cls");
		displayScore();
		_getch();
		system("cls");
		menu();
	}
	else if (choice == 5) {
		system("cls");
		cout << right << setw(70) << "============================\n";
		cout << right << setw(62) << "THANK YOU\n";
		cout << right << setw(70) << "============================\n";
		cout << right << setw(62) << "Developed by:\n";
		cout << right << setw(62) << "1. Ahsan Shafqat\n";
		cout << right << setw(62) << "2. Muhammad Moeen\n";
		cout << right << setw(70) << "============================\n";
		cout << right << setw(70) << "Good Bye\n";
		exit(0);
	}
	else if (choice == 3) {
		showInstructions();
	}
	else if (choice == 4) {
		system("cls");
		cout << right << setw(70) << "============================\n";
		cout << right << setw(62) << "ABOUT DEVELOPERS\n";
		cout << right << setw(70) << "============================\n";
		cout << right << setw(62) << "Developed by:\n";
		cout << right << setw(62) << "1. Ahsan Shafqat\n";
		cout << right << setw(62) << "2. Muhammad Moeen\n";
		cout << right << setw(70) << "============================\n";
		cout << "\nPress any key to return to the menu.";
		_getch();
		system("cls");
		menu();
	}
	else {
		return choice;
	}

}

void enemyLevel(int time) {
	initMap();
	spawnEnemy(); // Initialize enemy ships
	int count = 0;
	cout << right << setw(70) << "============================\n";
	cout << right << setw(62) << "Space Ranger\n";
	cout << right << setw(70) << "============================\n";
	cout << setw(62) << "Enemy Level\n";
	cout << setw(59) << "Level: " << level << endl;
	cout << setw(60) << "Lives: 3" << endl;
	cout << setw(67) << "Distance to cover: 2000m" << endl;
	cout << setw(70) << "============================\n";
	this_thread::sleep_for(chrono::milliseconds(2000));
	system("cls");
	while (true) {
		if (dis >= 2000) {
			cout << right << setw(70) << "============================\n";
			cout << right << setw(62) << "CONGRATULATIONS\n";
			cout << right << setw(70) << "============================\n";
			cout << right << setw(60) << "Your Score: " << score << endl;
			cout << right << setw(60) << "Level Reached: " << level << endl;
			cout << right << setw(70) << "============================\n";
			this_thread::sleep_for(chrono::milliseconds(2000));
			return;
		}
		if (lives == 0) {
			gameOver(1);
		}
		count++;
		asteroid(count);
		moveAsteroids();
		stars(count);
		moveStars();
		moveEnemyShips();
		drawSpaceship();
		drawMap();
		shoot();
		enemybullets();
		moveEnemyBullets();
		enemyRespawn();
		bulletsCollisions();
		if (_kbhit()) {
			char key = _getch();
			moveSpaceship(key);
		}
		this_thread::sleep_for(chrono::milliseconds(time)); // Smooth update
		system("cls");
		dis += 5;
	}
}



void initMap() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			map[i][j] = ' ';
		}
	}
}

void mapBoundary() {
	for (int i = 0; i < ROW; ++i) {
		map[i][0] = '|';
		map[i][COL - 1] = '|';
	}
	for (int j = 0; j < COL; ++j) {
		map[0][j] = '=';
		map[ROW - 1][j] = '=';
	}
}

void timer() {
	cout << "Time left: " << MIN << "m " << SEC << "s " << endl;
	if (MSEC == 0) {
		if (SEC == 0) {
			if (MIN == 0) return;
			MIN -= 1;
			SEC = 59;
			MSEC = 800;
		}
		else {
			SEC -= 1;
			MSEC = 800;
		}
	}
	else {
		MSEC -= 200;
		if (MSEC < 0) {
			MSEC = 0;
		}
	}
	if (MIN == 0 && SEC == 1 && MSEC == 200) {
		system("cls");
		cout << "time over" << endl;
		this_thread::sleep_for(chrono::milliseconds(300));
		gameOver(1);
	}
}

void drawMap() {
	mapBoundary();
	cout << "Name: " << name << endl;
	cout << "Score: " << score << "  Lives: " << lives << endl;
	cout << "Distance: " << dis << endl;
	timer();
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void stars(int count) {
	if (count % 6 == 0) {
		int x = rand() % (COL - 2) + 1;
		map[1][x] = '*';
	}
}

void moveStars() {
	for (int i = ROW - 2; i > 0; i--) {
		for (int j = 1; j < COL - 1; j++) {
			if (map[i][j] == '*') {
				map[i][j] = ' ';
				if (i + 1 < ROW - 1) {
					collisionStar(i, j);
					map[i + 1][j] = '*';
				}
			}
		}
	}
}

void asteroid(int count) {
	if (count % 4 == 0) {
		int x = rand() % (COL - 2) + 1;
		map[1][x] = '#';
	}
}

void moveAsteroids() {
	for (int i = ROW - 2; i > 0; i--) {
		for (int j = 1; j < COL - 1; j++) {
			if (map[i][j] == '#') {
				map[i][j] = ' ';
				if (i + 1 < ROW - 1) {
					collisionAsteroid(i, j);
					map[i + 1][j] = '#';
				}
			}
		}
	}
}

void drawSpaceship() {
	map[spaceship_y][spaceship_x - 1] = '<';
	map[spaceship_y][spaceship_x] = '^';
	map[spaceship_y][spaceship_x + 1] = '>';
}

void removeSpaceship() {
	map[spaceship_y][spaceship_x - 1] = ' ';
	map[spaceship_y][spaceship_x] = ' ';
	map[spaceship_y][spaceship_x + 1] = ' ';
}

void moveSpaceship(char move) {
	if ((move == 'a' || move == 'A') && spaceship_x > 2) {
		removeSpaceship();
		spaceship_x--;
	}
	else if ((move == 'd' || move == 'D') && spaceship_x < COL - 3) {
		removeSpaceship();
		spaceship_x++;
	}
	else if ((move == 'w' || move == 'W') && spaceship_y > ROW - 11) {
		removeSpaceship();
		spaceship_y--;
	}
	else if ((move == 's' || move == 'S') && spaceship_y < ROW - 2) {
		removeSpaceship();
		spaceship_y++;
	}
	else if (move == 32) {
		map[spaceship_y - 1][spaceship_x] = '|';
	}
	else if ((move == 'j' || move == 'J') && spaceship_y > ROW - 11) {
		removeSpaceship();
		spaceship_y = spaceship_y - 2;
	}
}

void shoot() {
	for (int i = 1; i < ROW - 1; i++) {
		for (int j = 1; j < COL - 1; j++) {
			if (map[i][j] == '|') {
				map[i][j] = ' ';
				if (i - 1 > 0) {
					if (map[i - 1][j] == 'E')
					{
						map[i - 1][j] = ' ';
						score += 30;
					}
					else if (map[i - 1][j] == 'B')
					{
						boss_health = boss_health - 10;
					}
					else if (map[i - 1][j] == '!') {
						map[i - 1][j] = ' ';
					}
					else if (map[i - 1][j] == '*')
					{
						map[i - 1][j] = ' ';
						score += 20;
					}
					else if (map[i - 1][j] == '#')
					{
						map[i - 1][j] = ' ';
						score += 10;
					}
					else {
						map[i - 1][j] = '|';
					}
				}
			}
		}
	}
}

void collisionAsteroid(int i, int j) {
	if (map[i + 1][j] != ' ') {
		if ((map[i + 1][j] == '<' || map[i + 1][j] == '^' || map[i + 1][j] == '>') && (spaceship_x == j || spaceship_x - 1 == j || spaceship_x + 1 == j)) {
			lives--;
		}
	}
	if (lives == -1)
	{
		gameOver(1);
	}
}

void collisionStar(int i, int j) {
	if (map[i + 1][j] != ' ') {
		if ((map[i + 1][j] == '<' || map[i + 1][j] == '^' || map[i + 1][j] == '>') && (spaceship_x == j || spaceship_x - 1 == j || spaceship_x + 1 == j)) {
			score = score + 20;
		}
	}
}

void spawnEnemy() {
	for (int i = 0; i < 2; ++i) {
		if (!enemy_alive[i]) {
			enemy_x[i] = rand() % (COL - 4) + 2; // Random x position
			enemy_y[i] = rand() % 5 + 1; // Random y position in the first 5 rows
			enemy_direction[i] = (rand() % 2 == 0) ? 1 : -1; // Random direction
			enemy_alive[i] = true;
		}
	}
}

void moveEnemyShips() {
	for (int i = 0; i < 2; ++i) {
		if (enemy_alive[i]) {
			// Clear previous position
			map[enemy_y[i]][enemy_x[i]] = ' ';
			// Update position
			enemy_x[i] += enemy_direction[i];
			// Check boundaries and wrap around
			if (enemy_x[i] <= 1) {
				enemy_x[i] = COL - 2;
			}
			else if (enemy_x[i] >= COL - 2) {
				enemy_x[i] = 1;
			}
			// Draw new position
			map[enemy_y[i]][enemy_x[i]] = 'E';
		}
	}
}

void enemybullets() {
	for (int i = 0; i < 2; ++i) {
		if (enemy_alive[i] && rand() % 20 == 0) { // Adjust the frequency of shooting
			int bulletX = enemy_x[i];
			int bulletY = enemy_y[i] + 1;
			if (bulletY < ROW - 1) {
				map[bulletY][bulletX] = '!'; // '!' represents a bullet
			}
		}
	}
}
void moveEnemyBullets() {
	for (int i = ROW - 2; i > 0; --i) {
		for (int j = 1; j < COL - 1; ++j) {
			if (map[i][j] == '!') {
				map[i][j] = ' ';
				if (i + 1 < ROW - 1) {
					map[i + 1][j] = '!';
				}
			}
		}
	}
}
void enemyRespawn() {
	for (int i = 0; i < 2; ++i) {
		if (enemy_alive[i] && map[enemy_y[i]][enemy_x[i]] != 'E') { // If the ship is destroyed
			enemy_alive[i] = false;
		}
	}
	spawnEnemy(); // Ensure there are always two enemy ships
}
/////////////////moeen updation

void bossLevel(int time) {
	initMap();
	spawnBoss();
	lives = 3; // Set initial lives for the player
	MIN = 2;
	SEC = 0;
	MSEC = 0;
	cout << right << setw(70) << "============================\n";
	cout << right << setw(62) << "Space Ranger\n";
	cout << right << setw(70) << "============================\n";
	cout << setw(62) << "Boss Level\n";
	cout << setw(59) << "Level: " << level << endl;
	cout << setw(60) << "Lives: 3" << endl;
	cout << setw(62) << "kill the boss" << endl;
	cout << setw(70) << "============================\n";
	this_thread::sleep_for(chrono::milliseconds(2000));
	system("cls");
	while (true) {
		drawSpaceship();
		drawMap();
		moveBoss();
		moveBossBullets();
		bossShoot();
		shoot();
		checkBossCollision();
		checkPlayerCollision(); // Check for collisions with boss bullets

		// Display boss health and player lives
		cout << "Boss Health: " << boss_health << endl;

		if (_kbhit()) {
			char key = _getch();
			moveSpaceship(key);
		}

		this_thread::sleep_for(chrono::milliseconds(time));
		system("cls");
		if (boss_health <= 0) {
			cout << right << setw(70) << "============================\n";
			cout << right << setw(62) << "CONGRATULATIONS\n";
			cout << right << setw(70) << "============================\n";
			cout << right << setw(60) << "Your Score: " << score << endl;
			cout << right << setw(60) << "Level Reached: " << level << endl;
			cout << right << setw(70) << "============================\n";
			this_thread::sleep_for(chrono::milliseconds(2000));
			return;
		}
		if (lives <= 0) {
			gameOver(1);
		}
	}
}

void moveBoss() {
	for (int i = boss_y; i < boss_y + 3; ++i) {
		for (int j = boss_x - 2; j <= boss_x + 2; ++j) {
			map[i][j] = ' ';
		}
	}

	boss_x += boss_direction;
	if (boss_x <= 2 || boss_x >= COL - 3) {
		boss_direction = -boss_direction;
	}

	for (int i = boss_y; i < boss_y + 3; ++i) {
		for (int j = boss_x - 2; j <= boss_x + 2; ++j) {
			map[i][j] = 'B';
		}
	}
}

void bossShoot() {
	for (int i = 0; i < 5; ++i) {
		if (boss_bullets[i][1] == 0) {
			boss_bullets[i][0] = boss_x;
			boss_bullets[i][1] = boss_y + 3;
			break;
		}
	}
}

void moveBossBullets() {
	for (int i = 0; i < 5; ++i) {
		if (boss_bullets[i][1] > 0) {
			map[boss_bullets[i][1]][boss_bullets[i][0]] = ' ';
			map[boss_bullets[i][1]][boss_bullets[i][0] + 3] = ' ';
			map[boss_bullets[i][1]][boss_bullets[i][0] - 3] = ' ';
			boss_bullets[i][1]++;

			if (boss_bullets[i][1] >= ROW - 1) {
				boss_bullets[i][1] = 0;
			}
			else {
				map[boss_bullets[i][1]][boss_bullets[i][0]] = '!';
				map[boss_bullets[i][1]][boss_bullets[i][0] + 3] = '!';
				map[boss_bullets[i][1]][boss_bullets[i][0] - 3] = '!';

			}
		}
	}
}

void checkBossCollision() {
	for (int i = boss_y; i < boss_y + 3; ++i) {
		for (int j = boss_x - 2; j <= boss_x + 2; ++j) {
			if (map[i][j] == '|') { // Checking for spaceship bullets
				map[i][j] = ' ';
				boss_health -= 10; // Decrease boss health by 10 for each hit
				score += 25; // Increase score by 25 for each bullet that hits the boss

				if (boss_health <= 0) {
					score += 50; // Additional points for defeating the boss
					gameOver(2);
				}
			}
		}
	}
}

void checkPlayerCollision() {

	for (int i = 0; i < 5; ++i) {
		if (boss_bullets[i][1] > 0 && boss_bullets[i][1] < ROW) {
			// Check if boss bullet collides with the spaceship
			if (boss_bullets[i][0] == spaceship_x && boss_bullets[i][1] == spaceship_y) {
				boss_bullets[i][1] = 0; // Reset bullet position
				lives--; // Decrease player's life by 1
				if (lives <= 0) {
					gameOver(1);
				}
			}
		}
	}
}

void spawnBoss() {
	boss_health = 100;  // Set initial boss health to 100
	boss_x = COL / 2;
	boss_y = 2;
	boss_direction = 1;
}

void bulletsCollisions() {
	// Check for collisions between player's bullets and enemy ships
	for (int i = 1; i < ROW - 1; ++i) {
		for (int j = 1; j < COL - 1; ++j) {
			if (map[i][j] == '|') {
				for (int k = 0; k < 2; ++k) {
					if (enemy_alive[k] && map[enemy_y[k]][enemy_x[k]] == 'E' && enemy_y[k] == i && enemy_x[k] == j) {
						map[i][j] = ' '; // Remove bullet
						map[enemy_y[k]][enemy_x[k]] = ' '; // Remove enemy ship
						enemy_alive[k] = false; // Mark enemy as dead
						score += 20; // Increase score
					}
				}
			}
		}
	}

	// Check for collisions between enemy bullets and player's spaceship
	for (int i = 1; i < ROW - 1; ++i) {
		for (int j = 1; j < COL - 1; ++j) {
			if (map[i][j] == '!') {
				if (map[i + 1][j] == '<' || map[i + 1][j] == '^' || map[i + 1][j] == '>') {
					map[i][j] = ' '; // Remove bullet
					lives--; // Decrease lives111
					if (lives <= 0) {
						gameOver(1); // Trigger game over
					}
				}
			}
		}
	}
}

void gameOver(int a) {
	system("cls");
	if (a == 1) {
		cout << right << setw(70) << "============================\n";
		cout << right << setw(62) << "GAME OVER\n";
		cout << right << setw(70) << "============================\n";
		cout << right << setw(60) << "Your Score: " << score << endl;
		cout << right << setw(60) << "Level Reached: " << level << endl;
		cout << right << setw(70) << "============================\n";
		this_thread::sleep_for(chrono::milliseconds(2000));
		saveScore(name, score);
		menu();
	}
	else if (a == 2) {
		cout << right << setw(70) << "============================\n";
		cout << right << setw(62) << "CONGRATULATIONS\n";
		cout << right << setw(70) << "============================\n";
		cout << right << setw(60) << "Your Score: " << score << endl;
		cout << right << setw(60) << "Level Reached: " << level << endl;
		cout << right << setw(70) << "============================\n";
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
}

void saveScore(const string name, int score) {
	ofstream file("scores.txt", ios::app);
	file << name << " " << score << "\n";
}

void displayScore() {
	ifstream file("scores.txt");
	string name;
	int score;
	cout << right << setw(70) << "============================\n";
	cout << right << setw(62) << "Rangerboard\n";
	cout << right << setw(70) << "============================\n";
	while (file >> name >> score) {
		cout << right << setw(50) << "Name: " << name << ", Score: " << score << "\n";
	}
	cout << right << setw(70) << "============================\n";
}
