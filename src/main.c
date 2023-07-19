#include "log.h"
#include "util.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

int width = 1920;
int height = 1080;
int cells [1920][1080];
Texture2D screenTexture = {0};
Camera2D camera = { 0 };
float cooldown = 0;
float timer = 0;
int t = 1;

int countneighbours(int grid[width][height], int x, int y) {
    int count = 0;
    int dx, dy;
    int dxArray[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dyArray[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        dx = dxArray[i];
        dy = dyArray[i];

        if (x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height) {
            count += grid[x + dx][y + dy];
        }
    }

    return count;
}


void applyChanges(int newGrid[width][height], int grid[width][height]) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            grid[x][y] = newGrid[x][y];
        }
    }
}

void update(int running) {
    Color *pixels = (Color *)malloc(width * height * sizeof(Color));
    int newGrid[width][height];
    int liveNeighbors;

	timer += GetFrameTime();
	/* printf("%f\n", timer); */
	if (timer >= cooldown) {
		timer = 0;
		t = 1;
	} else {
		t = 0;
	}

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            liveNeighbors = countneighbours(cells, x, y);

            if (cells[x][y] == 1) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newGrid[x][y] = 0;
                } else {
                    newGrid[x][y] = 1;
                }
            } else {
                if (liveNeighbors == 3) {
                    newGrid[x][y] = 1;
                } else {
                    newGrid[x][y] = 0;
                }
            }

			if (running && t) {

			}
        }
    }

    if (running && t) {
        applyChanges(newGrid, cells);
    }

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (cells[x][y] == 1) {
                pixels[y * width + x] = WHITE;
            } else {
                pixels[y * width + x] = BLACK;
            }
        }
    }

    Image checkedIm = {
        .data = pixels,
        .width = width,
        .height = height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1
    };

    screenTexture = LoadTextureFromImage(checkedIm);
    UnloadImage(checkedIm);
}

int main(void) {
    InitWindow(width, height, "aaaa");
	ToggleFullscreen();
    SetTargetFPS(0); 

	camera.offset = (Vector2){ 0, 0 };
	camera.rotation = 0.0f;
	camera.zoom = 10.0f;

	for (int x = 0; x < 1920; ++x) {
		for (int y = 0; y < 1080; ++y) {
			cells[x][y] = RANDOM_INT_RANGE(0, 1);
		}
	}

	int running = 0;
    while (!WindowShouldClose()) {
		// cumera
		if (IsKeyDown(KEY_K)) camera.rotation--;
		else if (IsKeyDown(KEY_L)) camera.rotation++;
		else if (IsKeyDown(KEY_R)) {
			camera.rotation = 0;
			camera.offset = VEC2_0();
		}
		if (camera.rotation > 40) camera.rotation = 40;
		else if (camera.rotation < -40) camera.rotation = -40;
		camera.zoom += ((float)GetMouseWheelMove() * 0.5);
		if (camera.zoom <= 1.0f) {
			camera.zoom = 1.0f;
		}
		if (IsKeyPressed(KEY_UP)) {
			cooldown += 0.25;
		} else if (IsKeyPressed(KEY_DOWN)) {
			cooldown -= 0.25;
		}
		
		if (IsKeyDown(KEY_W)) {
			camera.offset.y += 1000 * dt;
		}
		if (IsKeyDown(KEY_S)) {
			camera.offset.y -= 1000 * dt;
		}
		if (IsKeyDown(KEY_A)) {
			camera.offset.x += 1000 * dt;
		}
		if (IsKeyDown(KEY_D)) {
			camera.offset.x -= 1000 * dt;
		}
		if (IsKeyPressed(KEY_SPACE)) {
			if (running == 0)
				running = 1;
			else 
				running = 0;
		}

		if (IsKeyDown(KEY_C)) {
			for (int x = 0; x < width; ++x) {
				for (int y = 0; y < height; ++y) {
					cells[x][y] = 0;
				}
			}
		}

		UnloadTexture(screenTexture);

		update(running);

        BeginDrawing();
        	ClearBackground(BLACK);

			BeginMode2D(camera);
				DrawTexture(screenTexture, 0, 0, WHITE);

				if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
					int mouseX = (int)((GetMouseX() / camera.zoom) - camera.offset.x);
					int mouseY = (int)((GetMouseY() / camera.zoom) - camera.offset.y);
					cells[mouseX][mouseY] = 1;
				}
				if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
					int mouseX = (int)((GetMouseX() / camera.zoom) - camera.offset.x);
					int mouseY = (int)((GetMouseY() / camera.zoom) - camera.offset.y);
					cells[mouseX][mouseY] = 0;
				}
			EndMode2D();

			DrawRectangleRec(RECT(20, 20, 100, 200), WHITE);
			DrawText(TextFormat("Wait time: %.2f", cooldown), 20, 40, 15, BLACK);
			DrawFPS(20, 20);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
