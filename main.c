#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void test_mysql(void);

int main(int argc, char **argv)
{
    lv_init();
 
   
    /*Linux frame buffer device init*/
    lv_display_t * disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, "/dev/fb0");

#if 0
	if(!lv_demos_create(&argv[1], argc - 1)) {
		lv_demos_show_help();
		goto demo_end;
	}
#else

        test_mysql();
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
