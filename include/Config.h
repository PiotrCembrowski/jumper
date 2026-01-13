#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GROUND_Y = 536;
const float GRAVITY = 0.25f;
const float PLAYER_SPEED = 5.0f;

// Jump sensitivity constants
const float INITIAL_JUMP_FORCE = -5.0f; // Small initial hop
const float JUMP_HOLD_ADDITION = -0.4f; // Force added every frame W is held
const int MAX_JUMP_TIME = 15;           // Max frames the player can "boost" the jump