


#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"



void DrawLight(int x , int y , int r);
void DrawLight(int x , int y , int r) {
   int rad = r;
   while (rad > 0) {
      int l = (r - rad)*255/r;
      al_draw_filled_circle(x , y , rad , al_map_rgba(0,0,0,l));
      rad -= 15;
   }
}

int main(int argc , char** argv) {

   (void)argc;
   (void)argv;


   if (!al_init()) {
      return 1;
   }
   if (!al_init_image_addon()) {return 2;}
   if (!al_init_font_addon()) {return 3;}
   if (!al_init_ttf_addon()) {return 4;}
   if (!al_init_primitives_addon()) {return 5;}

   al_install_keyboard();
   al_install_mouse();

   al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
   ALLEGRO_DISPLAY* d = al_create_display(800,600);

   ALLEGRO_TIMER* t = al_create_timer(1.0/60.0);

   ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();

   al_register_event_source(q , al_get_timer_event_source(t));
   al_register_event_source(q , al_get_display_event_source(d));
   al_register_event_source(q , al_get_keyboard_event_source());
   al_register_event_source(q , al_get_mouse_event_source());

   ALLEGRO_BITMAP* lmap = al_create_bitmap(800,600);
   ALLEGRO_BITMAP* bg = al_load_bitmap("test.jpg");

  if (!bg || !lmap) {return 7;}

   int mx = 0;
   int my = 0;

   bool run = true;
   bool draw = true;
   while (run) {
      if (draw) {
         /// draw our light map
         al_set_target_bitmap(lmap);

         al_clear_to_color(al_map_rgba(0,0,0,0));

         al_set_separate_blender(ALLEGRO_ADD , ALLEGRO_ZERO , ALLEGRO_ZERO , ALLEGRO_ADD , ALLEGRO_ALPHA , ALLEGRO_ALPHA);
         DrawLight(0 , 0 , 100);
         DrawLight(mx , my , 100);

         al_set_target_backbuffer(d);
         al_clear_to_color(al_map_rgb(0,0,0));
         al_set_blender(ALLEGRO_ADD , ALLEGRO_ONE , ALLEGRO_ZERO);
         al_draw_bitmap(bg , 0 , 0 , 0);
         al_set_blender(ALLEGRO_ADD , ALLEGRO_ZERO , ALLEGRO_INVERSE_ALPHA);
         al_draw_bitmap(lmap , 0 , 0 , 0);
         al_flip_display();
         draw = false;
      }

      do {
         ALLEGRO_EVENT ev;
         al_wait_for_event(q , &ev);
         if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mx = ev.mouse.x;
            my = ev.mouse.y;
            draw = true;
         }
         if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            run = false;
         }
         if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            run = false;
         }
         if (ev.type == ALLEGRO_EVENT_TIMER) {
            draw = true;
         }
      } while (!al_is_event_queue_empty(q));

   }
   return 0;
}
