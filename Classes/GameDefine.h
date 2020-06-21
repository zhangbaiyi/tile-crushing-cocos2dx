
#ifndef  _Inkmoo_Elimination_h_
#define  _Inkmoo_Elimination_h_

#define GAME_SCREEN_WIDTH 480
#define GAME_SCREEN_HEIGHT 800

#define SPRITE_WIDTH 48
#define BOADER_WIDTH 2

#define ROWS 8
#define COLS 8

#define TOTAL_SPRITE 6

#define MAP_SIZE 64

#define TAG_LAYER_SCORE 10

#include "SimpleAudioEngine.h"

#define SOUND_KEY "sound_key"
#define MUSIC_KEY "music_key"


#define NORMAL_SPRITE 0
#define ROW_SPRITE 1
#define COL_SPRITE 2

#define left_up_label_width 80
#define left_up_label_height 710
#define left_up_label_size 27

#define right_up_label_width 430
#define right_up_label_height 720
#define right_up_label_size 27

#define aim_label_width 430
#define aim_label_height 690
#define aim_label_size 27

#define level_trans_current_label_width 200
#define level_trans_current_label_height 600
#define level_trans_current_label_size 27

#define level_trans_best_label_width 418
#define level_trans_best_label_height 600
#define level_trans_best_label_size 27

#define level_trans_croissant_width 240
#define level_trans_croissant_height 650
#define level_trans_croissant_size 27

#define level_trans_donut_width 90
#define level_trans_donut_height 520
#define level_trans_donut_size 27

#define level_trans_cupcake_width 90
#define level_trans_cupcake_height 651
#define level_trans_cupcake_size 27

#define level_trans_danish_width 386
#define level_trans_danish_height 520
#define level_trans_danish_size 27

#define level_trans_macaroon_width 240
#define level_trans_macaroon_height 520
#define level_trans_macaroon_size 27

#define level_trans_supercookie_width 386
#define level_trans_supercookie_height 650
#define level_trans_supercookie_size 27

#define level_trans_aim_label_width 240
#define level_trans_aim_label_height 680
#define level_trans_aim_label_size 35

#define level_trans_bonus_label_width 290
#define level_trans_bonus_label_height 530
#define level_trans_bonus_label_size 27

#define zen_score_size 54
#define zen_score_width 240
#define zen_score_height 650

#define zen_best_x 390
#define zen_best_y 470
#define zen_best_size 54

#define level_best_x 390
#define level_best_y 376
#define level_best_size 54

#define gen_best_x 390
#define gen_best_y 280
#define gen_best_size 54


#define SCORE_PER_LEVEL 100
#define BASE_SCORE 30

#define LEVEL_CHANGE 1
#define LEVEL_TO_STEP(x) x * 2 + 3
#define SCORE_CHANGE 60

#define DISPLAY_TIME_SPLASH_SCENE 2.0

#define TRANSITION_TIME 0.5

#define TRANSITION_LEVEL 4.0

#define ZEN_MODEL 0
#define	GENERAL_MODEL 1
#define RLIKE_MODEL 2
#define CONTINUE_MODEL 3

static const char* spriteNormal[TOTAL_SPRITE] =
{
	"Croissant.png",
	"Cupcake.png",
	"Danish.png",
	"Macaroon.png",
	"SugarCookie.png",
	"Donut.png"
};

static const char* spriteHighlighted[TOTAL_SPRITE] =
{
	"Croissant-Highlighted.png",
	"Cupcake-Highlighted.png",
	"Danish-Highlighted.png",
	"Macaroon-Highlighted.png",
	"SugarCookie-Highlighted.png",
	"Donut-Highlighted.png"
};

static const unsigned long long rowEliminate[ROWS] =
{
	0xff,
	0xff00,
	0xff0000,
	0xff000000,
	0xff00000000,
	0xff0000000000,
	0xff000000000000,
	0xff00000000000000
};

static const unsigned long long colEliminate[ROWS] =
{
	0x0101010101010101,
	0x0202020202020202,
	0x0404040404040404,
	0x0808080808080808,
	0x1010101010101010,
	0x2020202020202020,
	0x4040404040404040,
	0x8080808080808080
};
#endif
