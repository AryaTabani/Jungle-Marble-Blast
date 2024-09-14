#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>
#include<cstdlib>
#include<time.h>
#include<math.h>
#include<fstream>


#define pi 3.141592653589
#define radius 30

using namespace std;

int l=1280, h=800;

SDL_Renderer * m_renderer;
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height)
{
        int n = addressOfImage.length();
        char char_array[n+1];
        strcpy(char_array, addressOfImage.c_str());
        SDL_Texture *myTexture;
        myTexture = IMG_LoadTexture( m_renderer, char_array);
        int w1, h1;
        SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
        SDL_Rect texr1;
        texr1.x = xp;
        texr1.y = yp;
        texr1.w = width;
        texr1.h = height;
        SDL_RenderCopy( m_renderer, myTexture, NULL, &texr1);
            SDL_DestroyTexture(myTexture);
}
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{
    SDL_Rect rectangle ;

    rectangle.x = x;

    rectangle.y = y;

    rectangle.w = w;

    rectangle.h = h;

    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);

    if (fill_boolian==1)

        SDL_RenderFillRect(Renderer, &rectangle);

    SDL_RenderDrawRect(Renderer, &rectangle);
}


void my_line(SDL_Renderer *Renderer, int x_1, int y_1, int L, double theta,int widht, int R, int G, int B )

{
    int x_2 = x_1 + L*cos(theta);
    int y_2 = y_1 - L*sin(theta);
    thickLineRGBA(Renderer,x_1,y_1,x_2,y_2,widht,R,G,B,255);
}
void settingmenu(SDL_Renderer*m_renderer,int T,int &M1,int &M2);
void helpbuttonclick(SDL_Renderer*m_renderer,int T,int &M1,int &M2);





struct point
{
double x, y;
};

point P[4], Middle_Points[3], Middle_Points2[2], Main_Point[1000], save_FP, save_LP;
struct ball
{
    double x[1000], y[1000];
    int index=0;
    int R, G, B;
};

ball balls[80];

void monh (SDL_Renderer* m_renderer, point P1, point P2, point &P, double t)
{
    P.x=P1.x+(P2.x-P1.x)*t;
    P.y=P1.y+(P2.y-P1.y)*t;
}

double x_line=640, y_line=700, width_line=25, L_line=100, x_circle=x_line, radius_circle=40, y_circle=y_line;
double x_ball=x_line, y_ball=y_line, radius_ball=width_line/2-1;
int random_color, ball_colors_R[4]={251, 8, 255, 45}, ball_colors_G[4]={130, 130, 48, 253}, ball_colors_B[4]={25, 234, 111, 84};
////int random_color, ball_colors_R[4]={253, 70, 250, 253}, ball_colors_G[4]={119, 1, 0, 254}, ball_colors_B[4]={0, 28, 0, 1};
////int random_color, ball_colors_R[4]={0, 86, 255, 47}, ball_colors_G[4]={88, 85, 255, 30}, ball_colors_B[4]={1, 93, 255, 0};
double t=0, dt=0.001;
int indexOfPoints=0, indexOfMoves=-1, indexOfReapeat=0;
int R, G, B;
bool shot=true;
double theta_line=pi/2, filled_theta=0, filled_theta_first, filled_theta_last, deltaX, deltaY, deltaXFirst, deltaYFirst, deltaXLast, deltaYLast;
SDL_Event *e=new  SDL_Event();
int lol=0;


void Move ()
{
    if(indexOfReapeat%29==0)
    {
        ++indexOfMoves;
        random_color=rand()%4;
        switch(random_color){
        case 0:{
    balls[indexOfMoves].R=ball_colors_R[0];
    balls[indexOfMoves].G=ball_colors_G[0];
    balls[indexOfMoves].B=ball_colors_B[0];
    break;
    }
    case 1:{
    balls[indexOfMoves].R=ball_colors_R[1];
    balls[indexOfMoves].G=ball_colors_G[1];
    balls[indexOfMoves].B=ball_colors_B[1];
    break;
    }
    case 2:{
balls[indexOfMoves].R=ball_colors_R[2];
 balls[indexOfMoves].G=ball_colors_G[2];
 balls[indexOfMoves].B=ball_colors_B[2];
    break;
    }
    case 3:{
    balls[indexOfMoves].R=ball_colors_R[3];
    balls[indexOfMoves].G=ball_colors_G[3];
    balls[indexOfMoves].B=ball_colors_B[3];
    break;
    }
}
}

for(int s=0; s<=indexOfMoves; ++s)
{
    filledCircleRGBA(m_renderer, balls[s].x[balls[s].index], balls[s].y[balls[s].index], radius, balls[s].R, balls[s].G, balls[s].B, 255);
    circleRGBA(m_renderer, balls[s].x[balls[s].index], balls[s].y[balls[s].index], radius-10, 255, 255, 255, 255);
    circleRGBA(m_renderer, balls[s].x[balls[s].index], balls[s].y[balls[s].index], radius-20, 255, 255, 255, 255);
    circleRGBA(m_renderer, balls[s].x[balls[s].index], balls[s].y[balls[s].index], radius, 255, 255, 255, 255);
    ++balls[s].index;
}
SDL_Delay(30);
filledCircleRGBA(m_renderer, save_FP.x, save_FP.y, radius, 0, 0, 0, 255);
filledCircleRGBA(m_renderer, save_FP.x, save_FP.y+10, radius, 0, 0, 0, 255);
filledCircleRGBA(m_renderer, save_LP.x, save_LP.y, radius, 0, 0, 0, 255);
filledCircleRGBA(m_renderer, save_LP.x, save_LP.y+10, radius, 0, 0, 0, 255);
indexOfReapeat++;
deltaY=-balls[0].y[balls[0].index]+y_circle;
deltaX=balls[0].x[balls[0].index]-x_circle;
if(deltaX<0 && deltaY>0)
filled_theta=atan(deltaY/deltaX)+pi;
else if(deltaX<0 && deltaY<0)
filled_theta=atan(deltaY/deltaX)-pi;
else if(deltaX>0)
filled_theta=atan(deltaY/deltaX);
    else if(deltaX==0 && deltaY>0)
        filled_theta=(pi/2);

else if(deltaX==0 && deltaY<0)
    filled_theta=-(pi/2);
if(balls[0].index>=indexOfPoints)
{
    while(balls[indexOfMoves].index<indexOfPoints)
    {
    for(int s=0; s<=indexOfMoves; ++s)
    {
    if(balls[s].index<indexOfPoints)
    {
            filledCircleRGBA(m_renderer, balls[s].x[balls[s].index], balls[s].y[balls[s].index], radius, balls[s].R, balls[s].G, balls[s].B, 255);
            circleRGBA(m_renderer, balls[s].x[balls[s].index], balls[s].y[balls[s].index], radius, 255, 255, 255, 255);
            circleRGBA(m_renderer, balls[s].x[balls[s].index], balls[s].y[balls[s].index], radius-10, 255, 255, 255, 255);
            circleRGBA(m_renderer, balls[s].x[balls[s].index], balls[s].y[balls[s].index], radius-20, 255, 255, 255, 255);
            filledEllipseRGBA(m_renderer, x_ball, y_ball, radius_ball, radius_ball, R, G, B, 255);
            my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, 109, 109, 109);
            filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
            balls[s].index+=50;
    }
}

filledEllipseRGBA(m_renderer, x_ball, y_ball, radius_ball, radius_ball, R, G, B, 255);
my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, 109, 109, 109);
filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
filledCircleRGBA(m_renderer, save_FP.x, save_FP.y, radius, 0, 0, 0, 255);
filledCircleRGBA(m_renderer, save_FP.x, save_FP.y+10, radius, 0, 0, 0, 255);
filledCircleRGBA(m_renderer, save_LP.x, save_LP.y, radius, 0, 0, 0, 255);
filledCircleRGBA(m_renderer, save_LP.x, save_LP.y+10, radius, 0, 0, 0, 255);
        SDL_RenderPresent(m_renderer);

                SDL_RenderClear(m_renderer);
            }
            exit(1);
        }
}

void game(){


 int T=1,M1 = 1,M2 = 2;
    Mix_Music *background = Mix_LoadMUS("test.mp3");
    Mix_Music *background3 = Mix_LoadMUS("test2.mp3");
    Mix_Music *background4 = Mix_LoadMUS("test3.mp3");
    Mix_Music *background5 = Mix_LoadMUS("test4.mp3");
    Mix_Music *background2 = Mix_LoadMUS("Piano.mp3");
    Mix_Chunk *first = Mix_LoadWAV("shoot.wav");
    Mix_PlayMusic(background,1);
    Mix_Chunk *second = Mix_LoadWAV("Blow.wav");
    Mix_Chunk *third = Mix_LoadWAV("Msound.wav");
    Mix_Chunk *fourth = Mix_LoadWAV("Lsound.wav");
  int Volume = MIX_MAX_VOLUME;
  int next = 0;

  string map0 = "project.jpg";
    string map1 = "map1.jpg";
    string map2 = "map2.jpg";
    string map3 = "map3.jpg";
    int emtiyaz = 0;
    double v = 0;
            srand(time(NULL));

        P[0].x=80;
        P[0].y=750;
        P[1].x=50;
        P[1].y=20;
        P[2].x=1230;
       P[2].y=20;
        P[3].x=1200;
        P[3].y=750;
        Middle_Points[0].x=(P[0].x+P[1].x)/2;
        Middle_Points[0].y=(P[0].y+P[1].y)/2-1000000;
        Middle_Points[1].x=(P[1].x+P[2].x)/2;
        Middle_Points[1].y=(P[1].y+P[2].y)/2-1000000;
        Middle_Points[2].x=(P[2].x+P[3].x)/2;
        Middle_Points[2].y=(P[2].y+P[3].y)/2-1000000;
        Middle_Points2[0].x=(Middle_Points[0].x+Middle_Points[1].x)/2;
        Middle_Points2[0].y=(Middle_Points[0].y+Middle_Points[1].y)/2-2000000;
        Middle_Points2[1].x=(Middle_Points[1].x+Middle_Points[2].x)/2;
        Middle_Points2[1].y=(Middle_Points[1].y+Middle_Points[2].y)/2-2000000;
        Main_Point[0].x=(Middle_Points2[0].x+Middle_Points2[1].x)/2;
        Main_Point[0].y=(Middle_Points2[0].y+Middle_Points2[1].y)/2-2000000;
        save_FP.x=P[0].x;
        save_FP.y=P[0].y;
        save_LP.x=P[3].x;
        save_LP.y=P[3].y;
        deltaYFirst=-save_FP.y+y_circle;
        deltaXFirst=save_FP.x-x_circle;
                            /*while(1){

                            filledCircleRGBA(m_renderer,Main_Point[0].x ,Main_Point[0].y , 30, 85, 85, 85, 255);
                             filledCircleRGBA(m_renderer,Middle_Points[0].x ,Middle_Points[0].y , 30, 0, 85, 85, 255);
                             filledCircleRGBA(m_renderer,Middle_Points[1].x ,Middle_Points[1].y , 30, 0, 85, 85, 255);
                             filledCircleRGBA(m_renderer,Middle_Points[2].x ,Middle_Points[2].y , 30, 0, 85, 85, 255);
                             filledCircleRGBA(m_renderer,Middle_Points2[0].x ,Middle_Points2[0].y , 30, 0, 85, 85, 255);
                             filledCircleRGBA(m_renderer,Middle_Points2[1].x ,Middle_Points2[1].y , 30, 0, 85, 85, 255);

                            SDL_RenderPresent(m_renderer);

                            }*/
            if(deltaXFirst<0)
            filled_theta_first=atan(deltaYFirst/deltaXFirst)+pi;
            else if(deltaXFirst>0)
            filled_theta_first=atan(deltaYFirst/deltaXFirst);
            else if(deltaXFirst==0 && deltaYFirst>0)
            filled_theta_first=(pi/2);
            else if(deltaXFirst==0 && deltaYFirst<0)
                filled_theta_first=-(pi/2);
            deltaYLast=-save_LP.y+y_circle;
            deltaXLast=save_LP.x-x_circle;
            if(deltaXLast<0)
            filled_theta_last=atan(deltaYLast/deltaXLast)+pi;
            else if(deltaXLast>0)
            filled_theta_last=atan(deltaYLast/deltaXLast);
            else if(deltaXLast==0 && deltaYLast>0)
            filled_theta_last=(pi/2);
            else if(deltaXLast==0 && deltaYLast<0)
            filled_theta_last=-(pi/2);
        while(1)
        {
            monh(m_renderer, P[0], P[1], Middle_Points[0], t);
            monh(m_renderer, P[1], P[2], Middle_Points[1], t);
            monh(m_renderer, P[2], P[3], Middle_Points[2], t);
            monh(m_renderer, Middle_Points[0], Middle_Points[1], Middle_Points2[0], t);
            monh(m_renderer, Middle_Points[1], Middle_Points[2], Middle_Points2[1], t);
            monh(m_renderer, Middle_Points2[0], Middle_Points2[1], Main_Point[indexOfPoints], t);
            indexOfPoints++;
            t+=dt;
        if(t<0 || t>1)
        break;
    }
for(int i=0; i<indexOfPoints; ++i)
        {
        for(int s=0; s<80; ++s)
    {
    balls[s].x[i]=Main_Point[i].x;
balls[s].y[i]=Main_Point[i].y;
}
}
bool imanturkast = true;
//SDL_Event event;
//
//    while ( true )
//    {
//        if ( SDL_PollEvent( &event ) )
//        {
//            if ( SDL_QUIT == event.type )
//            { break; }
//            if ( SDL_MOUSEBUTTONDOWN == event.type )
//            {
//                if ( (SDL_BUTTON_LEFT == event.button.button))
//                {
//
//                imanturkast = false;
//                }
//
//                else if ( SDL_BUTTON_RIGHT == event.button.button )
//                {
//                break;
//                }
//                else if ( SDL_BUTTON_MIDDLE == event.button.button )
//                { std::cout << "Middle mouse button is down" << std::endl;
//                 }
//            }
//        }
//    }
    while(imanturkast){

    lol=0;
    bool draw = true;
    while(1){
    if(shot){
    random_color=rand()%4;
    switch(random_color){
    case 0:{
    R=ball_colors_R[0];
    G=ball_colors_G[0];
    B=ball_colors_B[0];
    break;
    }
    case 1:{
    R=ball_colors_R[1];
    G=ball_colors_G[1];
    B=ball_colors_B[1];
    break;
    }
    case 2:{
    R=ball_colors_R[2];
    G=ball_colors_G[2];
    B=ball_colors_B[2];
    break;
        }
case 3:{
    R=ball_colors_R[3];
    G=ball_colors_G[3];
    B=ball_colors_B[3];
    break;
    }
    }
texture(m_renderer, 0, 0, map2, l, h);
   my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, 109, 109, 109);
texture(m_renderer,x_line-39, y_line-40,"tank.png",80, 100);
filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
        Move();

    SDL_RenderPresent(m_renderer);
    SDL_RenderClear(m_renderer);
    shot=false;
}
SDL_PollEvent(e);
    if(e->type==SDL_KEYDOWN){
        switch(e->key.keysym.sym){
        case SDLK_a:{
        theta_line+=0.1;
        texture(m_renderer, 0, 0, map2, l, h);
my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, 109, 109, 109);
texture(m_renderer,x_line-39, y_line-40,"tank.png",80, 100);
filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
        Move();
    SDL_RenderPresent(m_renderer);
    break;
    }
    case SDLK_d:{
    theta_line-=0.1;
    texture(m_renderer, 0, 0, map2, l, h);
    my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, 109, 109, 109);
texture(m_renderer,x_line-39, y_line-40,"tank.png",80, 100);
filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
    Move();
    SDL_RenderPresent(m_renderer);
    break;
}
    case SDLK_w:{
    Mix_PlayChannel(-1,first,0);
    int s=0;
    bool collision=false;
    if(theta_line<=filled_theta_first && theta_line>=filled_theta_last)
    {
    if(deltaX<0)
 {
    if(theta_line>=filled_theta)
    {
    while(atan((-balls[s].y[balls[s].index]+y_circle)/(balls[s].x[balls[s].index]-x_circle))+pi<=theta_line)
    {
    balls[s].index+=29;
    s++;
    }
    balls[s].index+=29;
    collision=true;
}
}
else
{
    if(theta_line>=filled_theta)
    {
    double M=atan((-balls[s].y[balls[s].index]+y_circle)/(balls[s].x[balls[s].index]-x_circle));
    while(M<=theta_line)
    {
    balls[s].index+=29;
    s++;
    if((balls[s].x[balls[s].index]-x_circle)<0)
    M=atan((-balls[s].y[balls[s].index]+y_circle)/(balls[s].x[balls[s].index]-x_circle))+pi;
    else if((balls[s].x[balls[s].index]-x_circle)>0)
    M=atan((-balls[s].y[balls[s].index]+y_circle)/(balls[s].x[balls[s].index]-x_circle));
    else M=pi/2;
    }
    balls[s].index+=29;
    collision=true;
    }
    }
    }
    while(1){
    if(x_ball<-radius_ball-3 || x_ball>l+radius_ball+3)
        break;
    else if(y_ball<-radius_ball-3 || y_ball>h+radius_ball+3)
    break;
    if(collision)
    {
    if(((-balls[s].y[balls[s].index]+y_circle)*(-balls[s].y[balls[s].index]+y_circle))+((balls[s].x[balls[s].index]-x_circle)*(balls[s].x[balls[s].index]-x_circle))<((y_ball-y_circle)*(y_ball-y_circle))+((x_circle-x_ball)*(x_circle-x_ball)))
    {
    for(int i=indexOfMoves; i>s; --i)
    balls[i+1]=balls[i];
    balls[s+1].index=balls[s].index-29;
    balls[s+1].R=R;
    balls[s+1].G=G;
    balls[s+1].B=B;
indexOfMoves++;
int counter=1, first, last;
for(last=s+2; balls[last].R==R && balls[last].G==G && balls[last].B==B; ++last)
counter++;
for(first=s; balls[first].R==R && balls[first].G==G && balls[first].B==B; --first)
counter++;
//cout<<indexOfMoves<<" "<<last<<"  ";
          //cout<<balls[first].index<<" "<<balls[last-1].index;
////enfejar
if(R == 0 && G==0&&B==0){

   int arriving_place=balls[last-1].index;
    for(int i=last; i<=indexOfMoves; ++i)
balls[i-last]=balls[i];
for(int i=0; i<counter; ++i)
    balls[indexOfMoves-i].index=0;
        //indexOfMoves-=counter;
        indexOfMoves-=last;
        while(balls[first].index>last)
   // while(balls[first].index>arriving_place)
    {
    for(int j=indexOfMoves; j>=0; --j)
        balls[j].index-=2;
    texture(m_renderer, 0, 0, map2, l, h);
//    for(int i=0; i<=indexOfMoves; ++i){
//    filledCircleRGBA(m_renderer, balls[i].x[balls[i].index], balls[i].y[balls[i].index], radius, balls[i].R, balls[i].G, balls[i].B, 255);
//    circleRGBA(m_renderer, balls[i].x[balls[i].index], balls[i].y[balls[i].index], radius, 255, 255, 255, 255);
//    circleRGBA(m_renderer, balls[i].x[balls[i].index], balls[i].y[balls[i].index], radius-10, 255, 255, 255, 255);
//    circleRGBA(m_renderer, balls[i].x[balls[i].index], balls[i].y[balls[i].index], radius-20, 255, 255, 255, 255);
//    }
    filledCircleRGBA(m_renderer, save_FP.x, save_FP.y, radius, 0, 0, 0, 255);
    filledCircleRGBA(m_renderer, save_FP.x, save_FP.y+10, radius, 0, 0, 0, 255);
    filledCircleRGBA(m_renderer, save_LP.x, save_LP.y, radius, 0, 0, 0, 255);
    filledCircleRGBA(m_renderer, save_LP.x, save_LP.y+10, radius, 0, 0, 0, 255);
    my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, 109, 109, 109);
texture(m_renderer,x_line-39, y_line-40,"tank.png",80, 100);
filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
    SDL_RenderPresent(m_renderer);
        SDL_RenderClear(m_renderer);
}


}
if(counter>=3)
{  //Mix_PlayChannel(-1,second,0);

    bool sameColor=true;
    while(sameColor)
{  Mix_PlayChannel(-1,second,0);
emtiyaz+=pow(counter,2);
  int arriving_place=balls[last-1].index;
 // cout<<arriving_place<<" "<<endl;
    for(int i=last; i<=indexOfMoves; ++i)
balls[i-counter]=balls[i];
for(int i=0; i<counter; ++i)
    balls[indexOfMoves-i].index=0;
        indexOfMoves-=counter;
        //indexOfMoves-=last;
        //while(balls[first].index>first)
    while(balls[first].index>arriving_place)
    {
    for(int j=first; j>=0; --j)
        balls[j].index-=2;
    texture(m_renderer, 0, 0, map2, l, h);
    for(int i=0; i<=indexOfMoves; ++i){
    filledCircleRGBA(m_renderer, balls[i].x[balls[i].index], balls[i].y[balls[i].index], radius, balls[i].R, balls[i].G, balls[i].B, 255);
    circleRGBA(m_renderer, balls[i].x[balls[i].index], balls[i].y[balls[i].index], radius, 255, 255, 255, 255);
    circleRGBA(m_renderer, balls[i].x[balls[i].index], balls[i].y[balls[i].index], radius-10, 255, 255, 255, 255);
    circleRGBA(m_renderer, balls[i].x[balls[i].index], balls[i].y[balls[i].index], radius-20, 255, 255, 255, 255);
    }
    filledCircleRGBA(m_renderer, save_FP.x, save_FP.y, radius, 0, 0, 0, 255);
    filledCircleRGBA(m_renderer, save_FP.x, save_FP.y+10, radius, 0, 0, 0, 255);
    filledCircleRGBA(m_renderer, save_LP.x, save_LP.y, radius, 0, 0, 0, 255);
    filledCircleRGBA(m_renderer, save_LP.x, save_LP.y+10, radius, 0, 0, 0, 255);
    my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, 109, 109, 109);
texture(m_renderer,x_line-39, y_line-40,"tank.png",80, 100);
filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
    SDL_RenderPresent(m_renderer);
        SDL_RenderClear(m_renderer);
}
counter=1;
s=first;
for(last=s+1; balls[last].R==balls[s].R && balls[last].G==balls[s].G && balls[last].B==balls[s].B; ++last)
    counter++;
    for(first=s-1; balls[first].R==balls[s].R && balls[first].G==balls[s].G && balls[first].B==balls[s].B; --first)
    counter++;
    if(counter<3)
sameColor=false;
cout<<emtiyaz<<endl;
        }
//////enfejar
}
break;
}
}
texture(m_renderer, 0, 0, map2, l, h);
filledEllipseRGBA(m_renderer, x_ball, y_ball, radius_ball, radius_ball, R, G, B, 255);
my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, R, G, B);
texture(m_renderer,x_line-39, y_line-40,"tank.png",80, 100);
filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
Move();
SDL_RenderPresent(m_renderer);
SDL_RenderClear(m_renderer);
x_ball+=40*cos(theta_line);
y_ball-=40*sin(theta_line);
}
x_ball=x_line;
y_ball=y_line;
shot=true;
break;
}
case SDLK_1:{
    Mix_PauseMusic();
    Mix_PlayMusic(background,1);
    break;
}
case SDLK_2:{
    Mix_PauseMusic();
    Mix_PlayMusic(background2,1);
    break;
        }
        case SDLK_3:{
    Mix_PauseMusic();
    Mix_PlayMusic(background3,1);
    break;
        }
        case SDLK_4:{
    Mix_PauseMusic();
    Mix_PlayMusic(background4,1);
    break;
        }
        case SDLK_5:{
    Mix_PauseMusic();
    Mix_PlayMusic(background5,1);
    break;
        }
        case SDLK_6:{
    if(Mix_PlayingMusic() == 0){
        Mix_PlayMusic(background,1);
    }

    else{
        if(Mix_PausedMusic() == 1){
            Mix_ResumeMusic();
        }
        else{
            Mix_PauseMusic();
        }
    }
    break;
        }
        case SDLK_7:{
             if (Volume == 0)
                Mix_PlayChannel(-1,fourth,0);
                else{
            Volume -= 8;
    Mix_Volume(-1, Volume);
            Mix_VolumeMusic(Volume);}
            cout<<Volume;
    break;
        }
         case SDLK_8:{

            if (Volume == 128)
                Mix_PlayChannel(-1,third,0);
                else{
                        Volume += 8;
    Mix_Volume(-1, Volume);
            Mix_VolumeMusic(Volume);}
            cout<<Volume;
    break;
        }
        case SDLK_SPACE:{

            R=ball_colors_R[next];
    G=ball_colors_G[next];
    B=ball_colors_B[next];
    next = (next + 1)%4;
    break;
        }
        case SDLK_ESCAPE:{
           if(Mix_PlayingMusic() == 0){
        Mix_PlayMusic(background,1);
    }

    else{
        if(Mix_PausedMusic() == 1){
            Mix_ResumeMusic();
        }
        else{
            Mix_PauseMusic();
        }
    }

    settingmenu(m_renderer,T,M1,M2);
    Mix_ResumeMusic();
    SDL_Delay(1000);
    break;
    }
         case SDLK_0:{
            if(v>=100){
            R=0;
            G=0;
            B=0;
            v=0;
    draw = true;
            }
            break;
        }
        }
    }
else
{
texture(m_renderer, 0, 0, map2,l, h);


//my_line(m_renderer, x_line, y_line-40, L_line-50, theta_line, width_line-20, R, G, B);
//filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
my_line(m_renderer, x_line, y_line, L_line, theta_line, width_line, 109, 109, 109);
texture(m_renderer,x_line-39, y_line-40,"tank.png",80, 100);
filledEllipseRGBA(m_renderer, x_circle, y_circle-40, 10, 10, R, G, B, 255);
Move();
rect(m_renderer,0,0,v,20,255,0,0,1);
 if(draw){
    rect(m_renderer,0,0,v,20,255,255,255,1);
    v+=0.2;
    if(v>=100){
    draw = false;

    }
 }
SDL_RenderPresent(m_renderer);
//for(int v = 0;v<100;v++){
//    rect(m_renderer,0,0,v,20,255,255,255,1);
//    SDL_RenderPresent(m_renderer);
//    SDL_Delay(100);
//}
SDL_RenderClear(m_renderer);
shot=false;
}


}

    }

}




int main( int argc, char * argv[] )
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    Uint32 FullscreenFlag = SDL_WINDOW_SHOWN;
    SDL_Window * m_window;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( l, h, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = DM.w;
    int H = DM.h;

   SDL_Texture*mTexture = SDL_CreateTexture(m_renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,l,h);
   SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
//   texture(m_renderer, 0, 0, map2, l, h);
    SDL_RenderClear( m_renderer );
    SDL_RenderPresent( m_renderer );
    SDL_SetRenderTarget(m_renderer,mTexture);
SDL_SetRenderTarget(m_renderer,NULL);
SDL_RenderCopy(m_renderer,mTexture,NULL,NULL);
SDL_RenderPresent(m_renderer);
   game();


    SDL_DestroyTexture(mTexture);
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void settingmenu(SDL_Renderer*m_renderer,int T,int &M1,int &M2)
{
            int R1,G1,B1,R2,G2,B2,R3,G3,B3;
   if(T==1)
    {
        R1=60;
        G1=127;
        B1=40;
        R2=199;
        G2=47;
        B2=62;
        R3=229;
        G3=213;
        B3=13;
    }
    else if(T==2)
    {
        R1=59;
        G1=138;
        B1=126;
        R2=185;
        G2=68;
        B2=34;
        R3=231;
        G3=205;
        B3=5;
    }
    else if(T==3)
    {
        R1=143;
        G1=128;
        B1=31;
        R2=194;
        G2=94;
        B2=8;
        R3=90;
        G3=81;
        B3=21;
    }
    else if(T==4)
    {
        R1=200;
        G1=101;
        B1=247;
        R2=233;
        G2=28;
        B2=183;
        R3=55;
        G3=53;
        B3=166;
    }
  SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear(m_renderer);
    SDL_Event*e=new SDL_Event();
        string theme=to_string(T);
        string background="Settingbackground"+theme+".png";
    texture(m_renderer,0,0,background,1280,800);
    if(T==4)
    texture(m_renderer,1150,50,"back4.png",100,100);
    else
    texture(m_renderer,1150,50,"back.png",100,100);
    rect(m_renderer,430,150,500,120,R1,G1,B1,1);
    rect(m_renderer,430,350,500,120,R1,G1,B1,1);
    rect(m_renderer,290,500,300,120,R1,G1,B1,1);
    rect(m_renderer,760,500,300,120,R2,G2,B2,1);
    const char * text1 ="SOUND";
//    textRGBA(m_renderer,565,180,text1,2,52,R3,G3,B3,255);
                 text1 ="MUSIC";
    //textRGBA(m_renderer,580,380,text1,2,52,R3,G3,B3,255);
                 text1 ="HELP";
    //textRGBA(m_renderer,370,530,text1,2,52,R3,G3,B3,255);
                 text1 ="EXIT";
    //textRGBA(m_renderer,830,530,text1,2,52,R3,G3,B3,255);
    SDL_RenderPresent( m_renderer );
    bool menu1=true;
    int counter1=0,counter2=0;
    while(menu1==true)
    {
        SDL_PollEvent(e);
        if(e->type==SDL_MOUSEBUTTONDOWN)
        {
                int x=e->motion.x;
                int y=e->motion.y;
                if(x>=430 && x<=930 && y>=150 && y<=270&&e->type==SDL_MOUSEBUTTONDOWN)
                {
                    SDL_Delay(150);
                    counter1++;
                    text1="SOUND";
                    if(counter1%2==1)
                   rect(m_renderer,430,150,500,120,R2,G2,B2,1);
                   else
                   rect(m_renderer,430,150,500,120,R1,G1,B1,1);
//                   textRGBA(m_renderer,565,180,text1,2,52,R3,G3,B3,255);
                   SDL_RenderPresent(m_renderer);

                }
                else if(x>=430&& x<=930 && y>=350&& y<=470)
                {
                    //music;
                    SDL_Delay(150);
                    counter2++;
                    text1="MUSIC";
                    if(counter2%2==1)
                   rect(m_renderer,430,350,500,120,R2,G2,B2,1);
                   else
                   rect(m_renderer,430,350,500,120,R1,G1,B1,1);
//                   textRGBA(m_renderer,580,380,text1,2,52,R3,G3,B3,255);
                   SDL_RenderPresent(m_renderer);
                }
                else if(x>=290 && x<=590 && y>=500 && y<=620)
                {
                    helpbuttonclick(m_renderer,T,M1,M2);
                   menu1=false;
                }
                else if(x>=760 && x<=960 && y>=500 && y<=620)
                {
                    //mainmenu(m_renderer,T,M1,M2);
                   menu1=false;

                }
                else if(x>=1150&&x<=1250&&y>=50&&y<=150)
                {    menu1=false;

                }

        }
    }
}
void helpbuttonclick(SDL_Renderer*m_renderer,int T,int &M1,int &M2)
{
            int R1,G1,B1,R2,G2,B2,R3,G3,B3;
   if(T==1)
    {
        R1=60;
        G1=127;
        B1=40;
        R2=199;
        G2=47;
        B2=62;
        R3=229;
        G3=213;
        B3=13;
    }
    else if(T==2)
    {
        R1=59;
        G1=138;
        B1=126;
        R2=185;
        G2=68;
        B2=34;
        R3=231;
        G3=205;
        B3=5;
    }
    else if(T==3)
    {
        R1=143;
        G1=128;
        B1=31;
        R2=194;
        G2=94;
        B2=8;
        R3=90;
        G3=81;
        B3=21;
    }
    else if(T==4)
    {
        R1=200;
        G1=101;
        B1=247;
        R2=233;
        G2=28;
        B2=183;
        R3=55;
        G3=53;
        B3=166;
    }
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear(m_renderer);
    SDL_Event*e=new SDL_Event();
        string theme=to_string(T);
        string background;
        if(T==1){
         background="help"+theme+".png";}
        else{
         background="help"+theme+".jpg";}
    texture(m_renderer,0,0,background,1280,800);
    rect(m_renderer,490,665,300,80,R2,G2,B2,1);
    const char * text1 ="BACK";
//    textRGBA(m_renderer,580,680,text1,2,44,R3,G3,B3,255);
    SDL_RenderPresent(m_renderer);
    bool menu1=true;
    while(menu1==true)
    {
       SDL_PollEvent(e);
        if(e->type==SDL_MOUSEBUTTONDOWN)
        {
                int x=e->motion.x;
                int y=e->motion.y;
                if(x>=490&&x<=790&&y>=665&&y<=745)
                {
                    settingmenu(m_renderer,T,M1,M2);
                    menu1=false;
                }
    }

}
}
