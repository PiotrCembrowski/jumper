#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int GROUND_Y = 536;
const float GRAVITY = 0.25f;

// --- JUMP TUNING ---
const float INITIAL_JUMP_FORCE = -5.0f; // Small initial hop
const float JUMP_HOLD_ADDITION = -0.5f; // Extra force added while holding
const int MAX_JUMP_TIME = 15;           // Max frames you can hold to go higher

// Horizontal Movement
const float ACCEL = 0.5f;
const float MAX_SPEED = 6.0f;
const float FRICTION = 0.85f;

const int PLATFORM_W = 120;
const int PLATFORM_H = 30;