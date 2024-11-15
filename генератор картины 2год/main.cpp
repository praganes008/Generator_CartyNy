#include "TXLib.h"
#include <fstream>
#include <windows.h>
#include <string.h>


using namespace std;                                                                                            //cемейство меток работающих с fstream

 struct Button
  {
    int x;
    int y;
    int width;
    int height;
    const char* text;
    COLORREF color;
    string category;

  void draw()
  {
        txSetColor (TX_WHITE, 2);
        txSetFillColor (color);
        if(click())
        {
            txSetFillColor(TX_GREY);
        }

        txRectangle (x, y, x+width, y+height);
        txSetColor (TX_WHITE, 2);
        txSelectFont("Times New Roman", 30);
        txDrawText(x, y, x+width, y+height, text);
  }

    bool click()
    {
        return( txMouseButtons() == 1 &
        txMouseX()>x & txMouseX() < x+width &
        txMouseY()>y & txMouseY() < y+height );
    }

 };

 struct Picture
{
    int x;
    int y;
    string adress;
    HDC image;
    int w_scr;
    int h_scr;
    int w;
    int h;
    string category;
    bool visible;

    void draw()
    {
        if(visible)
        {
        Win32::TransparentBlt (txDC(), x, y, w_scr, h_scr, image, 0, 0, w, h, TX_WHITE);
        }
    }

    bool click()
    {
                return( txMouseButtons() == 1 &
                txMouseX()>x & txMouseX() < x+w_scr &
                txMouseY()>y & txMouseY() < y+h_scr );

    }

};

void drawworkspase(int x, int y, int width, int height)
{

    txSetColor (TX_BLUE, 7);
    txSetFillColor (TX_WHITE);
    txRectangle (x, y, x+width, y+height);

}

string DialogFile(bool isSave)
{
  string filename = "";


OPENFILENAME ofn = {0};
TCHAR szFile[260]={0};
// Initialize remaining fields of OPENFILENAME structure
ZeroMemory(&ofn, sizeof(ofn));
ofn.lStructSize = sizeof(ofn);
ofn.hwndOwner = txWindow();
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = ("Text\0*.TXT\0");
ofn.nFilterIndex = 1;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if(isSave)
    {
        if(GetSaveFileName(&ofn) == TRUE)
        {
                filename = ofn.lpstrFile;
                filename = filename + ".txt";

        }
    }

    else
    {
        if(GetOpenFileName(&ofn) == TRUE)
        {
                filename = ofn.lpstrFile;

        }
    }

 return filename;
}

int main()
        {
    txCreateWindow (1500, 800);
    txTextCursor(false);
    //кол-во кнопок
    int count_btn = 11;
    //кнопка сохранения
    int btn_save = count_btn-4;
    //кнопка загрузки
    int btn_load = count_btn-3;
    //кнопка выхода
    int btn_exit = count_btn-1;
    //кнопка помощи
    int btn_help = count_btn-2;
    //кол-во картинок
    int count_pic = 19;
    //кол-во центральных картинок в рабочей области
    int nCentralpic = 0;
    //переменная что бы двигать картинки
    int vybor = -1;
    //переменная нажатия на картинку на рабочей области
    bool mouse_down = false;

    string PAGE = "work";

    //кнопки
    Button btn[count_btn];
    btn[0] = {10, 10, 170, 35, "еда", TX_BLUE, "еда"};
    btn[1] = {200, 10, 170, 35, "предметы", TX_BLUE, "предметы"};
    btn[2] = {390, 10, 170, 35, "персонажи", TX_BLUE, "персонажи"};
    btn[3] = {580, 10, 170, 35, "мебель", TX_BLUE, "мебель"};
    btn[4] = {770, 10, 170, 35, "растения", TX_BLUE, "растения"};
    btn[5] = {960, 10, 170, 35, "техника", TX_BLUE, "техника"};
    btn[6] = {1150, 10, 170, 35, "животные", TX_BLUE, "животные"};
    btn[7] = {250, 55, 170, 35, "сохранить", TX_LIGHTBLUE, ""};
    btn[8] = {440, 55, 170, 35, "загрузить", TX_LIGHTBLUE, ""};
    btn[9] = {630, 55, 170, 35, "помощ", TX_LIGHTBLUE, ""};
    btn[10] = {820, 55, 170, 35, "выход", TX_LIGHTBLUE, ""};


    //картинки в меню
    Picture menu_pic[count_pic];
    menu_pic[0] = {10, 100, "pictures/еда/Яблоки.bmp", txLoadImage("pictures/еда/Яблоки.bmp"), 50, 50, 100, 100, "еда", false};
    menu_pic[1] = {10, 200, "pictures/еда/авокадо.bmp", txLoadImage("pictures/еда/авокадо.bmp"), 50, 50, 100, 100, "еда", false};
    menu_pic[2] = {10, 300, "pictures/еда/груша.bmp", txLoadImage("pictures/еда/груша.bmp"), 50, 50, 100, 100, "еда", false};

    menu_pic[3] = {10, 100, "pictures/персонажи/стив.bmp", txLoadImage("pictures/персонажи/стив.bmp"), 80, 80, 400, 400, "персонажи", false};
    menu_pic[4] = {10, 200, "pictures/персонажи/джерри.bmp", txLoadImage("pictures/персонажи/джерри.bmp"), 80, 80, 400, 400, "персонажи", false};
    menu_pic[5] = {10, 300, "pictures/персонажи/том.bmp", txLoadImage("pictures/персонажи/том.bmp"), 80, 80, 400, 400, "персонажи", false};

    menu_pic[6] = {10, 100, "pictures/предметы/ваза1.bmp", txLoadImage("pictures/предметы/ваза1.bmp"), 80, 80, 400, 400, "предметы", false};
    menu_pic[7] = {10, 200, "pictures/предметы/ноутбук1.bmp", txLoadImage("pictures/предметы/ноутбук1.bmp"), 80, 80, 400, 400, "предметы", false};
    menu_pic[8] = {10, 300, "pictures/предметы/диван.bmp", txLoadImage("pictures/предметы/диван.bmp"), 80, 80, 400, 400, "предметы", false};

    menu_pic[9] = {10, 100, "pictures/мебель/стол1.bmp", txLoadImage("pictures/мебель/стол1.bmp"), 80, 80, 400, 400,"мебель", false};
    menu_pic[10] = {10, 200, "pictures/мебель/стол2.bmp", txLoadImage("pictures/мебель/стол2.bmp"), 80, 80, 400, 400 ,"мебель", false};
    menu_pic[11] = {10, 300, "pictures/мебель/стол3.bmp", txLoadImage("pictures/мебель/стол3.bmp"), 80, 80, 400, 400, "мебель", false};

    menu_pic[12] = {10, 100, "pictures/растения/фикус1.bmp", txLoadImage("pictures/растения/фикус1.bmp"), 80, 80, 400, 400, "растения", false};
    menu_pic[13] = {10, 200, "pictures/растения/фикус2.bmp", txLoadImage("pictures/растения/фикус2.bmp"), 80, 80, 400, 400, "растения", false};

    menu_pic[14] = {10, 100, "pictures/техника/танк1.bmp", txLoadImage("pictures/техника/танк1.bmp"), 80, 80, 400, 400, "техника" , false};

    menu_pic[15] = {10, 100, "pictures/животные/собака.bmp", txLoadImage("pictures/животные/собака.bmp"), 80, 80, 400, 400, "животные", false};
    menu_pic[16] = {10, 200, "pictures/животные/жираф.bmp", txLoadImage("pictures/животные/жираф.bmp"), 80, 80, 400, 400, "животные" , false};
    menu_pic[17] = {10, 300, "pictures/животные/нюхач.bmp", txLoadImage("pictures/животные/нюхач.bmp"), 80, 80, 400, 400, "животные" , false};
    menu_pic[18] = {10, 400, "pictures/животные/кот.bmp", txLoadImage("pictures/животные/кот.bmp"), 80, 80, 400, 400, "животные" , false};

   for(int i=0; i<count_btn; i++)
   {

    menu_pic[i].visible = false;

   }





    //coздание массива картинок на рабочей области, БЕЗ замены картинок
    Picture centr_pic[100];


    while(!btn[btn_exit].click())//!GetAsyncKeyState (VK_ESCAPE)
    {

        txSetFillColor(TX_LIGHTGREEN);
        txClear();
        txBegin();

        // рабочая область
        drawworkspase(250, 100, 1240, 670);

        if(PAGE == "work")
        {

        //рисование кнопок
        for(int i=0; i<count_btn; i++)
        {
            btn[i].draw();
        }

        //рисование картинок в меню
        for(int i=0; i<count_pic; i++)
        {
            menu_pic[i].draw();
        }

        //рисование картинок на воркспейс
        for(int i=0; i<nCentralpic; i++)
        {
            centr_pic[i].draw();
        }

        //условие видимоти картинок меню в зависимости от нажатой кнопки
        for(int nbutton=0; nbutton<count_btn; nbutton++)
        {
            if(btn[nbutton].click())
            {
                 for(int npic=0; npic<count_pic; npic++)
                 {
                      menu_pic[npic].visible = false;
                      if(menu_pic[npic].category == btn[nbutton].category)
                      {
                        menu_pic[npic].visible = true;
                      }
                 }
            }

        }


        //без замены центральных картинок на рабочей области
        for(int npic=0; npic<count_pic; npic++)
        {
            if(menu_pic[npic].click() && menu_pic[npic].visible)
            {
                 while(txMouseButtons() == 1)
                 {
                 txSleep(10);
                 }

                 centr_pic[nCentralpic] =   { 350,
                                              150,
                                              menu_pic[npic].adress,
                                              menu_pic[npic].image,
                                              menu_pic[npic].w,
                                              menu_pic[npic].h,
                                              menu_pic[npic].w,
                                              menu_pic[npic].h,
                                              menu_pic[npic].visible,
                                              menu_pic[npic].category,


                                            };
                        nCentralpic++;
            }

        }

        for(int npic=0; npic<nCentralpic; npic++)                                                                           //то есть на какую кликнул, меняется переменная выбор(1,2,3...)
        {
          if(centr_pic[npic].click() && centr_pic[npic].visible)
          {
           vybor = npic;
           mouse_down = false;
          }
        }



    //Передвижение объекта мышкой
    if(vybor>=0)
    {
        if(txMouseButtons() == 1 && !mouse_down)
        {
            centr_pic[vybor].x = txMouseX() - centr_pic[vybor].w_scr/2;
            centr_pic[vybor].y = txMouseY() - centr_pic[vybor].h_scr/2;
        }
            else
            {
                if(txMouseButtons() != 1)
                {
                mouse_down = true;
                }
            }
    }

    //перемещение объекта клавиатурой
    if(vybor>=0)
    {
     //
    if(GetAsyncKeyState (VK_UP))
        {
        centr_pic[vybor].y -= 5;
        }

    if(GetAsyncKeyState (VK_DOWN))
        {
        centr_pic[vybor].y += 5;
        }

    if(GetAsyncKeyState (VK_LEFT))
        {
        centr_pic[vybor].x -= 5;
        }

    if(GetAsyncKeyState (VK_RIGHT))
        {
        centr_pic[vybor].x += 5;
        }
     //
    if(GetAsyncKeyState (VK_OEM_PLUS))                                                                                          //если нажат плюс, то умножить на 1.05 ширину и высоту
        {
        centr_pic[vybor].w_scr = centr_pic[vybor].w_scr*1.05;
        centr_pic[vybor].h_scr = centr_pic[vybor].h_scr*1.05;
        if(centr_pic[vybor].w_scr>700)
        {
        centr_pic[vybor].w_scr=700;
        centr_pic[vybor].h_scr=700;
        }
        }

    if(GetAsyncKeyState (VK_OEM_MINUS))                                                                                          //если нажат плюс, то умножить на 1.05 ширину и высоту
        {
        centr_pic[vybor].w_scr = centr_pic[vybor].w_scr*0.95;
        centr_pic[vybor].h_scr = centr_pic[vybor].h_scr*0.95;
        if(centr_pic[vybor].w_scr<50)
        {
        centr_pic[vybor].w_scr=50;
        centr_pic[vybor].h_scr=50;
        }
        }
    }

    //удаление объекта
    if(vybor>=0 && GetAsyncKeyState (VK_DELETE))                                                                                            // элемент выбранный мышкой, сдвигаем в лево на 1 и выбор = -1(тоесть мы типа сбрасываем нажатие клавиши), делаем mouse_down снова тру(тоесть типа мы его отжали) и картинка убирается
    {
        centr_pic[vybor] = centr_pic[nCentralpic - 1];
        nCentralpic--;
        vybor = -1;
        mouse_down = true;
    }

    //сохранение файла в файл, по нажатию на клавишу
    if(btn[btn_save].click())
    {
            string filename = DialogFile(true);
            ofstream fileout;               // поток для записи
            fileout.open(filename);      // открываем файл для записи(текстовый)
            if (fileout.is_open())
            {
                for(int i=0; i<nCentralpic; i++)
                {
                fileout << centr_pic[i].x << endl;                                                                                          //это сохранение сначала икса картинки, потом у, потом его адрес, и потом его высоту и ширину
                fileout << centr_pic[i].y << endl;
                fileout << centr_pic[i].adress << endl;
                fileout << centr_pic[i].h_scr << endl;
                fileout << centr_pic[i].w_scr << endl;
                }
            }
            fileout.close();                    //закрываем файл

    }

    //загрузка композиции из файла
    if(btn[btn_load].click())
    {

          string filename = DialogFile(false);

          while(txMouseButtons() == 1)
         {
         txSleep(10);
         }

          for(int i=0; i>0; i--)
          {
            centr_pic[nCentralpic] = centr_pic[nCentralpic - 1];
            nCentralpic--;
            vybor = -1;
            mouse_down = true;
          }

        char buff[50];
        ifstream filein("hello.txt");      // открываем файл для записи(текстовый)
        while(filein.good())
        {
            filein.getline(buff, 50);
            int x = atoi(buff);
            filein.getline(buff, 50);
            int y = atoi(buff);
            filein.getline(buff, 50);
            string adress = buff;
            filein.getline(buff, 50);
            int h_scr = atoi(buff);
            filein.getline(buff, 50);
            int w_scr = atoi(buff);

         for(int i=0; i<count_pic; i++)
         {

         if(menu_pic[i].adress == adress)
         {
         centr_pic[nCentralpic] =   { x,
                                      y,
                                      adress,
                                      menu_pic[i].image,
                                      w_scr,
                                      h_scr,
                                      menu_pic[i].w,
                                      menu_pic[i].h,
                                      menu_pic[i].category,
                                      true


                                    };
        nCentralpic ++;
         }
         }
                                                                                                                        //atoi - перевод из букв, в число проще говоря
        }
        filein.close();
    }

    }

        if(btn[btn_help].click())
        {

         PAGE = "help";

        }

        if(PAGE == "help")
        {
        txClear();
        txSetColor (TX_RED, 7);
        txSetFillColor (TX_BLUE);
        txRectangle(0, 0, 1500, 800);
        drawworkspase(100, 50, 1300, 700);
        txSelectFont("Comic Sans MS", 50);
        //верхня строчка
        txSetColor (TX_RED, 7);
        txDrawText(200, 20, 1250, 200, "Помощ по приложению");
        //средняя строчка
        txSelectFont("Comic Sans MS", 32);
        txSetColor (TX_BLACK, 7);
        txDrawText(165, 100, 1250, 215, "возможности генератора картины");
        //сама помощ
        txSelectFont("Comic Sans MS", 30);
        txSetColor (TX_BLACK, 7);
        txDrawText(165, 160, 1250, 215, "В приложении присутствуют 8 категорий картинок,\n
                                         ");

        if(GetAsyncKeyState (VK_ESCAPE))
        {
         PAGE = "work";
        }


        }

    txEnd();
    txSleep(10);
    }


    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC(menu_pic[i].image);
    }

    for(int i=0; i<nCentralpic; i++)
    {
        txDeleteDC(centr_pic[i].image);
    }

        txDisableAutoPause();
        txTextCursor (false);
        return 0;
        }


