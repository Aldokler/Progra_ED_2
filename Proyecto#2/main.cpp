#include <iostream>
#include <winbgim.h>
#include <conio.h>
#include <stdexcept>
#include <ctime>
#include <math.h>
#include "ListaAdyacente.h"


using namespace std;

int game(int num){
    ListaAdyacente<int> L (5);
    int timer = 15;
    for(int i=5;(i=i);i++){
        int stime=time(0);
        L.setSize(i*i);

        if(num==0){
          L.vecinosss();
          L.deepSearch();
          L.addExtra(i);
        }
        if(num==1){
          L.kruskal();
          L.convert();
        }
        if(num==2){
          L.prim();
          L.convert();
        }


        L.initialize();
        L.labDisplay();
        L.setPlayerPos();
        timer+=(timer/3);


        while(!L.atEnd()){
            string tiempo= "";
            tiempo=to_string(timer-int(time(0)-stime));
            char * timeString = new char [tiempo.length()+1];
            strcpy(timeString, tiempo.c_str());
            setcolor(15);
            outtextxy(0, 0, "Tiempo restante: ");
            outtextxy(230, 0, "       ");// usamos espacios para limpiar el string del tiempo
            outtextxy(230, 0,timeString);/*
            outtextxy(i*30, 0, "Tiempo restante: ");
            outtextxy(i*30+230, 0, "                                               ");// usamos espacios para limpiar el string del tiempo
            outtextxy(i*30+230, 0,timeString);
            //outtextxy(i*30+230, 0,tiempo.c_str());*/
            int pos = getch();
            if(time(0)-stime>=timer){
                cleardevice();
                cout<<"Perdiste por tiempo!"<<endl;
                return 0;
            }


            if(pos==27){// esc para salir
                cleardevice();
                cout<<endl<<"Has salido del programa."<<endl;
                return 0;
            }

            else if(pos==72){//flechas para moverse (arriba)
                L.labDisplay();
                L.setPlayerPos(1);
            }

            else if(pos==75){//flechas para moverse (izquierda)
                L.labDisplay();
                L.setPlayerPos(2);
            }

            else if(pos==77){//flechas para moverse (derecha)
                L.labDisplay();
                L.setPlayerPos(3);
            }
            else if(pos==80){//flechas para moverse (abajo)
                L.labDisplay();
                L.setPlayerPos(4);
            }
                else if(pos==104){// "h" para ver como llegar al final del laberinto
                L.hint();
            }
            else{
                L.labDisplay();
                L.setPlayerPos(pos);
                if(time(0)-stime>=timer){
                cleardevice();
                cout<<"Perdiste por tiempo!"<<endl;
                return 0;
                }
            }
        }
        cleardevice();
    }
    return 0;
}

void subMenu(){
    unsigned int choice = 0;
    while (true){
        setcolor(15);
        setfillstyle(1,15);
        outtextxy(600, 10, "A MAZE.ing");
        bar(480, 100, 880, 150);
        bar(480, 200, 880, 250);
        bar(480, 300, 880, 350);
        bar(480, 400, 880, 450);
        setbkcolor(15);
        setcolor(1);
        outtextxy(555, 110, "Laberinto profundo");
        outtextxy(555, 210, "Laberinto de Kruskal");
        outtextxy(555, 310, "Laberinto de Prim");
        outtextxy(555, 410, "Cancelar");
        setbkcolor(0);
        setfillstyle(1,4);
        if (choice%4 == 0)
            bar(500, 117, 515, 132);
        else if (choice%4 == 1)
            bar(500, 217, 515, 232);
        else if (choice%4 == 2)
            bar(500, 317, 515, 332);
        else
            bar(500, 417, 515, 432);
        int tecla = getch();
        if (tecla == 72)
            choice--;
        if (tecla == 80)
            choice++;
        else if (tecla == 13){
            if (choice%4 == 0){
                cleardevice();
                game(0);
                return;
            }
            else if (choice%4 == 1){
                cleardevice();
                game(1);
                return;
            }
            else if (choice%4 == 2){
                cleardevice();
                game(2);
                return;
            }
            else{
                cleardevice();
                return;
            }
        }
    }
}

//a�adir un men� inicial
void menu(){
    int choice = 0;
    while (true){
        setcolor(15);
        setfillstyle(1,15);
        outtextxy(600, 10, "A MAZE.ing");
        bar(480, 100, 880, 150);
        bar(480, 200, 880, 250);
        setbkcolor(15);
        setcolor(1);
        outtextxy(555, 110, "Jugar");
        outtextxy(555, 210, "Salir");
        setbkcolor(0);
        setfillstyle(1,4);
        if (choice%2 == 0)
            bar(500, 117, 515, 132);
        else
            bar(500, 217, 515, 232);
        int tecla = getch();
        if (tecla == 72 || tecla == 80){
            choice++;
        }
        else if (tecla == 13){
            if (choice%2 == 0){
                cleardevice();
                subMenu();
            }
            else
                return;
        }
    }
}
  //deber�a recibir el main
  //int maze size, tiempo on/off
int main(){
    initwindow (1920,1080);
    settextstyle(8, 0, 3);
    setcolor(15);
    setlinestyle(0, 0, 10);

    menu();

    closegraph();

    return 0;
}
