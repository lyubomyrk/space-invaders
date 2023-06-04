#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>

template <typename T>
T getRandomElement(const std::vector<T>& vec) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, vec.size() - 1);

	return vec[dis(gen)];
}

using namespace std;

struct Player {
	Vector2 pos;
	Texture2D tex;
	Rectangle source;
	Vector2 offset;
};

struct Bullet {
	Vector2 pos;
};

struct Alien {
	Vector2 pos;
};

const int obstacle_width = 64;
const int obstacle_height = 32;
const int obstacle_size = obstacle_height * obstacle_width;
bool obstacle[obstacle_size] = {
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,true, true, true, true, true, true, true, true,
};

struct Obstacle {
	bool* bitmap;
	Vector2 pos;
};

Alien* getrightmost(vector<Alien*> aliens);
Alien* getleftmost(vector<Alien*> aliens);

const int ScreenWidth = 800;
const int ScreenHeight = 450;

string ResourcePrefix = "../../../resources/";

int main(void)
{
	InitWindow(ScreenWidth, ScreenHeight, "Alien Defense!");
	SetTargetFPS(60);

	string prefix = ResourcePrefix;

	Player player;
	player.pos = { ScreenWidth / 2, ScreenHeight - 25 };
	player.tex = LoadTexture((prefix + "player.png").c_str());
	player.source = { 0., 0., (float)player.tex.width, (float)player.tex.height };
	player.offset = { (float)player.tex.width / 2, (float)player.tex.height / 2 };
	float speed = 200;
	vector<Bullet*> bullets;
	float bullet_speed = 300;

	Texture2D alien_tex = LoadTexture((prefix + "red.png").c_str());
	Rectangle alien_source = { 0., 0., alien_tex.width, alien_tex.height };
	Vector2 alien_offset = { alien_tex.width / 2, alien_tex.height / 2 };
	vector<Alien*> aliens;
	vector<Bullet*> alien_bullets;
	float alien_bullet_speed = 150;
	float aliens_horiz_empty_space = 20;

	int row = 0;
	int col = 0;
	for (int i = 0; i < 55; i++) {
		Alien* new_alien = new Alien;
		if (i % 11 == 0) {
			row++;
			col = 0;
		}
		new_alien->pos.x = 100 + col * 50;
		new_alien->pos.y = row * 40;
		aliens.push_back(new_alien);
		col++;
	}

	float alien_update_time = 1000; // ms
	float alien_shoot_time = 1000; // ms
	float alien_step = 20;
	bool alien_jumped = false;
	int alien_dir = 1;
	float move_timer = 0;
	float shoot_timer = 0;

	vector<Obstacle*> obstacles;
	for (int i = 0; i < 4; i++) {
		Obstacle* new_obstacle = new Obstacle;
		new_obstacle->bitmap = new bool[obstacle_size];
		copy(obstacle, obstacle + obstacle_size, new_obstacle->bitmap);
		new_obstacle->pos.y = player.pos.y - 100;
		new_obstacle->pos.x = 100 + i * 200;
		obstacles.push_back(new_obstacle);
	}

	bool game_over = false;

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		move_timer += dt * 1e3;
		shoot_timer += dt * 1e3;

		// Player input
		if (IsKeyDown(KEY_RIGHT))
			player.pos.x += speed * dt;
		if (IsKeyDown(KEY_LEFT))
			player.pos.x -= speed * dt;
		if (IsKeyPressed(KEY_SPACE)) {
			if (bullets.size() == 0)
				bullets.push_back(new Bullet{ player.pos.x, player.pos.y - 5 });
		}

		// Update positions
		player.pos.x = Clamp(player.pos.x, 0, ScreenWidth - player.source.width / 2);

		for (auto& b : bullets) {
			b->pos.y -= bullet_speed * dt;
		}
		for (auto& b : alien_bullets) {
			b->pos.y += alien_bullet_speed * dt;
		}


		if (move_timer > alien_update_time) {
			move_timer = 0;
			bool jump_down = false;
			Alien* rightmost = getrightmost(aliens);
			Alien* leftmost = getleftmost(aliens);
			if (!alien_jumped && (leftmost->pos.x <= 50 || rightmost->pos.x >= ScreenWidth - 50)) {
				alien_dir *= -1;
				jump_down = true;
				alien_jumped = true;
			}

			for (auto& a : aliens) {
				if (jump_down) {
					a->pos.y += alien_step;
				}
				else {
					a->pos.x += alien_dir * alien_step;
					alien_jumped = false;
				}
			}
		}

		// Check conditions
		if (game_over) {
			break;
		}
		for (auto& a : aliens) {
			if (a->pos.y >= player.pos.y) {
				game_over = true;
			}
		}
		if (shoot_timer > alien_shoot_time) {
			shoot_timer = 0;
			Alien* random_alien = getRandomElement(aliens);
			Bullet* alien_bullet = new Bullet;
			alien_bullet->pos.x = random_alien->pos.x;
			alien_bullet->pos.y = random_alien->pos.y + alien_offset.y;
			alien_bullets.push_back(alien_bullet);
		}

		// Handle collisions
		vector<int> aliens_delet_pos;
		vector<int> bullet_delet_pos;
		vector<int> alien_bullet_delet_pos;

		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i]->pos.y <= -20) {
				bullet_delet_pos.push_back(i);
			}
			else {
				Bullet* b = bullets[i];
				Rectangle bulletrec = { b->pos.x - 4, b->pos.y - 6, 6, 12 };
				for (int j = 0; j < aliens.size(); j++) {
					Alien* a = aliens[j];
					Rectangle alienrec = { a->pos.x - alien_offset.x, a->pos.y - alien_offset.y, alien_source.width, alien_source.height };
					if (CheckCollisionRecs(bulletrec, alienrec)) {
						// Set for deletion
						aliens_delet_pos.push_back(j);
						bullet_delet_pos.push_back(i);
						break;
					}
				}
			}
		}
		for (int i = 0; i < alien_bullets.size(); i++) {
			Bullet* b = alien_bullets[i];
			Rectangle bulletrec = { b->pos.x - 3, b->pos.y - 6, 6, 12 };
			Rectangle playerrec = { player.pos.x + 5, player.pos.y + 3, player.source.width - 5, player.source.height - 3 };
			if (CheckCollisionRecs(bulletrec, playerrec)) {
				game_over = true;
				break;
			}
			if (alien_bullets[i]->pos.y > ScreenHeight + 20) {
				alien_bullet_delet_pos.push_back(i);
				continue;
			}
			for (auto& o : obstacles) {
				Rectangle obstaclerec = { o->pos.x, o->pos.y, obstacle_width, obstacle_height };
				if (CheckCollisionRecs(bulletrec, obstaclerec)) {
					alien_bullet_delet_pos.push_back(i);
					int blast_radius = 3;
					float x = b->pos.x + 3 - o->pos.x;
					float y = b->pos.y + 6 - o->pos.y;
					for (int i = 0; i < obstacle_height; i++) {
						for (int j = 0; j < obstacle_width; j++) {
							float distance = Vector2Length({ x - j, y - i });
							if (distance < blast_radius) {
								o->bitmap[i * obstacle_width + j] = false;
							}
						}
					}
				}
			}
		}

		// Delete elements
		for (auto i : bullet_delet_pos) {
			bullets.erase(bullets.begin() + i);
		}
		for (auto i : alien_bullet_delet_pos) {
			alien_bullets.erase(alien_bullets.begin() + i);
		}
		for (auto i : aliens_delet_pos) {
			aliens.erase(aliens.begin() + i);
			alien_update_time -= 12;
			alien_shoot_time -= 3;
		}


		BeginDrawing();
		ClearBackground(RAYWHITE);

		// Draw aliens
		for (auto& a : aliens) {
			DrawTexturePro(alien_tex, alien_source, { a->pos.x, a->pos.y, alien_source.width, alien_source.height }, alien_offset, 0., WHITE);
		}

		// Draw player
		DrawTexturePro(player.tex, player.source, { player.pos.x, player.pos.y, player.source.width, player.source.height }, player.offset, 0., WHITE);
		DrawLine(player.pos.x, 0, player.pos.x, ScreenHeight, BLUE);
		DrawLine(0, player.pos.y, ScreenWidth, player.pos.y, BLUE);

		// Draw obstacles
		for (auto& o : obstacles) {
			Vector2 offset = o->pos;
			for (int i = 0; i < obstacle_height; i++) {
				for (int j = 0; j < obstacle_width; j++) {
					if (o->bitmap[i * obstacle_width + j]) {
						Vector2 pos = { offset.x + j, offset.y + i };
						DrawPixelV(pos, GREEN);
					}
				}
			}
		}

		// Draw player bullet
		for (auto& b : bullets) {
			DrawLineEx({ b->pos.x, b->pos.y - 6 }, { b->pos.x, b->pos.y + 6 }, 6, PURPLE);
		}
		// Draw alien bullet
		for (auto& b : alien_bullets) {
			DrawLineEx({ b->pos.x, b->pos.y - 6 }, { b->pos.x, b->pos.y + 6 }, 6, BLACK);
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

Alien* getrightmost(vector<Alien*> aliens)
{
	float max = 0;
	Alien* rightmost = nullptr;
	for (auto& a : aliens) {
		if (a->pos.x >= max) {
			max = a->pos.x;
			rightmost = a;
		}
	}
	return rightmost;
}

Alien* getleftmost(vector<Alien*> aliens)
{
	float min = ScreenWidth;
	Alien* leftmost = nullptr;
	for (auto& a : aliens) {
		if (a->pos.x <= min) {
			min = a->pos.x;
			leftmost = a;
		}
	}
	return leftmost;
}
