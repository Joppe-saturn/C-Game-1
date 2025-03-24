#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h> 
#include "Windows.h"

#pragma comment(lib, "winmm.lib")

//for debugging
bool isMute = true;
char debugLog = ' ';

//general
int screenSizeX = 45;
int screenSizeY = 80;
char screenDisplay[45][80];

char input = 0;
int totalSidewaysInputs = 0;
int maxSidewatsInputs = 1;

//player vars
int defaultPlayerValues[6] = { 8, 8, 2, 2, 6, 0}; //x, y, sizeX, sizeY, health, currentMap
int playerX = 0; 
int playerY = 0;
int playerSizeX = 0;
int playerSizeY = 0;

int playerHealthTextRow = 1;
char playerHealthDisplay[2] = { '<' , '>' };
int playerHealth = 0;

int totalValidInputs = 4;
char validInputs[4] = { 'w' , 'a' , 's' , 'd' };

bool canShoot = true;
bool isBulletActive = false;
int bulletX = 0;
int bulletY = 0;
char lastDirection = 'a';
int bulletDirection[2] = { -1 , 0 };

//map vars
int currentMap = 0;
char mapLayout[4][45][80];
int totalMapEvents = 10;
int mapEvents[4][10] =
{
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
};

int transitionSpotsCount = 3;
//transition points (map) (points) (x, y, sizeX, sizeY, transitionToMap, newPlayerX, newPlayerY, new song, appearWithEvent)
char transitionTiles[4][3][9] = { 
	{
		{29 , 66 , 2 , 4 , 1 , 22, 6 , 2, 0},
		{0 , 0 , 0 , 0 , -1 , 0 , 0 , 0, 0},
		{0 , 0 , 0 , 0 , -1 , 0 , 0 , 0, 0}
	},
	{
		{22 , 2 , 1 , 1 , 0 , 32 , 68 , 1, 0},
		{22 , 76 , 1 , 1 , 2 , 22 , 6 , 2, 0},
		{0 , 0 , 0 , 0 , -1 , 0 , 0 , 0, 0}
	},
	{
		{22 , 2 , 1 , 1 , 1 , 22 , 72 , 2, 0},
		{22 , 76 , 1 , 1 , 3 , 22 , 6 , 2, 1},
		{0 , 0 , 0 , 0 , -1 , 0 , 0 , 0, 0}
	},
	{
		{22 , 2 , 1 , 1 , 2 , 22 , 72 , 2, 0},
		{0 , 0 , 1 , 80 , 0 , 42 , 40 , 2, 0},
		{45 , 0 , 1 , 80 , 0 , 3 , 40 , 2, 0},
	}
};

int totalMaps = 4;

//sprites
char colors[13] = { ' ' , 'o' , '#' , '^' , ';' , '|', '[' , ']' , '!' , '%' , '*' , '`' , 'B'};
char spriteList[11][8][8] = {
	{
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] }
	}, //no sprite
	{
			{ colors[1] , colors[1] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[1] , colors[1] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] }
	}, //player sprite
	{
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[2] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[2] , colors[2] , colors[2] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[2] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[3] , colors[2] , colors[3] , colors[3] } ,
			{ colors[0] , colors[0] , colors[0] , colors[3] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[0] , colors[0] , colors[3] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] }
	}, //church sprite 1
	{
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] } ,
			{ colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] } ,
			{ colors[2] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] }
	}, //church sprite 2
	{
			{ colors[0] , colors[0] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[0] , colors[0] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[0] , colors[0] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[0] , colors[0] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[0] , colors[0] , colors[2] , colors[2] , colors[2] , colors[5] , colors[2] , colors[2] } ,
			{ colors[0] , colors[0] , colors[2] , colors[2] , colors[5] , colors[5] , colors[5] , colors[2] } ,
			{ colors[0] , colors[0] , colors[2] , colors[2] , colors[5] , colors[5] , colors[5] , colors[2] } ,
			{ colors[0] , colors[0] , colors[2] , colors[2] , colors[5] , colors[5] , colors[5] , colors[2] }
	}, //church sprite 3
	{
			{ colors[2] , colors[2] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] , colors[3] } ,
			{ colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] } ,
			{ colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] , colors[2] }
	}, //church sprite 4 
	{
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[9] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[7] , colors[0] , colors[0] , colors[9] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[9] , colors[7] , colors[6] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[8] , colors[0] , colors[9] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[8] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[8] , colors[0] , colors[0] , colors[0] , colors[0] }
	}, //tree sprite 
	{
			{ colors[11] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] }
	}, //bullet sprite
	{
			{ colors[6] , colors[7] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[6] , colors[7] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] }
	}, //door sprite
	{
			{ colors[12] , colors[12] , colors[12] , colors[12] , colors[12] , colors[12] , colors[0] , colors[0] } ,
			{ colors[12] , colors[0] , colors[0] , colors[0] , colors[0] , colors[12] , colors[0] , colors[0] } ,
			{ colors[12] , colors[0] , colors[12] , colors[0] , colors[0] , colors[12] , colors[0] , colors[0] } ,
			{ colors[12] , colors[0] , colors[0] , colors[0] , colors[12] , colors[12] , colors[0] , colors[0] } ,
			{ colors[0] , colors[12] , colors[12] , colors[0] , colors[12] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[12] , colors[12] , colors[12] , colors[0] , colors[0] , colors[0] } ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0]} ,
			{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] }
	}, //skull enemy sprite W
	{
		{ colors[12] , colors[12] , colors[12] , colors[12] , colors[12] , colors[12] , colors[0] , colors[0] } ,
		{ colors[12] , colors[0] , colors[0] , colors[0] , colors[0] , colors[12] , colors[0] , colors[0] } ,
		{ colors[12] , colors[0] , colors[0] , colors[12] , colors[0] , colors[12] , colors[0] , colors[0] } ,
		{ colors[12] , colors[12] , colors[0] , colors[0] , colors[0] , colors[12] , colors[0] , colors[0] } ,
		{ colors[0] , colors[12] , colors[0] , colors[12] , colors[12] , colors[0] , colors[0] , colors[0] } ,
		{ colors[0] , colors[12] , colors[12] , colors[12] , colors[0] , colors[0] , colors[0] , colors[0] } ,
		{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] } ,
		{ colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] , colors[0] }
	}, //skull enemy sprite O
}; 

//objects (map) (objects) (sprite, x, y, appearWithEvent)
int objects[4][8][4] =
{
	{
		{ 2 , 64 , 16 , 0 } ,
		{ 3 , 72 , 16 , 0 } ,
		{ 4 , 64 , 24 , 0 } ,
		{ 5 , 72 , 24 , 0 } ,
		{ 6 , 32 , 12 , 0 } ,
		{ 6 , 48 , 2 , 0 } ,
		{ 6 , 46 , 32 , 0 } ,
		{ 6 , 12 , 28 , 0 } 
	},
	{
		{ 8 , 2 , 22 , 0 } ,
		{ 8 , 76 , 22 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	},
	{
		{ 8 , 2 , 22 , 0 } ,
		{ 8 , 76 , 22 , 1 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	},
	{
		{ 8 , 2 , 22 , 0 } ,
		{ 8 , 76 , 22 , 1 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 }
	}
};

int solidObjectsCount = 5;
char solidObjects[5] = { '#' , '^' , '!' , '*' , 'B'};

int totalObjectsPerMap = 8;

//enemies (enemy) (spriteW, spriteO, speed, damage, sizeX, sizeY, hitCooldown, baseHealth)
int enemiePrefabs[2][8]{
	{0, 0, 0, 0, 0, 0, 0, 0}, //no enemy
	{9, 10, 15, 1, 6, 6, 2, 5}, //skull enemy
}; 

//enemies (map) (enemies instances) (enemie, x, y, health (cant be edited), direction, hitCooldown (cant be edited))
int enemies[4][8][6]{
	{
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 }
	},
	{
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 }
	},
	{
		{ 1 , 32 , 22 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 }
	},
	{
		{ 1 , 32 , 22 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 } ,
		{ 0 , 0 , 0 , 0 , 0 , 0 }
	}
};

int enemyTimer = 0;

int totalEnemiesPerMap = 8;

//music vars
float noteFrequencies[10][12] = {
	{ 16.35f , 17.32f , 18.35f , 19.45f , 20.60f , 21.83f , 23.12f , 24.50f , 25.96f , 27.50f , 29.14f , 30.87f }, //octave 0
	{ 32.70f , 34.65f , 36.71f , 38.89f , 41.20f , 43.65f , 46.25f , 49.0f , 51.91f , 55.0f , 58.27f , 61.74f }, //octave 1
	{ 65.41f , 69.30f , 73.42f , 77.78f , 82.41f , 87.31f , 92.50f , 98.0f , 103.83f , 110.0f , 116.54f , 123.47f }, //octave 2
	{ 130.81f , 138.59f , 146.83f , 155.56f , 164.81f , 174.61f , 185.0f , 196.0f , 207.65f , 220.0f , 233.08f , 246.94f }, //octave 3
	{ 261.63f , 277.18f , 293.66f , 311.13f , 329.63f , 349.23f , 369.99f , 392.0f , 415.30f , 440.0f , 466.16f , 493.88f }, //octave 4
	{ 523.25f , 554.37f , 587.33f , 622.25f , 659.26f , 698.46f , 739.99f , 783.99f , 830.61f , 880.0f , 932.33f , 987.77f }, //octave 5
	{ 1046.50f , 1108.73f , 1174.66f , 1244.51f , 1318.51f , 1396.91f , 1479.98f , 1567.98f , 1661.22f , 1760.0f , 1864.66f , 1975.53f }, //octave 6
	{ 2093.0f , 2217.46f , 2349.32f , 2489.02f , 2637.02f , 2793.83f , 2959.96f , 3135.96f , 3322.44f , 3520.0f , 3729.31f , 3951.07f }, //octave 7
	{ 4186.01f , 4434.92f , 4698.64f , 4978.03f , 5274.04f , 5587.65f , 5919.91f , 6271.93f , 6644.88f , 7040.0f , 7458.62f , 7902.13f }, //octave 8
	{ 8372.02f , 8869.84f , 9397.27f , 9956.06f , 10548.08f , 11175.30f , 11839.82f , 12543.86f , 13289.75f , 14080.0f , 14917.24f , 15804.26f } //octave 9
}; //This currently goes unused but I spent too much time on it to justify removing it
int currentSong = -1;

//Bottom screen text
int bottomScreenLength = 8;
std::string bottomScreenText[10] = {
	"____________________________________________________________",
	"Player: ",
	"____________________________________________________________",
	" ",
	"Controls:",
	"Wasd = Movement and Unpause.",
	"SPACE = Shoot.",
	"Pressing 2 buttons at the same time = Pause.",
	" ",
	"____________________________________________________________"
};

void Game::Start()
{
	StartGame();
	
	while (true)
	{
		if (playerHealth <= 0) 
		{
			StartGame();
		}

		DrawBackground();

		MoveEnemies();

		DrawEntities();

		Update();

		CheckForInput();

		Render();
	}
}

void Game::CheckForInput()
{
	if (!_kbhit()) 
	{
		totalSidewaysInputs = 0;
		return;
	}
	
	char oldInput = input;
	input = _getch();

	bool isvalid = false;
	for (int i = 0; i < totalValidInputs; i++) 
	{
		if (validInputs[i] == input) 
		{
			isvalid = true;
			break;
		}
	}

	if (!isvalid)
	{
		if (input != ' ') 
		{
			return;
		}
	}
	else 
	{
		lastDirection = input;
	}

	if (oldInput != input)
	{
		totalSidewaysInputs++;
	}
	else 
	{
		totalSidewaysInputs = 0;
	}
	
	if (totalSidewaysInputs > maxSidewatsInputs)
	{
		input = _getch();
		return;
	}

	if (input == ' ')
	{
		if (canShoot && !isBulletActive)
		{
			canShoot = false;
			Shoot();
		}
		return;
	}

	if (input == 'd')
	{
		playerX++;
		if (CheckCollision(playerX, playerY, playerSizeX, playerSizeY, 1) == 1)
		{
			playerX--;
		}
	}
	if (input == 'a')
	{
		playerX--;
		if (CheckCollision(playerX, playerY, playerSizeX, playerSizeY, 1) == 1)
		{
			playerX++;
		}
	}
	if (input == 's')
	{
		playerY++;
		if (CheckCollision(playerX, playerY, playerSizeX, playerSizeY, 1) == 1)
		{
			playerY--;
		}
	}
	if (input == 'w')
	{
		playerY--;
		if (CheckCollision(playerX, playerY, playerSizeX, playerSizeY, 1) == 1)
		{
			playerY++;
		}
	}
}

void Game::Shoot()
{
	int bulletOffsetX = 0;
	int bulletOffsetY = 0;
	
	if (lastDirection == 's')
	{
		bulletDirection[0] = 1;
		bulletDirection[1] = 0;
	}
	else if (lastDirection == 'w')
	{
		bulletDirection[0] = -1;
		bulletDirection[1] = 0;
		bulletOffsetX = 1;
	}
	else if (lastDirection == 'a')
	{
		bulletDirection[0] = 0;
		bulletDirection[1] = -1;
		bulletOffsetY = 1;
	}
	else if (lastDirection == 'd')
	{
		bulletDirection[0] = 0;
		bulletDirection[1] = 1;
	}

	bulletX = playerY + bulletDirection[0] + bulletOffsetX;
	bulletY = playerX + bulletDirection[1] + bulletOffsetY;

	isBulletActive = true;

	int collision = CheckCollision(bulletY, bulletX, 1, 1, 3);

	if (collision == 1 || collision == 4)
	{
		canShoot = true;
		isBulletActive = false;
	}
}

void Game::Update()
{
	for (int i = 0; i < totalObjectsPerMap; i++) 
	{
		int currentObject[4] = { objects[currentMap][i][0] , objects[currentMap][i][1] , objects[currentMap][i][2] , objects[currentMap][i][3] };
		
		if (mapEvents[currentMap][currentObject[3]] == currentObject[3]) 
		{
			DrawSprite(spriteList[currentObject[0]], currentObject[2], currentObject[1]);
		}
	}

	if (isBulletActive) 
	{
		bulletX += bulletDirection[0];
		bulletY += bulletDirection[1];
		int collision = CheckCollision(bulletY, bulletX, 1, 1, 3);
		if (collision == 1 || collision == 4) 
		{
			canShoot = true;
			isBulletActive = false;
		}
		else 
		{
			DrawSprite(spriteList[7], bulletX, bulletY);
		}
	}

	bool allEnemiesDead = true;
	for (int i = 0; i < totalEnemiesPerMap; i++) 
	{
		if (enemies[currentMap][i][3] != 0) 
		{
			allEnemiesDead = false;
			break;
		}
	}

	if (allEnemiesDead) 
	{
		mapEvents[currentMap][1] = 1;
	}
}

void Game::DrawEntities()
{
	DrawSprite(spriteList[1], playerY, playerX);

	for (int i = 0; i < totalEnemiesPerMap; i++) 
	{
		int currentEnemyInstance = enemies[currentMap][i][0];
		int currentEnemySprite = enemies[currentMap][i][4];
		if (enemies[currentMap][i][3] > 0) 
		{
			DrawSprite(spriteList[enemiePrefabs[currentEnemyInstance][currentEnemySprite]], enemies[currentMap][i][2], enemies[currentMap][i][1]);
		}
	}
}

void Game::DrawSprite(char sprite[8][8], int x, int y)
{
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			char pixel = sprite[i][j];
			if (pixel != ' ')
			{
				screenDisplay[i + x][j + y] = pixel;
			}
		}
	}
}

void Game::Render() 
{
	std::string display = "";
	for (int i = 0; i < screenSizeX; i++)
	{
		for (int j = 0; j < screenSizeY; j++)
		{
			display += screenDisplay[i][j];
		}
		
		if (i < bottomScreenLength) 
		{
			display += ' ' + bottomScreenText[i];
			if (i == playerHealthTextRow) 
			{
				int healthDisplayCounter = 0;
				for (int j = 0; j < playerHealth; j++) 
				{
					display += playerHealthDisplay[healthDisplayCounter];
					healthDisplayCounter = healthDisplayCounter - 2 * healthDisplayCounter + 1;
				}
			}
		}

		display += "\n";
	}
	
	system("cls");
	std::cout << display;
	std::cout << debugLog;
}

void Game::DrawBackground() 
{	
	for (int i = 0; i < screenSizeX; i++)
	{
		for (int j = 0; j < screenSizeY; j++)
		{
			screenDisplay[i][j] = mapLayout[currentMap][i][j];
		}
	}
}

void Game::MoveEnemies() 
{
	enemyTimer++;
	for (int i = 0; i < totalEnemiesPerMap; i++) 
	{
		int currentEnemy = enemies[currentMap][i][0];
		if (currentEnemy != 0) 
		{
			if (enemies[currentMap][i][3] <= 0) 
			{
				return;
			}
			if (enemyTimer % enemiePrefabs[currentEnemy][2] == 0)
			{
				int currentEnemyMovementX = 0;
				int currentEnemyMovementY = 0;

				int enemyPlayerDistanceX = playerX - enemies[currentMap][i][1];
				int enemyPlayerDistanceY = playerY - enemies[currentMap][i][2];

				if (enemyPlayerDistanceX > 0)
				{
					currentEnemyMovementX = 1;
				}
				else if (enemyPlayerDistanceX < 0)
				{
					currentEnemyMovementX = -1;
				}

				enemies[currentMap][i][4] = (currentEnemyMovementX + 1) / 2;

				if (enemyPlayerDistanceY > 0)
				{
					currentEnemyMovementY = 1;
				}
				else if (enemyPlayerDistanceY < 0)
				{
					currentEnemyMovementY = -1;
				}

				enemyPlayerDistanceX = sqrt(pow(enemyPlayerDistanceX, 2));
				enemyPlayerDistanceY = sqrt(pow(enemyPlayerDistanceY, 2));

			    if (enemyPlayerDistanceX > enemyPlayerDistanceY)
				{
					currentEnemyMovementY = 0;
				}
				else
				{
					currentEnemyMovementX = 0;
				}

				int collision = CheckCollision(enemies[currentMap][i][1] + currentEnemyMovementX, enemies[currentMap][i][2] + currentEnemyMovementY, 6, 6, 2);

				if (collision == 1)
				{
					int movementSwitch = currentEnemyMovementY;
					currentEnemyMovementY = currentEnemyMovementX;
					currentEnemyMovementX = movementSwitch * -1;

					collision = CheckCollision(enemies[currentMap][i][1] + currentEnemyMovementX, enemies[currentMap][i][2] + currentEnemyMovementY, 6, 6, 2);
				}
				if (collision == 0)
				{
					enemies[currentMap][i][1] += currentEnemyMovementX;
					enemies[currentMap][i][2] += currentEnemyMovementY;
				}
				else if (collision == 3)
				{
					if (enemies[currentMap][i][5] <= 0) 
					{
						playerHealth--;
						enemies[currentMap][i][5] = enemiePrefabs[currentEnemy][6];
						Beep(150, 600);
					}
					else 
					{
						enemies[currentMap][i][5]--;
					}
				}
			}
		}
	}
}

//return: 0 = no collision, 1 = solid wall collision, 2 = map transition collision, 3 = player collision, 4 = enemy collision
//source: 0 = none, 1 = player, 2 = enemy, 3 = bullet
int Game::CheckCollision(int x, int y, int sizeX, int sizeY, int source)
{
	//out of map check
	if (x >= screenSizeY || y >= screenSizeX || x < 0 || y < 0) 
	{
		return 1;
	}
	//map transition check
	if (source == 1) 
	{
		for (int i = 0; i < playerSizeX; i++)
		{
			for (int j = 0; j < playerSizeY; j++)
			{
				for (int k = 0; k < transitionSpotsCount; k++)
				{
					int checkPlayerX = playerY + j;
					int checkPlayerY = playerX + i;

					if (transitionTiles[currentMap][k][0] <= checkPlayerX && transitionTiles[currentMap][k][0] + transitionTiles[currentMap][k][2] >= checkPlayerX)
					{
						if (transitionTiles[currentMap][k][1] <= checkPlayerY && transitionTiles[currentMap][k][1] + transitionTiles[currentMap][k][3] >= checkPlayerY)
						{
							MapTransition(k);
							return 2;
						}
					}
				}
			}
		}
	}

	//enemy collision check;
	if (source == 3) 
	{
		for (int i = 0; i < totalEnemiesPerMap; i++) 
		{
			int enemyX = enemies[currentMap][i][1];
			int enemyY = enemies[currentMap][i][2];
			int enemySizeX = enemiePrefabs[enemies[currentMap][i][0]][1];
			int enemySizeY = enemiePrefabs[enemies[currentMap][i][0]][2];

			if (x >= enemyX && x <= enemyX + enemySizeX && y >= enemyY && y <= enemyY + enemySizeY && enemies[currentMap][i][3] > 0)
			{
				enemies[currentMap][i][3]--;
				return 4;
			}
		}
	}

	//solid wall check
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			for (int k = 0; k < solidObjectsCount; k++)
			{
				if (screenDisplay[y + j][x + i] == solidObjects[k])
				{
					return 1;
				}
			}
		}
	}

	//collision with player check
	if (source == 2) 
	{
		for (int i = 0; i < sizeX; i++)
		{
			for (int j = 0; j < sizeY; j++)
			{
				for (int playeri = 0; playeri < playerSizeX; playeri++)
				{
					for (int playerj = 0; playerj < playerSizeY; playerj++)
					{
						if (x + i == playerX + playeri && y + j == playerY + playerj)
						{
							return 3;
						}
					}
				}
			}
		}
	}
	
	return 0;
}

void Game::LoadMap()
{
	for (int i = 0; i < screenSizeX; i++)
	{
		for (int j = 0; j < screenSizeY; j++)
		{
			if (i == 0 || j == 0 || i == screenSizeX - 1 || j == screenSizeY - 1)
			{
				mapLayout[0][i][j] = '*';
			}
			else
			{
				mapLayout[0][i][j] = '_';
			}
		}
	}
	for (int i = 0; i < screenSizeX; i++)
	{
		for (int j = 0; j < screenSizeY; j++)
		{
			if (i < 10 || j == 0 || i > screenSizeX - 10 || j == screenSizeY - 1)
			{
				mapLayout[1][i][j] = '*';
			}
			else
			{
				mapLayout[1][i][j] = '_';
			}
		}
	}

	for (int i = 0; i < screenSizeX; i++)
	{
		for (int j = 0; j < screenSizeY; j++)
		{
			if (i < 10 || j == 0 || i > screenSizeX - 10 || j == screenSizeY - 1)
			{
				mapLayout[2][i][j] = '*';
			}
			else
			{
				mapLayout[2][i][j] = '_';
			}
		}
	}

	for (int i = 0; i < screenSizeX; i++)
	{
		for (int j = 0; j < screenSizeY; j++)
		{
			if (j == 0 || j == screenSizeY - 1)
			{
				mapLayout[3][i][j] = '*';
			}
			else
			{
				mapLayout[3][i][j] = '_';
			}
		}
	}
}

void Game::MapTransition(int spot) 
{
	playerY = transitionTiles[currentMap][spot][5];
	playerX = transitionTiles[currentMap][spot][6];
	
	int song = transitionTiles[currentMap][spot][7];
	if (song >= 0) 
	{
		MusicManager(song);
	}

	currentMap = transitionTiles[currentMap][spot][4];
}

//music

void Game::MusicManager(int song)
{
	//credits to "Max O'Didily" for his tutorial on how playsound works;

	if (currentSong == song) 
	{
		return;
	}

	currentSong = song;

	PlaySound(NULL, 0, 0);

	if (!isMute) 
	{
		if (song == 1)
		{
			PlaySound(TEXT("c++song.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		else if (song == 2)
		{
			PlaySound(TEXT("c++song2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
	}
}

//reset scene

void Game::StartGame() 
{
	LoadMap();

	playerX = defaultPlayerValues[0];
	playerY = defaultPlayerValues[1];
	playerSizeX = defaultPlayerValues[2];
	playerSizeY = defaultPlayerValues[3];
	playerHealth = defaultPlayerValues[4];
	currentMap = defaultPlayerValues[5];

	for (int i = 0; i < totalMaps; i++) 
	{
		for (int j = 0; j < totalMapEvents; j++) 
		{
			mapEvents[i][j] = 0;
		}
	}

	for (int i = 0; i < totalMaps; i++) 
	{
		for (int j = 0; j < totalEnemiesPerMap; j++)
		{
			enemies[i][j][3] = enemiePrefabs[enemies[i][j][0]][7];
		}
	}

	DrawBackground();
	Update();
	DrawEntities();
	Render();
	MusicManager(1);
}