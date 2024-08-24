#pragma once

#define MIN_WALK_SPEED      10
#define MIN_RUN_SPEED       40

/* advanced settings */
#define ANIM_FRAME_DURATION 150  // how long each frame lasts in ms
// #define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

extern bool isSneaking;
extern bool isJumping;
extern bool showedJump;

void render_luna(int LUNA_X, int LUNA_Y);
