#pragma once
#include <iostream>

class Game
{
	public:
		void Render();
		void Start();
		void Update();
		void CheckForInput();
		void DrawSprite(char sprite[8][8], int x, int y);
		void DrawEntities();
	private:
		void DrawBackground();
		int CheckCollision(int x, int y, int sizeX, int sizeY, int source);
		void LoadMap();
		void MusicManager(int song);
		void Shoot();
		void MapTransition(int spot);
		void MoveEnemies();
		void StartGame();
};

