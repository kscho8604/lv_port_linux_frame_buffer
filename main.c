#include "lvgl/lvgl.h"
#include "src/drivers/lv_drivers.h"
#include "lvgl/demos/lv_demos.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void test_mysql(void);
void ui_init(void);

int main(int argc, char **argv)
{
    lv_init();
 
   
    /*Linux frame buffer device init*/
    lv_display_t * disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");

    lv_indev_t *mouse_indev = lv_evdev_create(LV_INDEV_TYPE_POINTER, "/dev/input/event0");

    LV_IMG_DECLARE(mouse_cursor_icon)
    lv_obj_t *cursor_obj = lv_img_create(lv_scr_act());
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);
    lv_indev_set_cursor(mouse_indev, cursor_obj);

#if 0
	if(!lv_demos_create(&argv[1], argc - 1)) {
		lv_demos_show_help();
		goto demo_end;
	}
#else

       test_mysql();
    //   ui_init();
#endif
	while(1) {
		uint32_t delay = lv_timer_handler();
		if(delay < 1 ) delay = 1;
		usleep(delay * 1000);
	}
demo_end:
	lv_deinit();
	
    	return 0;
}
