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
int keyM = 0;
int barrierN = 0;
int monsterN = 0;
int treasureN = 0;
int trophyN = 0;

#define DELAY (10)

#define PERSON_WIDTH (3)
#define PERSON_HEIGHT (3)

#define ZOMBIE_WIDTH (4)
#define ZOMBIE_HEIGHT (4)

#define PLATFORM_WIDTH ((screen_width()/2.5))
#define PLATFORM_HEIGHT (1)

#define PLATFORM_L_2_WIDTH (PLATFORM_WIDTH / 3)
#define PLATFORML2_HEIGHT (1)

#define EXIT_WIDTH (4)
#define EXIT_HEIGHT (4)

#define PLATFORM_B_WIDTH (screen_width())
#define PLATFORM_B_HEIGHT (1)

#define MONSTER_WIDTH (3)
#define MONSTER_HEIGHT (2)

#define TREASURE_WIDTH (3)
#define TREASURE_HEIGHT (3)

#define PLATFORM_T_W (12)
#define PLATFORM_T_H (1)

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
bool treasuretaken1 = false; 
bool keytaken = false;
bool barrier_C = false;
bool on_groundr = true;

sprite_id person;
sprite_id door;
sprite_id door2;
sprite_id zombie;
sprite_id platform;
sprite_id platform_b1;
sprite_id platform_b2;
sprite_id platformTop;
sprite_id monster;
sprite_id treasure;
sprite_id platform_bottom;
sprite_id platform_move;
sprite_id platform_T;
sprite_id treasure1;
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

char * person2_img = 
/**/ "\\o/"
/**/ " | "
/**/ "/ \\";

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
/**/ "|o |"
/**/ "/| |"
/**/ "//   |";

char * exit2_image = 
/**/ "EXIT"
/**/ "|  |"
/**/ "|/.|"
/**/ "|//  |";
char * platform_image = "=================================================================================================================================================================================================================================================";
/**/ 

char * monster_image = 
/**/ " | "
/**/ "/ \\";

char * monster2_image = 
/**/ "\\ /"
/**/ " | ";

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

char * barrier_image = 
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]"
/**/ "[]";

char * key_image = 
/**/ ".  "
/**/ "0-+"
/**/ "  '";

char * key2_image = 
/**/ "  ."
/**/ "0-+"
/**/ "'  ";

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


// Function to draw border in screen 

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


// Function to setup screen
void setup(void) {
	// // Person setup 

	double x_p = 4;
	double y_p = screen_height() - 4;
	person = sprite_create(x_p, y_p, PERSON_WIDTH, PERSON_HEIGHT, person_img);
	sprite_draw(person);
	// Zombie Setup
	double x_z = screen_width()-15;
	double y_z = screen_height()-5;

	zombie = sprite_create(x_z, y_z, ZOMBIE_WIDTH, ZOMBIE_WIDTH, zombie_image);
	sprite_draw(zombie);
	//Platform Setup
	double x_pl = screen_width()*0.33;
	double y_pl = screen_height() - 12.5;

	platform = sprite_create(x_pl, y_pl, PLATFORM_WIDTH, PLATFORM_HEIGHT, platform_image);
	sprite_draw(platform);
	// Exit Setup
	double x_e = screen_width() - 7;
	double y_e = screen_height() - 5;

	door = sprite_create(x_e, y_e, EXIT_WIDTH, EXIT_HEIGHT, exit_image);
	sprite_draw (door);

	// Bottom Platform set-up
	double x_b = 0;
	double y_b = screen_height() - 1;

	platform_bottom = sprite_create(x_b, y_b, screen_width(), PLATFORM_B_HEIGHT, platform_image);
	sprite_draw(platform_bottom);
	//Zombie to move
	sprite_turn_to( zombie, -0.4, 0);

	show_screen();

}

void drawSprite2(void) {
	double x_p = 4;
	double y_p = screen_height() - 4;
	person = sprite_create(x_p, y_p, PERSON_WIDTH, PERSON_HEIGHT, person_img);
	sprite_draw(person);

		//Platform Setup
	double x_pl = screen_width()*0.33;
	double y_pl = screen_height() - 12.5;

	platform = sprite_create(x_pl, y_pl, PLATFORM_WIDTH, PLATFORM_HEIGHT, platform_image);
	sprite_draw(platform);
	// Exit Setup
	double x_e = screen_width() - 7;
	double y_e = screen_height() - 5;

	door = sprite_create(x_e, y_e, EXIT_WIDTH, EXIT_HEIGHT, exit_image);
	sprite_draw (door);

	// Bottom Platform set-up
	double x_b = 0;
	double y_b = screen_height() - 1;

	platform_bottom = sprite_create(x_b, y_b, screen_width(), PLATFORM_B_HEIGHT, platform_image);
	sprite_draw(platform_bottom);

	double x_pl2 = screen_width()*0.33 + screen_width()/9;
	double y_pl2 = screen_height() - 24;

	platformTop = sprite_create(x_pl2, y_pl2, PLATFORM_L_2_WIDTH, PLATFORML2_HEIGHT, platform_image);
	sprite_draw(platformTop);

	double x_m = screen_width()-15;
	double y_m = screen_height()- 3;

	monster = sprite_create(x_m, y_m, MONSTER_WIDTH, MONSTER_HEIGHT, monster_image);
	sprite_draw(monster);
	//Platform Setu

	double x_t = screen_width()/2 - 1;
	double y_t = screen_height() - 32.5;

	treasure = sprite_create(x_t, y_t, TREASURE_WIDTH, TREASURE_HEIGHT, treasure_image);
	sprite_draw(treasure);

	sprite_turn_to( monster, -0.3, 0);

	show_screen();


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
	door2 = sprite_create(x_e, y_e, EXIT_WIDTH, EXIT_HEIGHT, exit_image);
	sprite_draw (door2);

	double x_b1 = 0;
	double y_b1 = screen_height() - 1;
	platform_b1 = sprite_create(x_b1, y_b1, PLATFORM_B_1_W, PLATFORM_B_1_H, platform_image);
	sprite_draw(platform_b1);

	double x_b2 = screen_width() * 0.75 -1;
	double y_b2 = screen_height() - 1;
	platform_b2 = sprite_create(x_b2, y_b2, PLATFORM_B_1_W, PLATFORM_B_1_H, platform_image);
	sprite_draw(platform_b2);

	double x_t = screen_width() * .875 - 1;
	double y_t = screen_height() - 4;
	treasure1 = sprite_create(x_t, y_t, TREASURE_WIDTH, TREASURE_HEIGHT, treasure_image);
	sprite_draw(treasure1);

	sprite_turn_to( platform_move, -0.35, 0);

	show_screen();

}

void drawSprites4(void) {
	double x_p = 4;
	double y_p = screen_height() - 4;
	person = sprite_create(x_p, y_p, PERSON_WIDTH, PERSON_HEIGHT, person_img);
	sprite_draw(person);

	double x_e = screen_width() - 7;
	double y_e = screen_height() - 5;
	door = sprite_create(x_e, y_e, EXIT_WIDTH, EXIT_HEIGHT, exit_image);
	sprite_draw (door);

	double x_barr = screen_width() * 0.8;
	double y_barr = screen_height() - 12;
	barrier = sprite_create(x_barr, y_barr, 2, 11, barrier_image);
	sprite_draw(barrier);

	double x_b = 0;
	double y_b = screen_height() - 1;
	platform_bottom = sprite_create(x_b, y_b, screen_width(), PLATFORM_B_HEIGHT, platform_image);
	sprite_draw(platform_bottom);

	double x_p2 = screen_width() * 0.4;
	double y_p2 = screen_height() - 13;
	platform42 = sprite_create(x_p2, y_p2, PLATFORM_4_W, PLATFORM_4_H, platform_image);
	sprite_draw(platform42);

	double x_p3 = 1;
	double y_p3 = screen_height() - 25;
	platform43 = sprite_create(x_p3, y_p3, PLATFORM_4_W, PLATFORM_4_H, platform_image);
	sprite_draw(platform43);

	double x_p4 = screen_width()*0.4;
	double y_p4 = screen_height() - 37;
	platform44 = sprite_create(x_p4, y_p4, PLATFORM_4_W, PLATFORM_4_H, platform_image);
	sprite_draw(platform44);

	double x_t = screen_width() * 0.85;
	double y_t = screen_height() - 42;
	key = sprite_create(x_t, y_t, KEY_WIDTH, KEY_HEIGHT, key_image);
	sprite_draw(key);

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
// Determine whether the person is on the ground. 
void person_ground () {

	int person_x = round(sprite_x(person));
	int person_y = round(sprite_y(person));
	on_ground = false;
	int platform_b_y = round(sprite_y(platform_bottom));
	int platform_x = round(sprite_x(platform));
	int platform_y = round(sprite_y(platform));

	if (person_y >= platform_b_y - PERSON_HEIGHT) {
		on_ground = true;
	} else if (person_y == platform_y - PERSON_HEIGHT && person_x <= platform_x + PLATFORM_WIDTH && person_x >= platform_x) {
		on_ground = true;
} 
	if (person_dy < 0) {
		on_ground = false;
	}
}

void platform_collision (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(platform));
	int pl_y = round(sprite_y(platform));
	int pl_r = pl_x + PLATFORM_WIDTH;
	int pl_b = pl_y + 1;

	
	bool collided = true;
//Check other platform collision

	if (s_y >= pl_b) {collided = false;}
	if (s_x >= pl_r) {collided = false;}
	if (pl_x >= s_r) {collided = false;}
	if (pl_y >= s_b) {collided = false;}


	if (collided) {
		if (who_moved == person) {
			if (s_b == pl_b -1 && person_dy < 0) {
				person_dy = 0;
			} else if (s_r - 1 == pl_x && person_dx > 0) {
				person_dx = 0;
			} else if (s_x == pl_r - 1 && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} else {
		sprite_move_to (person, sprite_x(person), sprite_y(platform) - PLATFORM_HEIGHT);
	}
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


// Draw Border and Status Bar Code

// Declare Variables for border.. 

void zombie_move (void) {
	int zombie_x = round(sprite_x(zombie));

	double zombie_dx = sprite_dx(zombie);
	double zombie_dy = sprite_dy(zombie);

	sprite_step(zombie);

	//If zombie is touching the edge change direction

	if ( zombie_x <= 0 ) {
		zombie_dx = fabs(zombie_dx);
	} 
	else if ( zombie_x >= screen_width() - ZOMBIE_WIDTH ) {
		zombie_dx = -fabs(zombie_dx);
	}

	//Check to see if zombine needs to change direction

	if ( zombie_dx != sprite_dx( zombie ) || zombie_dy != sprite_dy(zombie) ) {
	sprite_back( zombie );
	sprite_turn_to( zombie, zombie_dx, zombie_dy );
	}
}

void person_move(int keyInput) {

	int person_x = round(sprite_x(person));
	int person_y = round(sprite_y(person));
	person_dx = sprite_dx(person);
	person_dy = sprite_dy(person);

	// Apply gravity if person is not on ground;
	if (!on_ground) {
		person_dy = person_dy + 0.008;
	} else if (on_ground) {
		sprite_set_image( person, person_img);
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
		sprite_set_image( person, person2_img);
		person_dy = -0.45;
	}

	sprite_turn_to(person, person_dx, person_dy);
	sprite_step(person);
}


void processes(void) {
	process_timer();
	zombie_move();
	person_ground();
	int keyInput = get_char();
	person_move(keyInput);

	platform_collision(person);
	
	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, zombie, ZOMBIE_WIDTH, ZOMBIE_HEIGHT)== true){
		lives = lives -1;

		// Reset movement speed of hero to 0
		person_dx = 0;

		clear_screen();
		setup();
	}
	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, door, EXIT_WIDTH, EXIT_HEIGHT)== true){
		
		sprite_hide(person);


		drawSprite2();
		person_dx = 0;	
		score = score + 100;
		level = level + 1;
		clear_screen();
		draw_border();
		drawSprite2();

		sprite_set_image(door, exit1_image);
		sprite_draw(door);
		timer_pause(150);
		show_screen();

		sprite_set_image(door, exit2_image);
		sprite_draw(door);
		timer_pause(150);
		show_screen();

		sprite_set_image(door, exit_image);
		sprite_draw(door);
		timer_pause(150);
		show_screen();
	}

	if (lives == 0) {
		game_over = true;

	}

	if (keyInput == 'l') {
		level = level + 1;
		drawSprite2();

	}

	clear_screen();
	sprite_draw(zombie);
	sprite_draw(platform);
	sprite_draw(platform_bottom);
	sprite_draw(person);
	sprite_draw(door);
	display_time();
	draw_border();
}

////////////////////////////PROCESSES 2//////////////////////////////////////////////////////////////


void monster_move(void) {
	int monster_x = round(sprite_x(monster));

	double monster_dx = sprite_dx(monster);
	double monster_dy = sprite_dy(monster);

	sprite_step(monster);

	if (monsterN == 0) {
		sprite_set_image( monster, monster2_image);
		monsterN = monsterN + 1;
	} else if (monsterN == 1) {
		sprite_set_image( monster, monster_image);	
		monsterN = monsterN - 1;	
	}

	//If zombie is touching the edge change direction

	if ( monster_x <= 0 ) {
		monster_dx = fabs(monster_dx);
	} 
	else if ( monster_x >= screen_width() - MONSTER_WIDTH ) {
		monster_dx = -fabs(monster_dx);
	}

	//Check to see if zombine needs to change direction

	if ( monster_dx != sprite_dx( monster ) || monster_dy != sprite_dy(monster) ) {
	sprite_back( monster );
	sprite_turn_to( monster, monster_dx, monster_dy );
	}
}

void platform_collision2 (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(platformTop));
	int pl_y = round(sprite_y(platformTop));
	int pl_r = pl_x + PLATFORM_L_2_WIDTH;
	int pl_b = pl_y + 1;

	
	bool collided = true;
//Check other platform collision

	if (s_y >= pl_b) {collided = false;}
	if (s_x >= pl_r) {collided = false;}
	if (pl_x >= s_r) {collided = false;}
	if (pl_y >= s_b) {collided = false;}


	if (collided) {
		if (who_moved == person) {
			if (s_b == pl_b -1 && person_dy < 0) {
				person_dy = 0;
			} else if (s_r - 1 == pl_x && person_dx > 0) {
				person_dx = 0;
			} else if (s_x == pl_r - 1 && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	}
}
}


void person_ground2(void) {

	int person_x = round(sprite_x(person));
	int person_y = round(sprite_y(person));
	on_ground = false;
	int platform_b_y = round(sprite_y(platform_bottom));
	int platform_L_2_y = round(sprite_y(platformTop));
	int platform_L_2_x = round(sprite_x(platformTop));
	int platform_x = round(sprite_x(platform));
	int platform_y = round(sprite_y(platform));

	if (person_y >= platform_b_y - PERSON_HEIGHT) {
		on_ground = true;
	} else if (person_y == platform_y - PERSON_HEIGHT && person_x <= platform_x + PLATFORM_WIDTH && person_x >= platform_x) {
		on_ground = true;
	} else if (person_y == platform_L_2_y - PERSON_HEIGHT && person_x <= platform_L_2_x + PLATFORM_L_2_WIDTH && person_x >= platform_L_2_x) {
		on_ground = true;
	} 
	if (person_dy < 0) {
		on_ground = false;
	}
}

void processes2() {
	process_timer();
	monster_move();
	person_ground2();
	int keyInput = get_char();
	person_move(keyInput);
	platform_collision(person);
	platform_collision2(person);

	if (treasureN == 0) {
		sprite_set_image( treasure, treasure2_image);
		treasureN = treasureN + 1;
	} else if (treasureN == 1) {
		sprite_set_image( treasure, treasure3_image);
		treasureN = treasureN + 1; 
	} else if (treasureN == 2) {
		sprite_set_image( treasure, treasure4_image);
		treasureN = treasureN + 1;
	} else if (treasureN == 3) {
		sprite_set_image( treasure, treasure_image);
		treasureN = 0;
	}
	
	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, monster, MONSTER_WIDTH, MONSTER_HEIGHT)== true){
		lives = lives - 1;

		// Reset movement speed of hero to 0
		person_dx = 0;

		clear_screen();
		drawSprite2();
	}
	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, door, EXIT_WIDTH, EXIT_HEIGHT)== true){
		score = score + 100;
		level = level + 1;
		drawSprites3();

		// Reset movement speed of hero to 0
		person_dx = 0;

		clear_screen();
		drawSprite2();
	}
	if (lives == 0) {
		game_over = true;
	}

	if (keyInput == 'l') {
		level = level + 1;
		drawSprites3();

	}

	if (treasuretaken == false) {

		if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, treasure, TREASURE_WIDTH, TREASURE_HEIGHT)== true && level == 2){
		score = score + 10;
		treasuretaken = true;
	}



	clear_screen();
	sprite_draw(monster);
	sprite_draw(platform);
	sprite_draw(platform_bottom);
	sprite_draw(platformTop);
	sprite_draw(person);
	sprite_draw(door);
	sprite_draw(treasure);
	display_time();
	draw_border();
} else {
		clear_screen();
		sprite_draw(monster);
		sprite_draw(platform);
		sprite_draw(platform_bottom);
		sprite_draw(platformTop);
		sprite_draw(person);
		sprite_draw(door);
		display_time();
		draw_border();
}
}

///////////////////////////////////////Level 3//////////////////////////////////////////
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

	if (person_y == platform_b1_y - PERSON_HEIGHT && person_x <= platform_b1_x + PLATFORM_B_1_W  && person_x >= platform_b1_x) {
		on_ground = true;
	} else if (person_y == platform_b2_y - PERSON_HEIGHT && person_x <= platform_b2_x + PLATFORM_B_1_W  && person_x >= platform_b2_x) {
		on_ground = true;
	} else if (person_y == platform_y - PERSON_HEIGHT && person_x <= platform_x + PLATFORM_WIDTH && person_x >= platform_x) {
		on_ground = true;
	} else if (person_y == platformTy - PERSON_HEIGHT && person_x <= platformTx + PLATFORM_T_W && person_x >= platformTx) {
		on_ground = true;
	} 
	
	if (person_dy < 0) {
		on_ground = false;
	}
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
			if (s_b == p_b -1 && person_dy < 0) {
				person_dy = 0;
			} else if (s_r -1 == p_x  && person_dx > 0) {
				person_dx = 0;
				person_dy = 0;
			} else if (s_x == p_r -1 && person_dx < 0) {
				person_dx = 0;
	
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
		} else {
			sprite_move_to( person, sprite_x(person), sprite_y(platform_move) - PERSON_HEIGHT );
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
		drawSprites4();

	}
	if (lives == 0) {
		game_over = true;

	}

	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, door2, EXIT_WIDTH, EXIT_HEIGHT)== true){
		score = score + 100;
		level = level + 1;
		person_dx = 0;


		clear_screen();
		drawSprites4();
	}
	if (keyInput == 'l') {
		level = level + 1;
		drawSprites4();

	}

	if (treasureN == 0) {
		sprite_set_image( treasure1, treasure2_image);
		treasureN = treasureN + 1;
	} else if (treasureN == 1) {
		sprite_set_image( treasure1, treasure3_image);
		treasureN = treasureN + 1; 
	} else if (treasureN == 2) {
		sprite_set_image( treasure1, treasure4_image);
		treasureN = treasureN + 1;
	} else if (treasureN == 3) {
		sprite_set_image( treasure1, treasure_image);
		treasureN = 0;
	}


	if (treasuretaken1 == false) {

		if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, treasure1, TREASURE_WIDTH, TREASURE_HEIGHT)== true) {
		score = score + 10;
		treasuretaken1 = true;
	}
	clear_screen();
	sprite_draw(person);
	sprite_draw(treasure1);
	sprite_draw(platform_move);
	sprite_draw(platform_b1);
	sprite_draw(platform_b2);
	sprite_draw(platform_T);
	sprite_draw(door2);
	display_time();
	draw_border();
} else {
	clear_screen();
	sprite_draw(person);
	sprite_draw(platform_move);
	sprite_draw(platform_b1);
	sprite_draw(platform_b2);
	sprite_draw(platform_T);
	sprite_draw(door2);
	display_time();
	draw_border();
}

}

/////////////////////////////Level 4 ///////////////////////////////////////////

void person_ground4(void) {

	int person_x = round(sprite_x(person));
	int person_y = round(sprite_y(person));
	on_ground = false;
	int platform_b_y = round(sprite_y(platform_bottom));
	int platform42y = round(sprite_y(platform42));
	int platform42x= round(sprite_x(platform42));
	int platform43x = round(sprite_x(platform43));
	int platform43y = round(sprite_y(platform43));
	int platform44x = round(sprite_x(platform44));
	int platform44y = round(sprite_y(platform44));


	if (person_y >= platform_b_y - PERSON_HEIGHT) {
		on_ground = true;
	} else if (person_y == platform42y - PERSON_HEIGHT && person_x <= platform42x + PLATFORM_4_W && person_x >= platform42x) {
		on_ground = true;
	} else if (person_y == platform43y - PERSON_HEIGHT && person_x <= platform43x + PLATFORM_4_W && person_x >= platform43x) {
		on_ground = true;
	} else if (person_y == platform44y - PERSON_HEIGHT && person_x <= platform44x + PLATFORM_4_W && person_x >= platform44x) {
		on_ground = true;
	} 
	if (person_dy < 0) {
		on_ground = false;
	}
}

void platform_collision4 (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(platform43));
	int pl_y = round(sprite_y(platform43));
	int pl_r = pl_x + PLATFORM_4_W;
	int pl_b = pl_y + PLATFORM_4_H;

	
	bool collided = true;
//Check other platform collision

	if (s_y >= pl_b) {collided = false;}
	if (s_x >= pl_r) {collided = false;}
	if (pl_x >= s_r) {collided = false;}
	if (pl_y >= s_b) {collided = false;}


	if (collided) {
		if (who_moved == person) {
			if (s_b == pl_b -1 && person_dy < 0) {
				person_dy = 0;
			} else if (s_r-1 == pl_x  && person_dx > 0) {
				person_dx = 0;
			} else if (s_x == pl_r-1 && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} 
}
}

void platform_collision5 (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(platform42));
	int pl_y = round(sprite_y(platform42));
	int pl_r = pl_x + PLATFORM_4_W;
	int pl_b = pl_y + PLATFORM_4_H;

	
	bool collided = true;
//Check other platform collision

	if (s_y >= pl_b) {collided = false;}
	if (s_x >= pl_r) {collided = false;}
	if (pl_x >= s_r) {collided = false;}
	if (pl_y >= s_b) {collided = false;}


	if (collided) {
		if (who_moved == person) {
			if (s_b == pl_b -1 && person_dy < 0) {
				person_dy = 0;
			} else if (s_r-1 == pl_x  && person_dx > 0) {
				person_dx = 0;
			} else if (s_x == pl_r-1 && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} 
}
}

void platform_collision6 (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(platform44));
	int pl_y = round(sprite_y(platform44));
	int pl_r = pl_x + PLATFORM_4_W;
	int pl_b = pl_y + PLATFORM_4_H;

	
	bool collided = true;
//Check other platform collision

	if (s_y >= pl_b) {collided = false;}
	if (s_x >= pl_r) {collided = false;}
	if (pl_x >= s_r) {collided = false;}
	if (pl_y >= s_b) {collided = false;}


	if (collided) {
		if (who_moved == person) {
			if (s_b == pl_b -1 && person_dy < 0) {
				person_dy = 0;
			} else if (s_r-1 == pl_x  && person_dx > 0) {
				person_dx = 0;
			} else if (s_x == pl_r-1 && person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} 
}
}

void barrier_collision (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platform2 is 
	int pl_x = round(sprite_x(barrier));
	int pl_y = round(sprite_y(barrier));
	int pl_r = pl_x + 2;
	int pl_b = pl_y + 12;

	
	bool collided = true;
//Check other platform collision

	if (s_y >= pl_b) {collided = false;}
	if (s_x >= pl_r) {collided = false;}
	if (pl_x >= s_r) {collided = false;}
	if (pl_y >= s_b) {collided = false;}


	if (collided && keytaken == false) {
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
		if (person_dx != 0) {
			collided = false;
	    }
	} 


}
}
void processes4(void) {
	process_timer();
	person_ground4();

	int keyInput = get_char();
	person_move(keyInput);

	platform_collision4(person);
	platform_collision5(person);
	platform_collision6(person);
	barrier_collision(person);

	if (keyM == 0) {
		sprite_set_image( key, key2_image);
		keyM = keyM + 1;
	} else if (keyM ==1) {
		sprite_set_image( key, key_image);
		keyM = keyM -1;
	}
	
	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, door, EXIT_WIDTH, EXIT_HEIGHT)== true){
		score = score + 100;
		level = level + 1;
		drawSprites5();


		// Reset movement speed of hero to 0
		person_dx = 0;

		clear_screen();
		drawSprites4();
	}
	if (lives == 0) {
		game_over = true;

	}
	if (keyInput == 'l') {
		level = level + 1;
		drawSprites5();

	}

	if (keytaken == false) {

		if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, key, KEY_WIDTH, KEY_HEIGHT)== true){
			keyN = keyN + 1;
			keytaken = true;

			clear_screen();
			display_time();
			sprite_draw(person);
			sprite_draw (door);
			sprite_draw(platform_bottom);
			sprite_draw(barrier);
			sprite_draw(platform42);
			sprite_draw(platform43);
			sprite_draw(platform44);
			draw_border();


			// Reset movement speed of hero to 0
		}
		clear_screen();
		display_time();
		sprite_draw(person);
		sprite_draw (door);
		sprite_draw(platform_bottom);
		sprite_draw(barrier);
		sprite_draw(platform42);
		sprite_draw(platform43);
		sprite_draw(platform44);
		sprite_draw(key);
		draw_border();

	} else if (keytaken == true && sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, barrier, 2, 12) == true) {
		barrierN = barrierN + 1;
		
		clear_screen();
		display_time();
		sprite_draw(person);
		sprite_draw (door);
		sprite_draw(platform_bottom);
		sprite_draw(platform42);
		sprite_draw(platform43);
		sprite_draw(platform44);
		draw_border();
	} else if (keytaken == true && barrierN > 0) {
		clear_screen();
		display_time();
		sprite_draw(person);
		sprite_draw (door);
		sprite_draw(platform_bottom);
		sprite_draw(platform42);
		sprite_draw(platform43);
		sprite_draw(platform44);
		draw_border();
	}
	else {
		clear_screen();
		display_time();
		sprite_draw(person);
		sprite_draw (door);
		sprite_draw(platform_bottom);
		sprite_draw(platform42);
		sprite_draw(platform43);
		sprite_draw(platform44);
		sprite_draw(barrier);
		draw_border();

	}
}


/////////////////////////////Level 5 /////////////////

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


	if (person_y == platform_b_y - PERSON_HEIGHT && person_x <= platform_b_x + PLATFORM_B_1_W  && person_x >= platform_b_x) {
		on_ground = true;
	} else if (person_y == platform52y - PERSON_HEIGHT && person_x <= platform52x + PLATFORM5_W && person_x >= platform52x) {
		on_ground = true;

	} else if (person_y == platform53y - PERSON_HEIGHT && person_x <= platform53x + PLATFORM5_W && person_x >= platform53x) {
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
			if (s_b == pl_b -1 && person_dy < 0) {
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
			if (s_b == pl_b -1 && person_dy < 0) {
				person_dy = 0;
			} else if (s_r -1 == pl_x  && person_dx > 0) {
				person_dx = 0;
			} else if (s_x == pl_r - 1&& person_dx < 0) {
				person_dx = 0;
			} else {
				person_dy = 0;
			}
		sprite_back(person);
		sprite_turn_to (person, person_dx, person_dy);
	} else {
			sprite_move_to(person, sprite_x(person), sprite_y(platform53) + PLATFORM_HEIGHT+ PLATFORM_HEIGHT );
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
	if (lives == 0) {
		game_over = true;

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
	if (keyInput == 'l') {
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
	draw_string(screen_width()/2 - 7, screen_height()/2 - 2, "Game Over");
	draw_string(screen_width()/2 - 10, screen_height()/2 + 0, "Press any key to exit");
	draw_formatted (screen_width()/2 - 6, screen_height()/2 + 2, "Score: %d", score);
	show_screen();
	wait_char();
}



int main(void) {
	setup_screen();
	setup_timer();
	setup();
	show_screen();

	while ( !game_over ) {
		process_timer();
		if (level == 1) {
			processes();
		} else if (level == 2) {
			processes2();
		} else if (level == 3) {
			processes3();
		} else if (level == 4) {
			processes4();
		} else if (level ==5) {
			processes5();
		}
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