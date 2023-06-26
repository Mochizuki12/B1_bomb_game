#include <stdio.h>
#include <drawlib.h>
#include <stdlib.h>
#include <time.h>

#define dl_black dl_color_from_name("black")
#define dl_green dl_color_from_name("green")
#define dl_white dl_color_from_name("white")
#define dl_red dl_color_from_name("red")
#define dl_lgreen dl_color_from_rgb(155, 255, 155)
#define dl_lgreen2 dl_color_from_rgb(125, 255, 125)
#define dl_dkred dl_color_from_rgb(210, 0, 0)
#define dl_dpdkred dl_color_from_rgb(176, 0, 0)
#define dl_gray dl_color_from_rgb(150, 150, 150)
#define dl_dkgray dl_color_from_rgb(51, 51, 51)
#define dl_orange dl_color_from_rgb(255, 153, 0)
#define dl_blue dl_color_from_name("blue")
#define key_up DL_KEY_UP
#define key_down DL_KEY_DOWN
#define key_enter DL_KEY_ENTER
#define key DL_EVENT_KEY
#define mausL DL_EVENT_L_DOWN
#define dl_gold dl_color_from_rgb(255, 204, 0)

int start();                          /*スタート画面*/
int main_back_layer (int wait_time);  /*基本背景*/
int crash();                          /*ゲームオーバ画面*/
int load_layer();                     /*ロード画面*/
int noise_layer(int a);               /*背景ノイズ*/
int timer_layer();                    /*タイマーと爆発処理*/
int bomb_layer();                     /*爆弾の描画*/
int clear();                          /*クリアー画面*/
int over_bomb(int to);                /*爆発する時の処理*/
int clear_bomb(int tc);               /*爆発しない時の処理*/
int cut_layer(int x1, int y1);
int tm = 30, noi = 0, xg, yg;       /*tm(タイマーの数字) noi(走査線の数値) xg(マウスx軸の入力数値) yg(マウスy軸の入力数値)*/

/*ゲーム------------------------------------------------------------------------------------------------*/
int main (void){
  dl_initialize(1.0);
  int i = 2, x, y, d, k, over = 0, bomb = 1; /*over(あたり、はずれ、時間切れの数値) bomb(なし)*/
  tm = 30;
  xg = 0;
  yg = 0;
  i = start();
   if(i == 0){
       dl_stop();
       while(dl_get_event(&d, &k, &x, &y) != 0){
         }
       dl_resume();
       load_layer();
       dl_wait(1.0);
       over = timer_layer();
       switch(over){
       
         case -2:/*ゲームオーバー(時間切れ）*/
           main_back_layer(0);
           bomb_layer();
           clear_bomb(0);
           crash();
           dl_clear(dl_black);
           printf("Gameover\n");
           break;
         
         case -1:/*ゲームオーバ（導線を切ったとき）*/
           main_back_layer(0);
           bomb_layer();
           over_bomb(tm);
           dl_wait(1.0);
           crash();
           dl_clear(dl_black);
           printf("Gameover\n");
           break;
         
         case 1:/*クリアー*/
           main_back_layer(0);
           bomb_layer();
           clear_bomb(tm);
           dl_wait(1.0);
           noi = noise_layer(noi);       
           clear();
           while(dl_get_event(&d, &k, &x, &y) != 0){
              }
           main();
        }
       dl_wait(1.0);
    }
    return 0;
}

/*スタート画面------------------------------------------------------------------------------------------------*/
int start(){
  int e = 0, a, b, k = 0, d;
  dl_clear(dl_black);
  while(1){
   if (dl_get_event(&d, &k, &a, &b)){
     if(d == key){
       if(k == key_up){
         e = 0;
         while(dl_get_event(&d, &k, &a, &b) != 0){
         }
        }
       if(k == key_down){
         e = 1;
         while(dl_get_event(&d, &k, &a, &b) != 0){
         }
        }
       if(k == key_enter){
          return e;
          main();
         }
     }else{ 
     while(dl_get_event(&d, &k, &a, &b) != 0){}
   }
   }
   main_back_layer(0);
   dl_text("Lacky Bomb", 40, 100, 2, dl_white, 2);
   if(e == 0){
     dl_rectangle(40, 195, 610, 245, dl_white, 1, 1);
     dl_text("Start", 40, 240, 2, dl_green, 2);
     dl_text("Exit", 40, 301, 2, dl_white, 2);
    }
   else if(e == 1){
     dl_rectangle(40, 255, 610, 305, dl_white, 1, 1);
     dl_text("Start", 40, 240, 2, dl_white, 2);
     dl_text("Exit", 40, 301, 2, dl_green, 2);
    }
   noi = noise_layer(noi);  
   dl_wait(1.0);
   }
   return 0;
}

/*基本背景---------------------------------------------------------------------------------------------------------------*/
int main_back_layer (int wait_time){

    dl_rectangle(50, 50, 590, 430, dl_green, 1, 1);    /*main */
    dl_rectangle(30, 50, 50, 430, dl_green, 1, 1);     /*left side*/
    dl_rectangle(590, 50, 610, 430, dl_green, 1, 1);   /*right side*/
    dl_rectangle(50, 30, 590, 50, dl_green, 1, 1);     /*up*/
    dl_rectangle(50, 430, 590, 450, dl_green, 1, 1);   /*down*/
    dl_ellipse(50, 50, 20, 20, 0, 0, 360, dl_green, 1, 1);
    dl_ellipse(50, 430, 20, 20, 0, 0, 360, dl_green, 1, 1);
    dl_ellipse(590, 50, 20, 20, 0, 0, 360, dl_green, 1, 1);
    dl_ellipse(590, 430, 20, 20, 0, 0, 360, dl_green, 1, 1);
    dl_wait(wait_time);
    
    return 0;
}

/*ゲームオーバー画面--------------------------------------------------------------------------------------------------------*/
int crash(){

    dl_rectangle(50, 50, 590, 430, dl_red, 1, 1);    /*main */
    dl_rectangle(30, 50, 50, 430, dl_red, 1, 1);     /*left side*/
    dl_rectangle(590, 50, 610, 430, dl_red, 1, 1);   /*right side*/
    dl_rectangle(50, 30, 590, 50, dl_red, 1, 1);     /*up*/
    dl_rectangle(50, 430, 590, 450, dl_red, 1, 1);   /*down*/
    dl_ellipse(50, 50, 20, 20, 0, 0, 360, dl_red, 1, 1);
    dl_ellipse(50, 430, 20, 20, 0, 0, 360, dl_red, 1, 1);
    dl_ellipse(590, 50, 20, 20, 0, 0, 360, dl_red, 1, 1);
    dl_ellipse(590, 430, 20, 20, 0, 0, 360, dl_red, 1, 1);
    dl_wait(1.0);
    
    return 0;
}

/*背景の走査線-----------------------------------------------------------------------------------------------------------------*/
int noise_layer(int noi){
  dl_rectangle(30, 50+noi, 610, 51+noi, dl_lgreen, 1, 1);
   if(noi >= 340){
      noi = 0;
   }else{
   return noi+10;
   }
}

/*タイマーと爆破処理-----------------------------------------------------------------------------------------------------------*/
int timer_layer(){
  int d, k, x, y, tr ,t = 0; /*tr(あたり、ハズレの決定数値) t(あたり、ハズレ、時間切れの数値をmain関数へと返すための値)*/
  char time_sec_right[3];
  char time_sec_left[5] = {'0', '0', ':'};
  srand((unsigned int)time(NULL));
  tr = (rand() % 3 + 2) % 2;

  while(tm >= -1){
      main_back_layer(0);
      bomb_layer();
      dl_rectangle(200, 180, 440, 300, dl_gray, 10, 0);
      dl_rectangle(200, 180, 440, 300, dl_black, 1, 1);
      
      snprintf(time_sec_right, 3, "%d", tm);
      if(tm >= 10){
        dl_rectangle(220, 200, 420, 280, dl_black, 1, 1);
        dl_text(time_sec_right, 330, 260, 2, dl_white, 2);
        dl_text(time_sec_left, 230, 260, 2, dl_white, 2);
        noi = noise_layer(noi);
        dl_wait(1.0);
        }
      else if(tm <= 9){
        dl_rectangle(220, 200, 420, 280, dl_black, 1, 1);
        dl_text(time_sec_right, 370, 260, 2, dl_white, 2);
        dl_text(time_sec_left, 230, 260, 2, dl_white, 2);
        dl_text("0", 330, 260, 2, dl_white, 2);
        noi = noise_layer(noi);
        dl_wait(1.0);
        }
      tm -= 1;
      if (dl_get_event(&d, &k, &x, &y)){
           if(d == mausL){
             if((50<x && 80>x && 240<y && 250>y) || (50<x && 60>x && 250<y && 350>y) || (60<x && 300>x && 340<y && 350>y) || 
                (290<x && 300>x && 300<y && 340>y)){
                if(tr == 0){
                 cut_layer(x,y);
                 dl_wait(2.0);
                 t = -1;
                 return t;
                 break;
                    }
                else if(tr != 0){
                 cut_layer(x,y);
                 dl_wait(2.0);
                 t = 1;
                 return t;
                 break;
                   }
                 }
             if((560<x && 590>x && 240<y && 250>y) || (580<x && 590>x && 250<y && 350>y) || (340<x && 580>x && 340<y && 350>y) ||
                (340<x && 350>x && 300<y && 340>y)){
                if(tr == 0){
                 cut_layer(x,y);
                 dl_wait(2.0);
                 t = 1;
                 return t;
                 break;
                    }
                else if(tr != 0){
                 cut_layer(x,y);
                 dl_wait(2.0);
                 t = -1;
                 return t;
                 break;
                   }
                 }
          }else
           while(dl_get_event(&d, &k, &x, &y) != 0){ }
        }
      if(tm == -1){
       t = -2;
       return t;
       break;
       }
   }
}

/*爆弾-------------------------------------------------------------------------------------------------------------------------------*/
int bomb_layer(){
   dl_rectangle(90, 80, 550, 170, dl_dkred, 1, 1);    /*up*/
   dl_rectangle(80, 170, 560, 310, dl_red, 1, 1);   /*mid*/
   dl_rectangle(90, 310, 550, 400, dl_dpdkred, 1, 1);   /*down*/
   dl_rectangle(130, 75, 170, 405, dl_dkgray, 1, 1);
   dl_rectangle(470, 75, 510, 405, dl_dkgray, 1, 1);
   /*導線赤*/
   dl_rectangle(80, 240, 50, 250, dl_orange, 1, 1);
   dl_rectangle(50, 250, 60, 350, dl_orange, 1, 1);
   dl_rectangle(60, 340, 300, 350, dl_orange, 1, 1);
   dl_rectangle(290, 350, 300, 300, dl_orange, 1, 1);
   /*導線青*/
   dl_rectangle(560, 240, 590, 250, dl_blue, 1, 1);
   dl_rectangle(590, 250, 580, 350, dl_blue, 1, 1);
   dl_rectangle(580, 340, 340, 350, dl_blue, 1, 1);
   dl_rectangle(340, 350, 350, 300, dl_blue, 1, 1); 
    
}  

/*ロード画面-----------------------------------------------------------------------------------------------------------------------*/
int load_layer(){
  int i = 0, a, b, d = 0, k = 0;

  while(1){
   main_back_layer(0);
   dl_text("Press enter key", 40, 360, 2, dl_white, 2);
   if (dl_get_event(&d, &k, &a, &b)){
     if(d == key){
       if(k == key_enter){
         while(dl_get_event(&d, &k, &a, &b) != 0){
         }
         break;
        }
     }else{
       while(dl_get_event(&d, &k, &a, &b) != 0){}
        }
    }
   if(i == 0){
    dl_rectangle(550, 320, 560, 375, dl_white, 1, 1);
    i = 1;
    }else{
    dl_rectangle(550, 320, 560, 375, dl_green, 1, 1);
    i = 0;
    }
   noi = noise_layer(noi);
   dl_wait(1.0);
  }
}
/*クリアー画面-----------------------------------------------------------------------------------*/
int clear(){
  int a, b, d, k, i=0;
  while(1){
  main_back_layer(0);
  dl_text("Press enter key", 40, 360, 2, dl_white, 2);
  if(i == 0){
    dl_text("CLEAR!!", 220, 240, 2, dl_white, 3);
    dl_rectangle(550, 320, 560, 375, dl_white, 1, 1);
    i = 1;
  }
  else if(i == 1){
    dl_rectangle(280, 200, 400, 280, dl_green, 1, 1);
    dl_rectangle(550, 320, 560, 375, dl_green, 1, 1);
    i = 0;
  }
  if (dl_get_event(&d, &k, &a, &b)){
     if(d == key){
       if(k == key_enter){
         while(dl_get_event(&d, &k, &a, &b) != 0){
            }
         break;
         }
     }else{
        while(dl_get_event(&d, &k, &a, &b) != 0){}
        }
   }
  noi = noise_layer(noi);
  dl_wait(1.0);
  }
}
/*爆発するときの処理------------------------------------------------------------------------------*/
int over_bomb(int to){
  char time_sec_right[3];
  char time_sec_left[5] = {'0', '0', ':'};
  dl_rectangle(200, 180, 440, 300, dl_gray, 10, 0);
  dl_rectangle(200, 180, 440, 300, dl_black, 1, 1);
  while(to >= 0){
  
      snprintf(time_sec_right, 3, "%d", to);
      if(to >= 10){
        dl_rectangle(220, 200, 420, 280, dl_black, 1, 1);
        dl_text(time_sec_right, 330, 260, 2, dl_white, 2);
        dl_text(time_sec_left, 230, 260, 2, dl_white, 2);
        cut_layer(xg,yg);
        dl_wait(0.07);
        }
      else if(to <= 9){
        dl_rectangle(220, 200, 420, 280, dl_black, 1, 1);
        dl_text(time_sec_right, 370, 260, 2, dl_white, 2);
        dl_text(time_sec_left, 230, 260, 2, dl_white, 2);
        dl_text("0", 330, 260, 2, dl_white, 2);
        cut_layer(xg,yg);
        dl_wait(0.07);
        }
      to -= 1;
   }
}

/*爆発しない時の処理--------------------------------------------------------------------------------------------*/
int clear_bomb(int tc){
  char time_sec_right[3];
  char time_sec_left[5] = {'0', '0', ':'};
  tm += 1;
  dl_rectangle(200, 180, 440, 300, dl_gray, 10, 0);
  dl_rectangle(200, 180, 440, 300, dl_black, 1, 1);
  snprintf(time_sec_right, 3, "%d", tc);
      if(tc >= 10){
        dl_rectangle(220, 200, 420, 280, dl_black, 1, 1);
        dl_text(time_sec_right, 330, 260, 2, dl_white, 2);
        dl_text(time_sec_left, 230, 260, 2, dl_white, 2);
        cut_layer(xg,yg);
        dl_wait(1.0);
        }
      else if(tc <= 9){
        dl_rectangle(220, 200, 420, 280, dl_black, 1, 1);
        dl_text(time_sec_right, 370, 260, 2, dl_white, 2);
        dl_text(time_sec_left, 230, 260, 2, dl_white, 2);
        dl_text("0", 330, 260, 2, dl_white, 2);
        cut_layer(xg,yg);
        dl_wait(1.0);
        }
      
}
/*導線切断-------------------------------------------------------------------------------------------------------*/
int cut_layer(int x1, int y1){
  xg = x1;
  yg = y1;
  if((50<x1 && 80>x1 && 240<y1 && 250>y1)){
    if((50<x1 && 60>x1 && 240<y1 && 250>y1)){
      dl_rectangle(50, 240, 60, 250, dl_green, 1, 1);
      dl_rectangle(52, 249, 58, 250, dl_gold, 1, 1);
      dl_rectangle(59, 242, 60, 248, dl_gold, 1, 1);
     }else if(60<x1 && 70>x1 && 240<y1 && 250>y1){
      dl_rectangle(x1, y1+10, x1+10, y1-10, dl_green, 1, 1);
      dl_rectangle(x1, 242, x1+2, 248, dl_gold, 1, 1);
      dl_rectangle(x1+8, 242, x1+10, 248, dl_gold, 1, 1);
      }
     else{
      dl_rectangle(x1, y1+10, x1-10, y1-10, dl_green, 1, 1);
      dl_rectangle(x1, 242, x1-2, 248, dl_gold, 1, 1);
      dl_rectangle(x1-8, 242, x1-10, 248, dl_gold, 1, 1);
     }
  }
  else if((50<x1 && 60>x1 && 250<y1 && 350>y1)){
    if((50<x1 && 60>x1 && 340<y1 && 350>y1)){
      dl_rectangle(50, 340, 60, 350, dl_green, 1, 1);
      dl_rectangle(52, 340, 58, 341, dl_gold, 1, 1);
      dl_rectangle(59, 342, 60, 348, dl_gold, 1, 1);
     }else if((50<x1 && 60>x1 && 330<y1 && 340>y1)){
      dl_rectangle(x1+10, y1-10, x1-10, y1, dl_green, 1, 1);
      dl_rectangle(52, y1-8, 58, y1-10, dl_gold, 1, 1);
      dl_rectangle(52, y1, 58, y1-2, dl_gold, 1, 1);
     }else{
      dl_rectangle(x1+10, y1+10, x1-10, y1, dl_green, 1, 1);
      dl_rectangle(52, y1+8, 58, y1+10, dl_gold, 1, 1);
      dl_rectangle(52, y1, 58, y1+2, dl_gold, 1, 1);
      }
  }
  else if((60<x1 && 300>x1 && 340<y1 && 350>y1)){
    if((70<x1 && 90>x1 && 340<y1 && 350>y1)){
      dl_rectangle(x1-10, y1+10, x1, y1-10, dl_green, 1, 1);
      dl_rectangle(x1-10, 342, x1-8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1-2, 348, dl_gold, 1, 1);
     }else if(60<x1 && 70>x1 && 340<y1 && 350>y1){
      dl_rectangle(x1+10, y1+10, x1, y1-10, dl_green, 1, 1);
      dl_rectangle(x1+10, 342, x1+8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1+2, 348, dl_gold, 1, 1);
     }else if((90<x1 && 120>x1 && 340<y1 && 350>y1)||(170<x1 && 180>x1 && 340<y1 && 350>y1)){
      dl_rectangle(x1+10, y1+10, x1, y1-10, dl_dpdkred, 1, 1);
      dl_rectangle(x1+10, 342, x1+8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1+2, 348, dl_gold, 1, 1);
     }else if((120<x1 && 130>x1 && 340<y1 && 350>y1)||(180<x1 && 290>x1 && 340<y1 && 350>y1)){
      dl_rectangle(x1-10, y1+10, x1, y1-10, dl_dpdkred, 1, 1);
      dl_rectangle(x1-10, 342, x1-8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1-2, 348, dl_gold, 1, 1);
     }else if(130<x1 && 160>x1 && 340<y1 && 350>y1){
      dl_rectangle(x1+10, y1+10, x1, y1-10, dl_dkgray, 1, 1);
      dl_rectangle(x1+10, 342, x1+8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1+2, 348, dl_gold, 1, 1);
     }else if(160<x1 && 170>x1 && 340<y1 && 350>y1){
      dl_rectangle(x1-10, y1+10, x1, y1-10, dl_dkgray, 1, 1);
      dl_rectangle(x1-10, 342, x1-8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1-2, 348, dl_gold, 1, 1);
     }else if(290<x1 && 300>x1 && 340<y1 && 350>y1){
      dl_rectangle(290, 340, 300, 350, dl_dpdkred, 1, 1);
      dl_rectangle(292, 340, 298, 342, dl_gold, 1, 1);
      dl_rectangle(291, 342, 290, 348, dl_gold, 1, 1);
      }
   }
  else if(290<x1 && 300>x1 && 300<y1 && 340>y1){
    if(290<x1 && 300>x1 && 310<y1 && 330>y1){
      dl_rectangle(x1-10, y1, x1+10, y1+10, dl_dpdkred, 1, 1);
      dl_rectangle(292, y1+8, 298, y1+10, dl_gold, 1, 1);
      dl_rectangle(292, y1, 298, y1+2, dl_gold, 1, 1);
    }else if(290<x1 && 300>x1 && 330<y1 && 340>y1){
      dl_rectangle(x1-10, y1, x1+10, y1-10, dl_dpdkred, 1, 1);
      dl_rectangle(292, y1+8, 298, y1-10, dl_gold, 1, 1);
      dl_rectangle(292, y1, 298, y1-2, dl_gold, 1, 1);
    }else if(290<x1 && 300>x1 && 300<y1 && 310>y1){
      dl_rectangle(290, 307, 300, 310, dl_red, 1, 1);
      dl_rectangle(292, 310, 298, 309, dl_gold, 1, 1);
     }
  } 
  if((560<x1 && 590>x1 && 240<y1 && 250>y1)){
    if((580<x1 && 590>x1 && 240<y1 && 250>y1)){
      dl_rectangle(580, 240, 590, 250, dl_green, 1, 1);
      dl_rectangle(581, 242, 580, 248, dl_gold, 1, 1);
      dl_rectangle(582, 249, 588, 250, dl_gold, 1, 1);
    }else if(570<x1 && 580>x1 && 240<y1 && 250>y1){
      dl_rectangle(x1, y1+10, x1-10, y1-10, dl_green, 1, 1);
      dl_rectangle(x1, 242, x1-2, 248, dl_gold, 1, 1);
      dl_rectangle(x1-8, 242, x1-10, 248, dl_gold, 1, 1);
    }else{
      dl_rectangle(x1, y1+10, x1+10, y1-10, dl_green, 1, 1);
      dl_rectangle(x1, 242, x1+2, 248, dl_gold, 1, 1);
      dl_rectangle(x1+8, 242, x1+10, 248, dl_gold, 1, 1);
     }
  }
  else if((580<x1 && 590>x1 && 250<y1 && 350>y1)){
    if((580<x1 && 590>x1 && 340<y1 && 350>y1)){
      dl_rectangle(580, 340, 590, 350, dl_green, 1, 1);
      dl_rectangle(582, 340, 588, 341, dl_gold, 1, 1);
      dl_rectangle(580, 342, 581, 348, dl_gold, 1, 1);
     }else if((580<x1 && 590>x1 && 330<y1 && 340>y1)){
      dl_rectangle(x1+10, y1-10, x1-10, y1, dl_green, 1, 1);
      dl_rectangle(582, y1-8, 588, y1-10, dl_gold, 1, 1);
      dl_rectangle(582, y1, 588, y1-2, dl_gold, 1, 1);
     }else{
      dl_rectangle(x1+10, y1+10, x1-10, y1, dl_green, 1, 1);
      dl_rectangle(582, y1+8, 588, y1+10, dl_gold, 1, 1);
      dl_rectangle(582, y1, 588, y1+2, dl_gold, 1, 1);
      }
  }
  else if((340<x1 && 580>x1 && 340<y1 && 350>y1)){
      if((570<x1 && 580>x1 && 340<y1 && 350>y1)){
      dl_rectangle(x1-10, y1+10, x1, y1-10, dl_green, 1, 1);
      dl_rectangle(x1-10, 342, x1-8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1-2, 348, dl_gold, 1, 1);
     }else if(550<x1 && 570>x1 && 340<y1 && 350>y1){
      dl_rectangle(x1+10, y1+10, x1, y1-10, dl_green, 1, 1);
      dl_rectangle(x1+10, 342, x1+8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1+2, 348, dl_gold, 1, 1);
     }else if((510<x1 && 540>x1 && 340<y1 && 350>y1)||(350<x1 && 460>x1 && 340<y1 && 350>y1)){
      dl_rectangle(x1+10, y1+10, x1, y1-10, dl_dpdkred, 1, 1);
      dl_rectangle(x1+10, 342, x1+8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1+2, 348, dl_gold, 1, 1);
     }else if((540<x1 && 550>x1 && 340<y1 && 350>y1)||(460<x1 && 470>x1 && 340<y1 && 350>y1)){
      dl_rectangle(x1-10, y1+10, x1, y1-10, dl_dpdkred, 1, 1);
      dl_rectangle(x1-10, 342, x1-8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1-2, 348, dl_gold, 1, 1);
     }else if(470<x1 && 500>x1 && 340<y1 && 350>y1){
      dl_rectangle(x1+10, y1+10, x1, y1-10, dl_dkgray, 1, 1);
      dl_rectangle(x1+10, 342, x1+8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1+2, 348, dl_gold, 1, 1);
     }else if(500<x1 && 510>x1 && 340<y1 && 350>y1){
      dl_rectangle(x1-10, y1+10, x1, y1-10, dl_dkgray, 1, 1);
      dl_rectangle(x1-10, 342, x1-8, 348, dl_gold, 1, 1);
      dl_rectangle(x1, 342, x1-2, 348, dl_gold, 1, 1);
     }else if(340<x1 && 350>x1 && 340<y1 && 350>y1){
      dl_rectangle(340, 340, 350, 350, dl_dpdkred, 1, 1);
      dl_rectangle(351, 342, 350, 348, dl_gold, 1, 1);
      dl_rectangle(342, 340, 348, 341, dl_gold, 1, 1);
      }
   }
  else if(340<x1 && 350>x1 && 300<y1 && 340>y1){
    if(340<x1 && 350>x1 && 300<y1 && 330>y1){
      dl_rectangle(x1-10, y1, x1+10, y1+10, dl_dpdkred, 1, 1);
      dl_rectangle(342, y1+8, 348, y1+10, dl_gold, 1, 1);
      dl_rectangle(342, y1, 348, y1+2, dl_gold, 1, 1);
    }else if(340<x1 && 350>x1 && 330<y1 && 340>y1){
      dl_rectangle(x1-10, y1, x1+10, y1-10, dl_dpdkred, 1, 1);
      dl_rectangle(342, y1-8, 348, y1-10, dl_gold, 1, 1);
      dl_rectangle(342, y1, 348, y1-2, dl_gold, 1, 1);
    }else if(340<x1 && 350>x1 && 300<y1 && 310>y1){
      dl_rectangle(340, 307, 350, 310, dl_red, 1, 1);
      dl_rectangle(342, 310, 348, 309, dl_gold, 1, 1);
     }
  } 
}

