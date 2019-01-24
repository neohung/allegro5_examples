#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_USTR *ustr;
ALLEGRO_EVENT my_event;
ALLEGRO_COLOR color;

float x = 10;
float y = 100;
void destroy_all(void) {
	if (ustr)
		al_ustr_free(ustr);
	if (display)
		al_destroy_display(display);
}

void draw(void) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	color = al_map_rgb(255, 255, 255);

	al_draw_circle(620, 460, 20, color, 2);
	al_draw_line(0, 0, al_get_display_width(display),
			al_get_display_height(display), al_map_rgb(255, 0, 0), 5.0);
	al_draw_rectangle(100, 100, 300, 300, al_map_rgb(0, 255, 0), 1);
	al_draw_ellipse(300, 300, 120, 50, al_map_rgb(0, 0, 255), 3);
	float points[8] = { 0.0f, 0.0f, 100.00f, 100.00f, 200.00f, 100.00f, 640.00f,
			150.00f };
	al_draw_spline(points, al_map_rgb(128, 128, 0), 8);

	float polygon[8] = { 100, 100, 100, 100 + 100, 100 + 100, 100 + 100, 100
			+ 100, 100 };
	//When the y-axis is facing downwards (the usual), the coordinates must be ordered anti-clockwise.
	al_draw_filled_polygon(polygon, 8, al_map_rgb(255, 255, 255));
	al_draw_polygon(polygon, 8, ALLEGRO_LINE_JOIN_BEVEL,
			al_map_rgb(255, 15, 15), 3, 1);

	al_draw_text(font, al_map_rgb(255, 255, 255), x, y, 0, "你好好");
	//al_draw_ustr(font, al_map_rgb(255, 0, 0), 100, 100, 0, ustr);
}
int main(int argc, char **argv) {
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_primitives_addon();
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(640, 480);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	al_set_window_title(display, "SET_TITLE");
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

	font=al_load_ttf_font("fzphfw.ttf",12,0);
	//font = al_load_ttf_font("simsun.ttc", 24, 0);
	if (!font) {
		fprintf(stderr, "failed to create font!\n");
		return -1;
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));

	ustr = al_ustr_new("你好");

	double t_now = 0.0;
	double t_pre = 0.0;
	while (1) {
		if (!al_is_event_queue_empty(queue)) {
			al_wait_for_event(queue, &my_event);
			//printf("my_event.keyboard.keycode=0x%x\n",my_event.keyboard.keycode);
			//<-,->,^, v, 0x52,0x53,0x54,0x55, enter 0x43
			if (my_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				destroy_all();
				exit(1);
			}
			if (my_event.keyboard.keycode == 0x52) {
				x = x - 10;
			}else if (my_event.keyboard.keycode == 0x53){
				x = x + 10;
			}else if (my_event.keyboard.keycode == 0x54){
				y = y - 10;
			}else if (my_event.keyboard.keycode == 0x55){
				y = y + 10;
			}

		} else {
			t_now = al_get_time();
			if (t_now - t_pre >= 0.033) {
				draw();
				al_flip_display();
				t_pre = t_now;
			} else {
				al_rest(0);
			}
		}
	}
	return 0;
}

