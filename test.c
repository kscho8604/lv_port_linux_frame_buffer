#include <stdio.h>
#include <mysql/mysql.h>
#include "config.h"
#include "lvgl/lvgl.h"

static lv_obj_t *list1;
extern lv_font_t NotoSansKR_Regular_28;

void test_mysql(void)
{  
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      return;
  }

  mysql_options(con, MYSQL_SET_CHARSET_NAME, "utf8");
  mysql_options(con, MYSQL_INIT_COMMAND, "SET NAMES utf8");

  if (mysql_real_connect(con, DB_SERVER, DB_USERNAME, DB_PASSWD, 
          "sandbox", 0, NULL, 0) == NULL) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      return;
  }  

  if (mysql_query(con, "SELECT number, name, team FROM record where lane=1 and part=1")) 
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      mysql_close(con);
      return;
  }
 
  MYSQL_RES *res = mysql_store_result(con);
  if( res == NULL)
  {
      fprintf(stderr, "no result\n");
      mysql_close(con);
      return;
  }

  int num_fields = mysql_num_fields(res);

  MYSQL_ROW row;

    /*Create a list*/
    list1 = lv_list_create(lv_screen_active());
    lv_obj_set_size(list1, lv_pct(60), lv_pct(100));
    lv_obj_set_style_pad_row(list1, 5, 0);

    /*Add buttons to the list*/
    lv_obj_t * btn;

  while( row = mysql_fetch_row(res) ) 
  {
    char member[100];
    int l = 0;
    btn = lv_button_create(list1);
    lv_obj_set_width(btn, lv_pct(100));
    lv_obj_t *lab = lv_label_create(btn);
    l = sprintf(member, "테스트 :"); 
    for(int i = 0;i<num_fields;i++) {
      l+=sprintf(member+l, "%s ", row[i] ? row[i] : "NULL"); 
    }
    lv_label_set_text_fmt(lab, member);
    lv_obj_set_style_text_font(lab, &NotoSansKR_Regular_28, 0);
  }
  

  mysql_free_result(res);
  mysql_close(con);
}

