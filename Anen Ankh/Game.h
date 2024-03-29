#pragma once

#include "Level.h"
#include "Construct.h"
#include "Player.h"
#include "Room.h"

//Klasa b�d�ca klas� organizuj�c� gr�. Odpowiada za wczytanie najpierw menu, 
//potem przechodzenie mi�dzy poziomami, za�adowanie ponownie poziomu po �mierci... 
//Tego typu rzeczy. Na razie jest nam �rednio potrzebna, dop�ki mamy tylko jeden level,
//ale potem b�dzie potrzebna.

Texture * tex = NULL;

class Game
{
private:
	Level levelOne = *(new Level());

public:
	//Player player = *(new Player(SetPlayerPositionMatrix(), SetPlayerPositionVector()));
	Player player = *(new Player(SetPlayerPositionMatrix(), SetPlayerPositionVector(), SetPlayerViewVector(), SetPlayerUpVector()));
	float tempX;
	float tempY;
	float tempZ;

public:
	Game() {};
	~Game();

	//Nie mamy �adnych zmian perspektywyw grze - chyba �e np. obr�cimy j� po �mierci (�e si� k�adzie)
	//Ale info o �mierci i potrzebie zrelo�dowania systemu i tak odbiera game, wi�c mo�na zrobi� to tutaj.
	mat4 SetPerspective();
	mat4 SetPlayerPositionMatrix();
	vec3 SetPlayerPositionVector();
	mat4 GetPlayerPositionMatrix();
	vec3 SetPlayerViewVector();
	vec3 SetPlayerUpVector();
	//Macierzy Modelu ni ma bo to raczej sprawa poszczeg�lnych leveli

	void SetLevelOne(vector<float> objV, vector<float> objN, vector<float> objT);
	void ShowLevelOne(vector<float> objV, vector<float> objN, vector<float> objT);
};

Game::~Game()
{
	delete &levelOne;
	delete &player;
}

mat4 Game::SetPerspective()
{
	float aspect = (float)GetSystemMetrics(SM_CXSCREEN) / (float)GetSystemMetrics(SM_CYSCREEN);
	mat4 P = perspective(50.0f*3.14f / 180.0f, aspect, 0.1f, 1000.0f);
	return P;
}

mat4 Game::SetPlayerPositionMatrix()
{
	mat4 V = lookAt(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, -1000.0f),
		vec3(0.0f, -1.0f, 0.0f));
	return V;
}

vec3 Game::SetPlayerPositionVector()
{
	return vec3(0.0f, 0.0f, 0.0f);
}

vec3 Game::SetPlayerViewVector()
{
	return vec3(0.0f, 0.0f, -10.0f);
}

vec3 Game::SetPlayerUpVector()
{
	return vec3(0.0f, -1.0f, 0.0f);
}

mat4 Game::GetPlayerPositionMatrix()
{
	return player.positionMatrix;
}

void Game::SetLevelOne(vector<float> objV, vector<float> objN, vector<float> objT)
{

#pragma region ROOM_1

	// Load all textures here //
	Texture * floor_tex = (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective()));
	Texture * wall_tex = (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective()));
	tex = wall_tex;

	Room room = *(new Room(vec3(0, 0, 0), vec3(25, 50, 25)));

	Construct floor = *(new Construct("floor", Construct::cube, room.roomMatrix, (new Texture("Textures\\floorMetal.png", "Textures\\floorMetal_SPEC.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 50, 0), vec3(25, 0.1f, 25)));
	floor.SetCubeCollider(vec3(0, 50, 0), vec3(0, 0, 0), vec3(50, 1, 50));
	room.AddObject(floor);

	Construct wallFront = *(new Construct("floor", Construct::cube, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 33, -25), vec3(25, 17, 0.1f)));
	//wallFront.SetCubeCollider(vec3(0, 0, -1), vec3(0, 0, 0), vec3(25, 50, 5));
	room.AddObject(wallFront);

	Construct wallBack = *(new Construct("floor", Construct::cube, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 33, 25), vec3(25, 17, 0.1f)));
	room.AddObject(wallBack);

	Construct wallLeft = *(new Construct("floor", Construct::cube, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(-25, 33, 0), vec3(0.1f, 17, 25)));
	//wallLeft.SetCubeCollider(vec3(-25, 0, 0), vec3(0, 0, 0), vec3(1, 50, 25));
	room.AddObject(wallLeft);

	Construct wallRight = *(new Construct("floor", Construct::cube, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(25, 33, 0), vec3(0.1f, 17, 25)));
	wallRight.SetCubeCollider(vec3(25, 33, 0), vec3(0, 0, 0), vec3(1, 34, 50));
	room.AddObject(wallRight);

	Construct cube = *(new Construct("floor", Construct::cube, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 17, -16.5), vec3(25, 1, 1)));
	cube.SetCubeCollider(vec3(0, 17, -16.5), vec3(0, 0, 0), vec3(50, 3, 3));
	room.AddObject(cube);

	Construct cube1 = *(new Construct("floor", Construct::cube, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 17, 16.5), vec3(25, 1, 1)));
	cube1.SetCubeCollider(vec3(0, 17, 16.5), vec3(0, 0, 0), vec3(50, 3, 3));
	room.AddObject(cube1);

	Construct stairs1 = *(new Construct("stairs", Construct::stairs, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(15, 33, 0), vec3(0, 0, 0)));
	stairs1.SetCubeCollider(vec3(15, 50, 0), vec3(0, 0, 0), vec3(20, 100, 30));
	stairs1.SetLineCollider(-7.5, 7.5f, 3.2f, -14.2f);
	room.AddObject(stairs1);

	Construct tempCube1 = *(new Construct("stairs", Construct::cube, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(15, 33, 0), vec3(0, 0, 0)));
	tempCube1.SetCubeCollider(vec3(5, 50, -1.5), vec3(0, 0, 0), vec3(0.5, 100, 27));
	room.AddObject(tempCube1);

	Construct tempCube2 = *(new Construct("stairs", Construct::cube, room.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(15, 33, 0), vec3(0, 0, 0)));
	tempCube2.SetCubeCollider(vec3(15, 50, -15), vec3(0, 0, 0), vec3(20, 20, 0.1));
	room.AddObject(tempCube2);

#pragma endregion

#pragma region ROOM_2
	Room room2 = *(new Room(vec3(0, -8.9, 0), vec3(75, 25, 75)));

	Construct floor1 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(50, 25, 0), vec3(25, 0.1f, 25)));
	floor1.SetCubeCollider(vec3(50, 15, 0), vec3(0, 0, 0), vec3(50, 0.1f, 50));
	room2.AddObject(floor1);

	Construct floor2 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 25, 50), vec3(75, 0.1f, 25)));
	floor2.SetCubeCollider(vec3(0, 15, 50), vec3(0, 0, 0), vec3(150, 0.1f, 50));
	room2.AddObject(floor2);

	Construct floor3 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(-50, 25, 0), vec3(25, 0.1f, 25)));
	floor3.SetCubeCollider(vec3(-50, 15, 0), vec3(0, 0, 0), vec3(50, 0.1f, 50));
	room2.AddObject(floor3);

	Construct floor4 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 25, -50), vec3(75, 0.1f, 25)));
	floor4.SetCubeCollider(vec3(0, 15, -50), vec3(0, 0, 0), vec3(150, 0.1f, 50));
	room2.AddObject(floor4);

	Construct roof = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, -25 + 1, 15), vec3(75, 1, 60)));
	roof.SetCubeCollider(vec3(0, -10, 0), vec3(0, 0, 0), vec3(50, 1, 100));
	room2.AddObject(roof);

	Construct roof1 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(50, -25 + 1, -60), vec3(25, 1, 15)));
	roof1.SetCubeCollider(vec3(0, -10, 0), vec3(0, 0, 0), vec3(50, 1, 100));
	room2.AddObject(roof1);

	Construct roof2 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(-50, -25 + 1, -60), vec3(25, 1, 15)));
	roof1.SetCubeCollider(vec3(0, -10, 0), vec3(0, 0, 0), vec3(50, 1, 100));
	room2.AddObject(roof2);

	Construct wallFrontRoom2 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 0, -75), vec3(75, 25, 0.1f)));
	wallFrontRoom2.SetCubeCollider(vec3(0, 0, -75), vec3(0, 0, 0), vec3(150, 50, 1));
	room2.AddObject(wallFrontRoom2);

	Construct wallBackRoom2 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(0, 0, 75), vec3(75, 25, 0.1f)));
	wallBackRoom2.SetCubeCollider(vec3(0, 0, 75), vec3(0, 0, 0), vec3(150, 50, 1));
	room2.AddObject(wallBackRoom2);

	/////
	Construct wallLeft1 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(-75, 17, 40), vec3(0.1f, 8, 35)));
	wallLeft1.SetCubeCollider(vec3(-75, 17, 40), vec3(0, 0, 0), vec3(1, 16, 70));
	room2.AddObject(wallLeft1);

	Construct wallLeft2 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(-75, 17, -40), vec3(0.1f, 8, 35)));
	wallLeft2.SetCubeCollider(vec3(-75, 17, -40), vec3(0, 0, 0), vec3(1, 16, 70));
	room2.AddObject(wallLeft2);

	Construct wallLeft3 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(-75, -8.5, 0), vec3(0.1f, 17.5, 75)));
	wallLeft3.SetCubeCollider(vec3(-75, -8.5, 0), vec3(0, 0, 0), vec3(1, 35, 150));
	room2.AddObject(wallLeft3);
	/////

	Construct wallRightRoom2 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(75, 0, 0), vec3(0.1f, 25, 75)));
	wallRightRoom2.SetCubeCollider(vec3(75, 0, 0), vec3(0, 0, 0), vec3(1, 50, 150));
	room2.AddObject(wallRightRoom2);

#pragma endregion

#pragma region ROOM_3
	Room room3 = *(new Room(vec3(0, -75, 10), vec3(75, 25, 75)));

	floor = *(new Construct("floor", Construct::cube, room2.roomMatrix, floor_tex, vec3(-85, 25, 0), vec3(10, 0.1f, 5)));
	floor.SetCubeCollider(vec3(-85, 15, 0), vec3(0, 0, 0), vec3(20, 0.1f, 10));
	room3.AddObject(floor);

	roof = *(new Construct("floor", Construct::cube, room2.roomMatrix, wall_tex, vec3(-85, 9, 0), vec3(10, 0.1f, 5)));
	roof.SetCubeCollider(vec3(0, -10, 0), vec3(0, 0, 0), vec3(50, 1, 100));
	room3.AddObject(roof);

	Construct wallFrontRoom3 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(-85, 17, -5), vec3(10, 8, 0.1f)));
	wallFrontRoom3.SetCubeCollider(vec3(-85, 17, -5), vec3(0, 0, 0), vec3(20, 16, 1));
	room3.AddObject(wallFrontRoom3);

	Construct wallBackRoom3 = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Textures\\metal.png", "Textures\\metal_spec.png", objV.size(), objV.data(), objN.data(), objT.data(), objT.data(), SetPerspective())), vec3(-85, 17, 5), vec3(10, 8, 0.1f)));
	wallBackRoom3.SetCubeCollider(vec3(-85, 17, 5), vec3(0, 0, 0), vec3(20, 16, 1));
	room3.AddObject(wallBackRoom3);

#pragma endregion

#pragma region ROOM_4
/*
Room room3 = *(new Room(vec3(0, -75, 10), vec3(75, 25, 75)));

floor = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Texture\bricks.png")), vec3(-85, 25, 0), vec3(10, 0.1f, 5)));
floor.SetCubeCollider(vec3(50, 50, 0), vec3(0, 0, 0), vec3(50, 0.1f, 50));
room3.AddObject(floor);

roof = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Texture\bricks.png")), vec3(-85, 9, 0), vec3(10, 0.1f, 5)));
roof.SetCubeCollider(vec3(0, -10, 0), vec3(0, 0, 0), vec3(50, 1, 100));
room3.AddObject(roof);

wallFront = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Texture\bricks.png")), vec3(-85, 17, -5), vec3(10, 8, 0.1f)));
wallFront.SetCubeCollider(vec3(0, 0, -20), vec3(0, 0, 0), vec3(25, 100, 1));
room3.AddObject(wallFront);

wallBack = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Texture\bricks.png")), vec3(-85, 17, 5), vec3(10, 8, 0.1f)));
wallBack.SetCubeCollider(vec3(0, 0, 20), vec3(0, 0, 0), vec3(25, 100, 1));
room3.AddObject(wallBack);

/*wallLeft = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Texture\bricks.png")), vec3(-75, 17, 40), vec3(0.1f, 8, 35)));
wallLeft.SetCubeCollider(vec3(-20, 0, 0), vec3(0, 0, 0), vec3(1, 100, 25));
room3.AddObject(wallLeft);

wallRight = *(new Construct("floor", Construct::cube, room2.roomMatrix, (new Texture("Texture\bricks.png")), vec3(75, 0, 0), vec3(0.1f, 25, 75)));
wallRight.SetCubeCollider(vec3(20, 0, 0), vec3(0, 0, 0), vec3(1, 100, 25));
room3.AddObject(wallRight);
*/
#pragma endregion


	levelOne.labirynth.AddRoom(room);
	levelOne.labirynth.AddRoom(room2);
	levelOne.labirynth.AddRoom(room3);

}

void Game::ShowLevelOne(vector<float> objV, vector<float> objN, vector<float> objT)
{
	//Tutaj reload przy �mierci, przej�cie do nastepnego poziomu przy wygranej itp.
	
	levelOne.labirynth.ShowLabirynth(player.positionMatrix, objV, objN, objT, tex);

	if (player.noClip == false)
	{

		player.collider.ChangePositionOfCenter(player.positionVector);

		if (player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[0].cubeCollider) == false
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[5].cubeCollider) == false
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[6].cubeCollider) == false
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[0].cubeCollider) == false
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[1].cubeCollider) == false
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[2].cubeCollider) == false
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[3].cubeCollider) == false
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[2].objects[0].cubeCollider) == false
			)
		{
			player.FallDown();
			player.SetCollider();
		}

		if (player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[0].cubeCollider) == true
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[5].cubeCollider) == true
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[6].cubeCollider) == true
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[0].cubeCollider) == true
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[1].cubeCollider) == true
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[2].cubeCollider) == true
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[3].cubeCollider) == true
			&& player.collider.DetectCollision(levelOne.labirynth.rooms[2].objects[0].cubeCollider) == true
			)
			player.GoUp();


		if (player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[1].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[7].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[2].objects[2].cubeCollider))
			player.canGoFoward = false;
		else
			player.canGoFoward = true;

		if (player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[2].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[8].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[2].objects[3].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[9].cubeCollider))
			player.canGoBack = false;
		else
			player.canGoBack = true;

		if (player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[3].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[9].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[10].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[11].cubeCollider))			player.canGoLeft = false;
		else
			player.canGoLeft = true;

		if (player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[4].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[1].objects[12].cubeCollider)
			|| player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[8].cubeCollider))
			player.canGoRight = false;
		else
			player.canGoRight = true;


		if (player.collider.DetectCollision(levelOne.labirynth.rooms[0].objects[7].cubeCollider))
		{
			while (levelOne.labirynth.rooms[0].objects[7].lineCollider.DetectCollision(player.collider.position.z, player.collider.position.y) == true)
			{
				player.GoUp();
				player.SetCollider();
			}
		}
	}
}