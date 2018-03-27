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
int keyN = 0;
int barrierN = 0;
int trophyN = 0;
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

#define PLATFORM_4_W (screen_width() * 0.6)
#define PLATFORM_4_H (1)

#define MONSTER_WIDTH (3)
#define MONSTER_HEIGHT (2)

#define TREASURE_WIDTH (3)
#define TREASURE_HEIGHT (3)

#define PLATFORM_T_W (12)
#define PLATFORM_T_H (1)

#define KEY_WIDTH (3)
#define KEY_HEIGHT (3)

#define PLATFORM5_W (screen_width() * 0.5)

#define ROCK_W (4)
#define ROCK_H (2)

#define TROPHY_W (3)
#define TROPHY_H (4)

// Defining Global Variables 
bool game_over = false;
bool update_screen = true;
bool on_ground = true;
bool enable_keys = true;
bool treasuretaken = false; 
bool keytaken = false;
bool barrier_C = false;
bool on_groundr = true;

//level 1
sprite_id person;
sprite_id door;
sprite_id zombie;
sprite_id platform;
sprite_id platform_bottom;
//level 2
sprite_id platformTop;
sprite_id monster;
sprite_id treasure;
//level 3
sprite_id platform_b1;
sprite_id platform_b2;
sprite_id platform_move;
sprite_id platform_T;

//level 4
sprite_id barrier;
sprite_id platform42;
sprite_id platform43;
sprite_id platform44;
sprite_id key;

//level 5
sprite_id platform52; 
sprite_id platform53;
sprite_id rock;
sprite_id trophy; 

timer_id my_timer;
int minute;
int second;

double person_dx = 0;
double person_dy = 0;
double rock_dy = 0;

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

 char * exit1_image = 
 /**/ "EXIT"
 /**/ "|o|"
 /**/ "|||"
 /**/ "/ |";

char * platform_image = "=========================================================================================================================================================================================";
/**/ 

char * rock_image = 
/**/ "/~~\\"
/**/ "\\~~/";

char * trophy_image = 
/**/ "'- "
/**/ "/ \\"
/**/ "\\ /"
/**/ " @'";

char * trophy2_image = 
/**/ " -'"
/**/ "/ \\"
/**/ "\\ /"
/**/ "'@ ";

char * trophy3_image = 
/**/ " - `"
/**/ "/ \\"
/**/ "\\ /"
/**/ ".@ ";

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

void drawSprites5 (void) {

	double x_p = 4;
	double y_p = screen_height() - 4;
	person = sprite_create(x_p, y_p, PERSON_WIDTH, PERSON_HEIGHT, person_img);
	sprite_draw(person);

	double x_b1 = 0;
	double y_b1 = screen_height() - 1;
	platform_b1 = sprite_create(x_b1, y_b1, PLATFORM_B_1_W, PLATFORM_B_1_H, platform_image);
	sprite_draw(platform_b1);

	double x_p2 = screen_width() / 2 - 1;
	double y_p2 = screen_height() - 12;
	platform52 = sprite_create (x_p2, y_p2, PLATFORM5_W, PLATFORM_HEIGHT, platform_image);
	sprite_draw(platform52);

	double x_p3 = 1;
	double y_p3 = screen_height() - 23;
	platform53 = sprite_create (x_p3, y_p3, PLATFORM5_W, PLATFORM_B_HEIGHT, platform_image);
	sprite_draw(platform53);

	double x_b = PLATFORM5_W / 2;
	double y_b = y_p3 - ROCK_H; 
	rock = sprite_create (x_b, y_b, ROCK_W, ROCK_H, rock_image);
	sprite_draw(rock);

	double x_t = screen_width() / 2 - 1;
	double y_y = screen_height() - 35;
	trophy = sprite_create(x_t, y_y, TROPHY_W, TROPHY_H, trophy_image);
	sprite_draw(trophy);

	sprite_turn_to( platform52, -0.35, 0);

	sprite_turn_to( platform53, 0.35, 0);

	sprite_turn_to( rock, .49, rock_dy);
}

void person_ground5(void) {

	int person_x = round(sprite_x(person));
	int person_y = round(sprite_y(person));
	on_ground = false;
	int platform_b_y = round(sprite_y(platform_b1));
	int platform_b_x = round (sprite_x(platform_b1));
	int platform52y = round(sprite_y(platform52));
	int platform52x= round(sprite_x(platform52));
	int platform53x = round(sprite_x(platform53));
	int platform53y = round(sprite_y(platform53));


	if (person_y == platform_b_y - PERSON_HEIGHT && person_x <= platform_b_x + PLATFORM_B_1_W - 1 && person_x >= platform_b_x) {
		on_ground = true;
	} else if (person_y == platform52y - PERSON_HEIGHT && person_x <= platform52x + PLATFORM5_W -1 && person_x >= platform52x) {
		on_ground = true;
	} else if (person_y == platform53y - PERSON_HEIGHT && person_x <= platform53x + PLATFORM5_W -1 && person_x >= platform53x) {
		on_ground = true;
	} 
	if (person_dy < 0) {
		on_ground = false;
	}
}


void rock_ground(void) {

	int rock_x = round(sprite_x(rock));
	int rock_y = round(sprite_y(rock));
	on_groundr = false;
	int platform_b_y = round(sprite_y(platform_b1));
	int platform_b_x = round (sprite_x(platform_b1));
	int platform52y = round(sprite_y(platform52));
	int platform52x= round(sprite_x(platform52));
	int platform53x = round(sprite_x(platform53));
	int platform53y = round(sprite_y(platform53));


	if (rock_y == platform_b_y - PERSON_HEIGHT && rock_x <= platform_b_x + PLATFORM_B_1_W && rock_x >= platform_b_x) {
		on_groundr = true;
	} else if (rock_y == platform52y - PERSON_HEIGHT && rock_x <= platform52x + PLATFORM5_W && rock_x >= platform52x) {
		on_groundr = true;
	} else if (rock_y == platform53y - PERSON_HEIGHT && rock_x <= platform53x + PLATFORM5_W && rock_x >= platform53x) {
		on_groundr = true;
	} 
	if (rock_dy < 0) {
		on_groundr = false;
	}
}

void rock_move (void) {
	int rock_x = round(sprite_x(rock));

	double rock_dx = sprite_dx(rock);
	rock_dy = sprite_dy(rock);

	//If zombie is touching the edge change direction
	if (!on_groundr) {
		rock_dy = rock_dy + 0.008;
	} else if (on_groundr) {
		rock_dy = 0;
	} 

	if ( rock_x <= 0 ) {
		rock_dx = fabs(rock_dx);
	} 
	else if ( rock_x >= screen_width() - ROCK_W ) {
		rock_dx = -fabs(rock_dx);
	}

	//Check to see if zombine needs to change direction

	sprite_turn_to (rock, rock_dx, rock_dy);
	sprite_step(rock);
}

void platform_move3 (void) {
	int platformM_x = round(sprite_x(platform53));

	double platformM_dx = sprite_dx(platform53);
	double platformM_dy = sprite_dy(platform53);

	sprite_step(platform53);

	//If zombie is touching the edge change direction

	if ( platformM_x <= 0 ) {
		platformM_dx = fabs(platformM_dx);
	} 
	else if ( platformM_x >= screen_width() - PLATFORM5_W ) {
		platformM_dx = -fabs(platformM_dx);
	}

	//Check to see if zombine needs to change direction

	if ( platformM_dx != sprite_dx( platform53 ) || platformM_dy != sprite_dy(platform53) ) {
	sprite_back( platform53 );
	sprite_turn_to( platform53, platformM_dx, platformM_dy );
	}
}

void platform_move2 (void) {
	int platformM_x = round(sprite_x(platform52));

	double platformM_dx = sprite_dx(platform52);
	double platformM_dy = sprite_dy(platform52);

	sprite_step(platform52);

	//If zombie is touching the edge change direction

	if ( platformM_x <= 0 ) {
		platformM_dx = fabs(platformM_dx);
	} 
	else if ( platformM_x >= screen_width() - PLATFORM5_W ) {
		platformM_dx = -fabs(platformM_dx);
	}

	//Check to see if zombine needs to change direction

	if ( platformM_dx != sprite_dx( platform52 ) || platformM_dy != sprite_dy(platform52) ) {
	sprite_back( platform52 );
	sprite_turn_to( platform52, platformM_dx, platformM_dy );
	}
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



void person_move(int keyInput) {

	int person_x = round(sprite_x(person));
	int person_y = round(sprite_y(person));
	// int person_y = round(sprite_y(person));
	person_dx = sprite_dx(person);
	person_dy = sprite_dy(person);

	// Apply gravity if person is not on ground;
	if (!on_ground) {
		person_dy = person_dy + 0.008;
	} else if (on_ground) {
		person_dy = 0;
	} 

	if (person_y < 3) {
		person_dy = 0.008;
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

	}

	sprite_turn_to(person, person_dx, person_dy);
	sprite_step(person);
}

void platform_collision7 (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(platform52));
	int pl_y = round(sprite_y(platform52));
	int pl_r = pl_x + PLATFORM5_W;
	int pl_b = pl_y + PLATFORM_HEIGHT;

	
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
			} else if (s_x == pl_r && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} else {
			sprite_move_to( person, sprite_x(person), sprite_y(platform53) + PLATFORM_HEIGHT + PERSON_HEIGHT );
	}
}
}

void platform_collision8 (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(platform53));
	int pl_y = round(sprite_y(platform53));
	int pl_r = pl_x + PLATFORM5_W;
	int pl_b = pl_y + PLATFORM_HEIGHT;

	
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
			} else if (s_x == pl_r && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} else {
			sprite_move_to(person, sprite_x(person), sprite_y(platform53) + PLATFORM_HEIGHT+ PERSON_HEIGHT );
	}
}
}

void processes5(void) {
	process_timer();
	person_ground5();
	rock_ground();

	int keyInput = get_char();
	person_move(keyInput);
	rock_move();
	platform_move2();
	platform_move3();

	platform_collision8(person);
	platform_collision7(person);

	if (trophyN == 0) {
		sprite_set_image( trophy, trophy_image);
		trophyN = trophyN + 1;
	} else if (trophyN == 1) {
		sprite_set_image( trophy, trophy2_image);
		trophyN = trophyN - 1;		
	} 

	int person_y = round(sprite_y(person));
	if (person_y > screen_height()) {
		person_dx = 0;
		lives = lives - 1;

		clear_screen();

		drawSprites5();
	}

	int rock_y = round(sprite_y(rock));
	if (rock_y > screen_height()) {
		
		sprite_move_to( rock, 10, 3 );
		clear_screen();
		sprite_draw(person);
		sprite_draw(platform_b1);
		sprite_draw(platform52);
		sprite_draw(platform53);
		sprite_draw(rock);
		sprite_draw(trophy);
		draw_border();
		display_time();
		

	}
	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, rock, ROCK_W, ROCK_W)) {
		lives = lives - 1;

		clear_screen();
		drawSprites5();
	}

	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, trophy, TROPHY_W, TROPHY_H)) {
		score = score + 1000;

		game_over = true;
	}
	clear_screen();
	sprite_draw(person);
	sprite_draw(platform_b1);
	sprite_draw(platform52);
	sprite_draw(platform53);
	sprite_draw(rock);
	sprite_draw(trophy);
	draw_border();
	display_time();
}
void gameOver() {
	while ( get_char() >= 0 ) {
	draw_string(screen_width()/2 - 7, screen_height()/2, "Game Over");
	draw_string(screen_width()/2 - 10, screen_height()/2 + 2, "Press any key to exit");
	draw_formatted (screen_width()/2 - 6, screen_height()/2 + 4, "Score: %d", score);
	show_screen();
	wait_char();
}
}

int main(void) {
	setup_screen();
	setup_timer();
	drawSprites5();
	draw_border();

	show_screen();



	while ( !game_over ) {
		process_timer();
		processes5();
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

