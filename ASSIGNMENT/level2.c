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
int monsterN = 0;

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

#define MONSTER_WIDTH (3)
#define MONSTER_HEIGHT (2)

#define TREASURE_WIDTH (3)
#define TREASURE_HEIGHT (3)

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
sprite_id platform_bottom;
sprite_id platformTop;
sprite_id monster;
sprite_id treasure;

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
	double y_pl2 = screen_height() - 22;

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

void monster_move(void) {
	int monster_x = round(sprite_x(monster));

	double monster_dx = sprite_dx(monster);
	double monster_dy = sprite_dy(monster);

	sprite_step(monster);


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
	int pl_b = pl_y + PLATFORML2_HEIGHT;

	
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

void platform_collision (sprite_id who_moved) {
// Determine where the person is
	int s_x = round(sprite_x(person));
	int s_y = round(sprite_y(person));
	int s_r = s_x + PERSON_WIDTH; 
	int s_b = s_y + PERSON_HEIGHT;
// Determine where platforms are 
	int p_x = round(sprite_x(platform));
	int p_y = round(sprite_y(platform));
	int p_r = p_x + PLATFORM_WIDTH;
	int p_b = p_y + PLATFORM_HEIGHT;
	
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
	} else if (person_y == platform_y - PERSON_HEIGHT && person_x <= platform_x + PLATFORM_WIDTH -1 && person_x >= platform_x) {
		on_ground = true;
	} else if (person_y == platform_L_2_y - PERSON_HEIGHT && person_x <= platform_L_2_x + PLATFORM_L_2_WIDTH -1 && person_x >= platform_L_2_x) {
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
		lives = lives -1;

		// Reset movement speed of hero to 0
		person_dx = 0;

		clear_screen();
		drawSprite2();
	}
	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, door, EXIT_WIDTH, EXIT_HEIGHT)== true){
		score = score + 100;


		// Reset movement speed of hero to 0
		person_dx = 0;

		clear_screen();
		drawSprite2();
	}

	if (treasuretaken == false) {

		if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, treasure, TREASURE_WIDTH, TREASURE_HEIGHT)== true && level == 1){
		score = score + 10;
		treasuretaken = true;

		// Reset movement speed of hero to 0
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

void gameOver() {
	draw_string(screen_width()/2 - 7, screen_height()/2, "Game Over");
	draw_string(screen_width()/2 - 10, screen_height()/2 + 2, "Press any key to exit");
	show_screen();
	wait_char();
}


int main(void) {
	setup_screen();
	setup_timer();
	drawSprite2();
	show_screen();


	while ( !game_over ) {
		if (monsterN == 0) {
		sprite_set_image( monster, monster2_image);
		monsterN = monsterN + 1;
		} else if (monsterN == 1) {
		sprite_set_image( monster, monster_image);	
		monsterN = monsterN - 1;	
	}
		process_timer();
		processes2();
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



