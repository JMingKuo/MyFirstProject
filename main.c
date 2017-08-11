#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"
#include <time.h>

#include <unistd.h>
#include <sys/types.h>

/*
putASCII2()  最後兩個參數分別是字元前景和背景的顏色
可以參考下面的顏色值對照表來設定你想要的顏色
   0: 黑     1: 暗藍   2: 暗綠   3: 暗青
   4: 暗紅   5: 暗紫   6: 暗黃   7: 淺灰
   8: 暗灰   9: 亮藍  10: 亮綠  11: 亮青
  12: 亮紅  13: 亮紫  14: 亮黃  15: 白
*/


void swing(int player_position,int weapon_No);

    Image *monster_box[6];
    int monster_hei[6]={42,42,42,42,0,42};
    int monster_speed[6]={1,1,1,1,1,3};
    int monster_def[6]={1,1,1,1,1,1};
    int monster_No = 0;

    Image *weapon[3];
    int weapon_No=0;


// window:300x100,8x16
int main()
{
    system("mode 300,100");
    //SMALL_RECT WinRect = {0, 0, 500, 200};   //New dimensions for window in 8x12 pixel chars
    //SMALL_RECT* WinSize = &WinRect;
    //SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, WinSize);   //Set new size for window


    int i,j,k,cat=0;

    int open_position=0;
    int cat_position=250;
    int cat_speed = 5;
    int lose_position = 110;
    int lose_shift = 1;

    int player_HP=16;
    int monster_HP=16;

    clock_t t;
    t = clock();

    initializeKeyInput();

    int player_position = 100;
    int monster_position = 250;
    char ch;

    Font *large_font = read_font("font.txt");
    int scene_Opening = 1;
    int scene_Playing = 0;
    int scene_Relax = 0;

    int OpenBreath = 0;
    int OpenBreath_cnt = 0;
    int OpenBreath_rate = 4;

    Audio hit1;
    openAudioFile("hit1.wav", &hit1);
    Audio mon2;
    openAudioFile("mon2.wav", &mon2);

    Image *monster1 = read_image("images/ascii/monster1.pixel", "images/ascii/monster1.color");
    Image *monster2 = read_image("images/ascii/monster2.pixel", "images/ascii/monster2.color");
    Image *monster3 = read_image("images/ascii/monster3.pixel", "images/ascii/monster3.color");
    Image *monster4 = read_image("images/ascii/monster4.pixel", "images/ascii/monster4.color");
    Image *monster5 = read_image("images/ascii/monster5.pixel", "images/ascii/monster5.color");
    Image *monster6 = read_image("images/ascii/monster6.pixel", "images/ascii/monster6.color");
    monster_box[0]=monster1;
    monster_box[1]=monster2;
    monster_box[2]=monster3;
    monster_box[3]=monster4;
    monster_box[4]=monster5;
    monster_box[5]=monster6;

    Image *player = read_image("images/ascii/player.pixel", "images/ascii/player.color");

    PlaySound(TEXT("wingoffreedom.wav"), NULL, SND_ASYNC|SND_FILENAME);

    while(scene_Opening){
    Image *open_background = read_image("images/ascii/open_background.pixel", "images/ascii/open_background.color");
    show_image(open_background, 0, 0);
    destroy_image(open_background);

    Image *open_title = read_image("images/ascii/open_title.pixel", "images/ascii/open_title.color");
    show_image(open_title, 90, 25);
    destroy_image(open_title);

    switch(OpenBreath){
        case 0:
        putStringLarge(large_font,85,50,"Press E to START",1);
        OpenBreath_cnt++;
        if(OpenBreath_cnt==OpenBreath_rate){OpenBreath++;OpenBreath_cnt=0;}
        break;
        case 1:
        putStringLarge(large_font,85,50,"Press E to START",3);
        OpenBreath_cnt++;
        if(OpenBreath_cnt==OpenBreath_rate){OpenBreath++;OpenBreath_cnt=0;}
        break;
        case 2:
        putStringLarge(large_font,85,50,"Press E to START",9);
        OpenBreath_cnt++;
        if(OpenBreath_cnt==OpenBreath_rate){OpenBreath=0;OpenBreath_cnt=0;}
        break;
    }

    drawCmdWindow();
    clearScreen();
    if(cat<80){show_image(player, open_position+=5, 75);cat++;}
    else{show_image(monster2, cat_position-=cat_speed, 75);cat_position++;cat++;if(cat%10==0)cat_speed+=3;if(cat_position<=0)cat_position=300;}


    if(waitForKeyDown(0.1)){
        ch=getKeyEventASCII();
    if(ch=='e'){
        clearScreen();
        scene_Opening=0;
        scene_Playing=1;
    }
    }
}

    PlaySound(TEXT("Legend-Of-Zelda-Them.wav"), NULL, SND_ASYNC|SND_FILENAME);

    while(scene_Playing){
        Image *background = read_image("images/ascii/background.pixel", "images/ascii/background.color");
        Image *monster1 = read_image("images/ascii/monster1.pixel", "images/ascii/monster1.color");
        Image *monster2 = read_image("images/ascii/monster2.pixel", "images/ascii/monster2.color");
        Image *monster3 = read_image("images/ascii/monster3.pixel", "images/ascii/monster3.color");
        Image *monster4 = read_image("images/ascii/monster4.pixel", "images/ascii/monster4.color");
        Image *monster5 = read_image("images/ascii/monster5.pixel", "images/ascii/monster5.color");
        Image *monster6 = read_image("images/ascii/monster6.pixel", "images/ascii/monster6.color");
        Image *player = read_image("images/ascii/player.pixel", "images/ascii/player.color");

    clearScreen();

        show_image(background,0,0);
        destroy_image(background);

    if(monster_HP>0){
        for(i=0;i<=monster_HP;i++)putStringLarge(large_font,140+8*i,12,":",12);
        show_image(monster_box[monster_No],monster_position , monster_hei[monster_No]);
        destroy_image(monster1);
        monster_position=monster_position-monster_speed[monster_No];
    if(monster_position<=player_position+10){
        player_position-=5;
        player_HP--;
        }
    }



    show_image(player, player_position, 40);
    destroy_image(player);

    putStringLarge(large_font,80,2," PLAYER",15);
    for(i=0;i<=player_HP;i++)putStringLarge(large_font,140+8*i,2,":",12);
    putStringLarge(large_font,80,12,"MONSTER",15);

            if(monster_position<=30||player_HP<0){
                for(i=0;i<=300;i+=70){
                for(j=20;j<=100;j+=8){
                putStringLarge(large_font,i,j,"YOU LOSE",13);
                drawCmdWindow();
                    }
                }
                PlaySound(TEXT("hahaha.wav"), NULL, SND_ASYNC|SND_FILENAME);
                Sleep(5000);
                while(1){
                clearScreen();
                putStringLarge(large_font,lose_position,30,"You Lose",13);
                putStringLarge(large_font,100,45,"Pree Q to quit",7);
                lose_position+=lose_shift;
                if(lose_position>=150||lose_position<=100)lose_shift = -lose_shift;
                drawCmdWindow();
                    if(waitForKeyDown(0.01)){
                        ch=getKeyEventASCII();
                        if(ch== 'q')
                        return 0;
                    }
                }
        }

    drawCmdWindow();


    if(waitForKeyDown(0.01)){
          //  clearScreen();
        ch=getKeyEventASCII();
            switch(ch){
            case 'e':
                weapon_No++;
                break;
            case 'q':
                return 0;
            case 'd':
                player_position+=5;
                break;
            case 'a':
                if(player_position>=50)player_position-=3;
                break;
            case 'k':
                if(clock()-t>100){
                    swing(player_position,weapon_No);
                    playAudio(&hit1);
                    if((player_position+35)>=monster_position){
                        monster_HP--;
                        if(monster_HP%4==0)monster_position+=5;
                    }
                    t = clock();
                }
                break;
            }
        }
    if(monster_HP<=0&&monster_No<5){
        monster_No++;
        monster_HP=16;
        player_HP=16;
        monster_position = 250;
            while(scene_Relax){

            }
    }
}
    return 0;
}

void swing(int player_position,int weapon_No){
    Image *sword1 = read_image("images/ascii/sword1.pixel", "images/ascii/sword1.color");
    Image *sword2 = read_image("images/ascii/sword2.pixel", "images/ascii/sword2.color");
    weapon[0] = sword1;
    weapon[1] = sword2;
    show_image(weapon[weapon_No%2], player_position+16, 42);
    drawCmdWindow();
}

