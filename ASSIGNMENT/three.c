#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

int level=1;
int score=0;
int lives=10;
int treasurepoints = 0;
int treasureN = 0;

#define DELAY (10)

#define PERSON_WIDTH (3)
#define PERSON_HEIGHT (3)

#define ZOMBIE_WIDTH (4)
#define ZOMBIE_HEIGHT (4)

#define PLATFORM_WIDTH ((screen_width()/3))
#define PLATFORM_HEIGHT (1)

#define PLATFORM_L_2_WIDTH (PLATFORM_WIDTH / 3)
#define PLATFORML2_HEIGHT (1)

#define EXIT_WIDTH (4)
#define EXIT_HEIGHT (4)

#define PLATFORM_B_WIDTH (screen_width())
#define PLATFORM_B_HEIGHT (1)

#define PLATFORM_B_1_W (screen_width()* 0.25)
#define PLATFORM_B_1_H (1)

#define PLATFORM_MOVE_W (screen_width()*0.4)
#define PLATFORM_MOVE_H (1)

#define MONSTER_WIDTH (3)
#define MONSTER_HEIGHT (2)

#define TREASURE_WIDTH (3)
#define TREASURE_HEIGHT (3)

#define PLATFORM_T_W (12)
#define PLATFORM_T_H (1)

// Defining Global Variables 
bool game_over = false;
bool update_screen = true;
bool on_ground = true;
bool enable_keys = true;
bool treasuretaken = false; 

sprite_id person;
sprite_id door;
sprite_id zombie;
sprite_id platform;
sprite_id platform_b1;
sprite_id platform_b2;
sprite_id platformTop;
sprite_id monster;
sprite_id treasure;
sprite_id platform_move;
sprite_id platform_T;

timer_id my_timer;
int minute;
int second;

double person_dx = 0;
double person_dy = 0;

char * person_img = 
/**/ 			 " o "
/**/			 "/|\\" 
/**/			 "/ \\";

char * zombie_image =
/**/	"ZZZZ"
/**/	"  Z "
/**/	" Z  "
/**/	"ZZZZ";

char * exit_image =
/**/ "EXIT"
/**/ "|  |"
/**/ "| .|"
/**/ "|  |";
char * platform_image = "=========================================================================================================================================================================================";
/**/ 

char * monster_image = 
/**/ " | "
/**/ "/ \\";

char* treasure_image= 
/**/ "  ."
/**/ " $ "
/**/ "'  ";

char* treasure2_image= 
/**/ ".  "
/**/ " $ "
/**/ "  '";

char* treasure3_image= 
/**/ "  '"
/**/ " $ "
/**/ "   ";

char* treasure4_image= 
/**/ "   "
/**/ " $ "
/**/ "'  ";
void setup_timer() {
	my_timer = create_timer(1000);
}

void process_timer() {
	if (timer_expired( my_timer )) {
		second++;
		if (second == 60) {
			minute++;
			second = 0;
		}
		timer_reset(my_timer);
	}
}

void display_time () {
	if (second < 10 && minute < 10) {
		draw_formatted(0, 0, "Time: 0%d:0%d", minute, second);
	} else if (second < 10 && minute >=10) {
		draw_formatted (0, 0, "Time: %d:0%d", minute, second);
	} else if (second >=10 && minute < 10) {
		draw_formatted( 0, 0, "Time: 0%d:%d", minute, second);
	} else {
		draw_formatted(0, 0, "Time: %2d:%2d", minute, second);
	}
}

void draw_border(void) {
	int left = 0;
	int right = screen_width() - 1; 
	int top = 1;
	int bottom = screen_height() -1;
	char border = '-';
	char sides = ':';

	draw_line (left, bottom-1, left, top+1, sides);
	draw_line (0, top, screen_width(), top, border);
	draw_line (right, top+1, right, bottom-1, sides);

	//Declare variables for status bar
	int second = 0.25*screen_width() - 1;
	int third = 0.5*screen_width() - 1;
	int	fourth = 0.75*screen_width() - 1;
	int y = 0;

	draw_formatted(second, y, "Lives %d", lives);
	draw_formatted(third, y, "Level:%d", level);
	draw_formatted(fourth, y, "Score:%d", score);
}

void drawSprites3 (void) {

	double x_p = 4;
	double y_p = screen_height() - 4;
	person = sprite_create(x_p, y_p, PERSON_WIDTH, PERSON_HEIGHT, person_img);
	sprite_draw(person);

	double x_pl = screen_width()*0.33;
	double y_pl = screen_height() - 12.5;
	platform_move = sprite_create(x_pl, y_pl, PLATFORM_MOVE_W, PLATFORM_MOVE_H, platform_image);
	sprite_draw(platform_move);

	double x_plT = screen_width()*0.5 - 7;
	double y_plT = screen_height() - 22.5;
	platform_T = sprite_create(x_plT, y_plT, PLATFORM_T_W, PLATFORM_T_H, platform_image);
	sprite_draw(platform_T);

	double x_e = screen_width()* 0.5 - EXIT_WIDTH/2 -1;
	double y_e = y_plT - EXIT_HEIGHT;
	door = sprite_create(x_e, y_e, EXIT_WIDTH, EXIT_HEIGHT, exit_image);
	sprite_draw (door);

	double x_b1 = 0;
	double y_b1 = screen_height() - 1;
	platform_b1 = sprite_create(x_b1, y_b1, PLATFORM_B_1_W, PLATFORM_B_1_H, platform_image);
	sprite_draw(platform_b1);

	double x_b2 = screen_width() * 0.75 -1;
	double y_b2 = screen_height() - 1;
	platform_b2 = sprite_create(x_b2, y_b2, PLATFORM_B_1_W, PLATFORM_B_1_H, platform_image);
	sprite_draw(platform_b2);

	sprite_turn_to( platform_move, -0.35, 0);

	show_screen();

}
void person_ground3(void) {

	int person_x = round(sprite_x(person));
	int person_y = round(sprite_y(person));
	on_ground = false;
	int platform_b1_y = round(sprite_y(platform_b1));
	int platform_b1_x = round(sprite_x(platform_b1));
	int platform_b2_x = round(sprite_x(platform_b2));
	int platform_b2_y = round(sprite_y(platform_b2));
	int platformTy = round(sprite_y(platform_T));
	int platformTx = round(sprite_x(platform_T));
	int platform_x = round(sprite_x(platform_move));
	int platform_y = round(sprite_y(platform_move));

	if (person_y == platform_b1_y - PERSON_HEIGHT && person_x <= platform_b1_x + PLATFORM_B_1_W - 1 && person_x >= platform_b1_x) {
		on_ground = true;
	} else if (person_y == platform_b2_y - PERSON_HEIGHT && person_x <= platform_b2_x + PLATFORM_B_1_W - 1 && person_x >= platform_b2_x) {
		on_ground = true;
	} else if (person_y == platform_y - PERSON_HEIGHT && person_x <= platform_x + PLATFORM_WIDTH -1 && person_x >= platform_x) {
		on_ground = true;
	} else if (person_y == platformTy - PERSON_HEIGHT && person_x <= platformTx + PLATFORM_T_W -1 && person_x >= platformTx) {
		on_ground = true;
	} 
	
	if (person_dy < 0) {
		on_ground = false;
	}
}

void person_move(int keyInput) {

	int person_x = round(sprite_x(person));
	// int person_y = round(sprite_y(person));
	person_dx = sprite_dx(person);
	person_dy = sprite_dy(person);

	// Apply gravity if person is not on ground;
	if (!on_ground) {
		person_dy = person_dy + 0.008;
	} else if (on_ground) {
		person_dy = 0;
	} 

// Person moving left 
	if (keyInput == 261 && on_ground == true) {
		if (person_dx < .7) {
			person_dx = person_dx + 0.35;
		} 
	} else if (keyInput ==260 && person_x > 1 && on_ground == true) { //LEFY
		if (person_dx > -.7) {
			person_dx = person_dx - 0.35;
		}
	} else if (person_x <= 1 || person_x >= screen_width() -1 - PERSON_WIDTH) {
		person_dx = 0;
	}
	if (keyInput == 259 && on_ground == true) { // JUMP
		person_dy = -0.45;
		// draw_string(screen_width()-1, screen_height()-5. 'x')
	}

	// if I am !on_ground then horizontal

	//Move Person accoding to input speed set 
	sprite_turn_to(person, person_dx, person_dy);
	sprite_step(person);
}

bool sprite_collsion (sprite_id s1, int s1_width, int s1_height, sprite_id s2, int s2_width, int s2_height) {
	bool collided = true; 

	int px = round(sprite_x(s1));
	int py = round (sprite_y (s1));
	int pr = px + s1_width -1;
	int pb = py + s1_height -1;

	int zx = round(sprite_x(s2));
	int zy = round(sprite_y(s2));
	int zr = zx + s2_width -1;
	int zb = zy +s2_height -1;

	if (pr < zx ) {
		collided = false;
	}
	if (pb < zy){ 
		collided = false;
	}
	if  (zr < px) {
		collided = false;
	}
	if (zb < py) {
		collided = false;
	}
	return collided;
}

void platform_collision3 (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platforms are 
	int p_x = round(sprite_x(platform_move));
	int p_y = round(sprite_y(platform_move));
	int p_r = p_x + PLATFORM_MOVE_W;
	int p_b = p_y + PLATFORM_MOVE_H;
	
	bool collided = true;

	if (s_y >= p_b) {collided = false;}
	if (s_x >= p_r) {collided = false;}
	if (p_x >= s_r) {collided = false;}
	if (p_y >= s_b) {collided = false;}
	if (collided) {
		if (who_moved == person) {
			if (s_b == p_b -1) {
				person_dy = 0;
			} else if (s_r -1 == p_x  && person_dx > 0) {
				person_dx = 0;
			} else if (s_x == p_r -1 && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} 
	else {
		sprite_move_to( person, sprite_x(person), sprite_y(platform_move) + PLATFORM_HEIGHT );
	}
}
}

void platform_collision2 (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(platform_T));
	int pl_y = round(sprite_y(platform_T));
	int pl_r = pl_x + PLATFORM_T_W;
	int pl_b = pl_y + PLATFORM_T_H;

	
	bool collided = true;
//Check other platform collision

	if (s_y >= pl_b) {collided = false;}
	if (s_x >= pl_r) {collided = false;}
	if (pl_x >= s_r) {collided = false;}
	if (pl_y >= s_b) {collided = false;}


	if (collided) {
		if (who_moved == person) {
			if (s_b == pl_b -1) {
				person_dy = 0;
			} else if (s_r -1 == pl_x  && person_dx > 0) {
				person_dx = 0;
			} else if (s_x == pl_r -1 && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} 
}
}

void platform_move1 (void) {
	int platformM_x = round(sprite_x(platform_move));

	double platformM_dx = sprite_dx(platform_move);
	double platformM_dy = sprite_dy(platform_move);

	sprite_step(platform_move);

	//If zombie is touching the edge change direction

	if ( platformM_x <= 0 ) {
		platformM_dx = fabs(platformM_dx);
	} 
	else if ( platformM_x >= screen_width() - PLATFORM_MOVE_W ) {
		platformM_dx = -fabs(platformM_dx);
	}

	//Check to see if zombine needs to change direction

	if ( platformM_dx != sprite_dx( platform_move ) || platformM_dy != sprite_dy(platform_move) ) {
	sprite_back( platform_move );
	sprite_turn_to( platform_move, platformM_dx, platformM_dy );
	}
}


void processes3() {
	process_timer();
	platform_move1();
	person_ground3();
	int keyInput = get_char();
	person_move(keyInput);

	platform_collision2(person);
	platform_collision3(person);
	int person_y = round(sprite_y(person));
	
	if (person_y > screen_height()) {
		person_dx = 0;
		lives = lives - 1;

		clear_screen();
		drawSprites3();

	}



	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, door, EXIT_WIDTH, EXIT_HEIGHT)== true){
		score = score + 100;
		level = level + 1;
		person_dx = 0;

		clear_screen();
		drawSprites3();
	}

	clear_screen();
	sprite_draw(person);
	sprite_draw(platform_move);
	sprite_draw(platform_b1);
	sprite_draw(platform_b2);
	sprite_draw(platform_T);
	sprite_draw(door);
	display_time();
	draw_border();

}

void gameOver() {
	draw_string(screen_width()/2 - 7, screen_height()/2, "Game Over");
	draw_string(screen_width()/2 - 10, screen_height()/2 + 2, "Press any key to exit");
	show_screen();
	wait_char();
}

int main(void) {
	setup_screen();
	setup_timer();
	drawSprites3();
	draw_border();
	show_screen();

	while ( !game_over ) {
		process_timer();
		processes3();
		if ( update_screen ) {
			show_screen();
		}
		timer_pause(DELAY);
	}
	clear_screen();
	gameOver();
	// cleanup();

	return 0;
}







