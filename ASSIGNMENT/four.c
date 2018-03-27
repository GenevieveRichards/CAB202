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
int exitN = 0;
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

// Defining Global Variables 
bool game_over = false;
bool update_screen = true;
bool on_ground = true;
bool enable_keys = true;
bool treasuretaken = false; 
bool keytaken = false;
bool barrier_C = false;


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

timer_id my_timer;
int minute;
int second;

double person_dx = 0;
double person_dy = 0;

char * person_img = 
/**/ 			 " o "
/**/			 "/|\\" 
/**/			 "/ \\";

char * person2_img = 
/**/ "\\o/ "
/**/ " |"
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
 /**/ "|o|"
 /**/ "|||"
 /**/ "/ |";

char * platform_image = "=========================================================================================================================================================================================";
/**/ 

char * monster_image = 
/**/ " | "
/**/ "/ \\";

char* treasure_image= 
/**/ "  ."
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
	} else if (person_y == platform42y - PERSON_HEIGHT && person_x <= platform42x + PLATFORM_4_W -1 && person_x >= platform42x) {
		on_ground = true;
	} else if (person_y == platform43y - PERSON_HEIGHT && person_x <= platform43x + PLATFORM_4_W -1 && person_x >= platform43x) {
		on_ground = true;
	} else if (person_y == platform44y - PERSON_HEIGHT && person_x <= platform44x + PLATFORM_4_W -1 && person_x >= platform44x) {
		on_ground = true;
	} 
	if (person_dy < 0) {
		on_ground = false;
	}
}

// void barrier_collision (void) {
// 	if (sprite_collsion (person, PERSON_WIDTH, PERSON_HEIGHT, barrier, 2, 12) && keytaken == false) {
// 		barrier_C = true; 
// 	}

// 	if (person_dx > 0) {
// 		barrier_C = false;
// 	}
// }

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

	if (person_dx < 0) {
		collided = false;
	}
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
	// if (exitN == 1) {
	// 	level = level + 1;
	// 	exitN = 0;

	// 	person_dx = 0;

	// 	clear_screen();
	// 	drawSprites4();
	// }
	
	if (sprite_collsion(person, PERSON_WIDTH, PERSON_HEIGHT, door, EXIT_WIDTH, EXIT_HEIGHT)== true){
		score = score + 100;
		exitN = 1;
		// drawSprite5();
		sprite_set_image( door, exit1_image);

		// Reset movement speed of hero to 0


		clear_screen();
		clear_screen();
		display_time();
		sprite_draw (door);
		sprite_draw(platform_bottom);
		sprite_draw(platform42);
		sprite_draw(platform43);
		sprite_draw(platform44);
		draw_border();


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

void gameOver() {
	draw_string(screen_width()/2 - 7, screen_height()/2, "Game Over");
	draw_string(screen_width()/2 - 10, screen_height()/2 + 2, "Press any key to exit");
	show_screen();
	wait_char();
}

int main(void) {
	setup_screen();
	setup_timer();
	drawSprites4();
	draw_border();

	show_screen();



	while ( !game_over ) {
		process_timer();
		processes4();
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











