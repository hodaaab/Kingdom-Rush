#include "rsdl.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <chrono>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define ARCHER "assets/towers/archer.png"
#define CANNON "assets/towers/canon.png"
#define ICY "assets/towers/icy.png"
#define MAGE "assets/towers/mage.png"
#define ORC_UP "assets/enemies/orc/back.png"
#define ORC_DOWN "assets/enemies/orc/front.png"
#define ORC_LEFT "assets/enemies/orc/left.png"
#define ORC_RIGHT "assets/enemies/orc/right.png"
#define WOLF_UP "assets/enemies/wolf/back.png"
#define WOLF_DOWN "assets/enemies/wolf/front.png"
#define WOLF_LEFT "assets/enemies/wolf/left.png"
#define WOLF_RIGHT "assets/enemies/wolf/right.png"
#define DEMON_UP "assets/enemies/demon/back.png"
#define DEMON_DOWN "assets/enemies/demon/front.png"
#define DEMON_LEFT "assets/enemies/demon/left.png"
#define DEMON_RIGHT "assets/enemies/demon/right.png"
#define ARMORED_UP "assets/enemies/armored/back.png"
#define ARMORED_DOWN "assets/enemies/armored/front.png"
#define ARMORED_LEFT "assets/enemies/armored/left.png"
#define ARMORED_RIGHT "assets/enemies/armored/right.png"
#define BLACK_SCREEN "assets/levels/Black_Screen.png"
#define LOSING_MESSAGE "assets/levels/lose.png"
#define WINNING_MESSAGE "assets/levels/win.png"
#define TEXT_SIZE 20
#define FONT_FREESANS "assets/OpenSans.ttf"

#define bullet_speed 10
#define orc_speed 16.4
#define wolf_speed 17.6
#define armor_speed 4.2
#define demon_speed 5.6
#define orc_life 200
#define wolf_life 100
#define armor_life 450
#define demon_life 400
#define ad_loss 3
#define ow_loss 1
#define orc_prize 5
#define wolf_prize 4
#define armor_prize 8
#define demon_prize 8
#define archer_destruct 50
#define cannon_destruct 140
#define mage_destruct 140
#define icy_destruct 30
#define archer_time 700
#define cannon_time 2000
#define mage_time 1500
#define icy_time 2000
#define archer_cost 70
#define cannon_cost 125
#define mage_cost 90
#define icy_cost 80
#define TOW_X 80
#define TOW_Y 60
#define ENEM_X 30
#define ENEM_Y 30
#define rand_min -50
#define rand_max 10
#define tower_range 95
#define cannon_range 50
#define mylife 15
#define mymoney 220
#define bullet_dim 5

using namespace std;

struct Point
{
  int x;
  int y;
};

struct Enemy
{
  char type;
  int life;
  int speed;
  int armor;
  int prize;
  int loss;
  int direction;
  int random;
  Point coor;
};

struct Tower
{
  char type;
  bool physmag;
  bool cannon;
  int destruct;
  int time_limit;
  int cost;
  Point coor;
};

struct Wave
{
  int time;
  vector<int> number;
  vector<char> type;
};

struct Bullet
{
  Point start;
  Point end;
  Point now;
  int index;
  char type;
};

void draw(string backgroundadd,Window* game, vector<Tower> towers, vector<Enemy> enemies, vector<Bullet> bullets,int user_life, int user_money)
{
  game->clear();
  game->draw_bg(backgroundadd,0,0);
  game->show_text("LIFE  "+to_string(user_life)+"  MONEY  "+to_string(user_money),10,10, BLACK,FONT_FREESANS,TEXT_SIZE);
  for(int i=0; i < towers.size(); i++)
  {
    if(towers[i].type == 'a')
      game->draw_png(ARCHER,towers[i].coor.x-35,towers[i].coor.y-40,TOW_X,TOW_Y);
    else if(towers[i].type == 'c')
      game->draw_png(CANNON,towers[i].coor.x-35,towers[i].coor.y-40,TOW_X,TOW_Y);
    else if(towers[i].type == 'm')
      game->draw_png(MAGE,towers[i].coor.x-35,towers[i].coor.y-40,TOW_X,TOW_Y);
    else if(towers[i].type == 'i')
      game->draw_png(ICY,towers[i].coor.x-35,towers[i].coor.y-40,TOW_X,TOW_Y);
  }
  for(int i=0 ; i<enemies.size(); i++)
  {
    if(enemies[i].type == 'o')
      switch(enemies[i].direction)
      {
        case 1: game->draw_png(ORC_RIGHT,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 2: game->draw_png(ORC_UP,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 3: game->draw_png(ORC_LEFT,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 4: game->draw_png(ORC_DOWN,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
      }
    else if(enemies[i].type == 'w')
      switch(enemies[i].direction)
      {
        case 1: game->draw_png(WOLF_RIGHT,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 2: game->draw_png(WOLF_UP,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 3: game->draw_png(WOLF_LEFT,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 4: game->draw_png(WOLF_DOWN,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
      }
    else if(enemies[i].type == 'a')
      switch(enemies[i].direction)
      {
        case 1: game->draw_png(ARMORED_RIGHT,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 2: game->draw_png(ARMORED_UP,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 3: game->draw_png(ARMORED_LEFT,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 4: game->draw_png(ARMORED_DOWN,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
      }
    else if(enemies[i].type == 'd')
      switch(enemies[i].direction)
      {
        case 1: game->draw_png(DEMON_RIGHT,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 2: game->draw_png(DEMON_UP,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 3: game->draw_png(DEMON_LEFT,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
        case 4: game->draw_png(DEMON_DOWN,enemies[i].coor.x+enemies[i].random,enemies[i].coor.y+enemies[i].random,ENEM_X,ENEM_Y); break;
      }
  }
  for(int i=0 ; i<bullets.size() ; i++)
  {
    game->draw_rect(bullets[i].now.x,bullets[i].now.y,bullet_dim,bullet_dim,BLACK);
  }
  game->update_screen();
}

void display_losing_message(Window* game)
{
  game->clear();
	game->draw_bg(BLACK_SCREEN);
	game->draw_png(LOSING_MESSAGE, WINDOW_WIDTH/3-50, WINDOW_HEIGHT/3-50 , 400, 400);
  game->update_screen();
  Delay(4000);
}

void display_winning_message(Window* game)
{
  game->clear();
	game->draw_bg(BLACK_SCREEN);
	game->draw_png(WINNING_MESSAGE, WINDOW_WIDTH/3-50, WINDOW_HEIGHT/3-50 , 400, 400);
  game->update_screen();
  Delay(4000);
}

vector<int> readCoor(string coorfile)
{
  ifstream inputFile(coorfile);
  vector<int> coor;
  if (inputFile.good())
  {
    int value;
    while (inputFile >> value)
    {
      coor.push_back(value);
    }
  }
  return coor;
}

vector<int> readPath(string pathfile)
{
  ifstream inputFile(pathfile);
  vector<int> path;
  if (inputFile.good())
  {
    int value;
    while (inputFile >> value)
    {
      path.push_back(value);
    }
  }
  return path;
}

vector<Wave> readWaves(string wavefile)
{
  string dummy;
  vector<Wave> waves;
  Wave temp_wave;
  int i = 0;
  ifstream inputFile(wavefile);
  while(inputFile >> dummy)
  {
    if(dummy == "wave")
    {
      if(i!=0)
      {
        waves.push_back(temp_wave);
        temp_wave.number.clear();
        temp_wave.type.clear();
      }
      inputFile >> dummy;
      temp_wave.time = stoi(dummy);
      inputFile >> dummy;
      temp_wave.number.push_back(stoi(dummy));
      inputFile >> dummy;
      temp_wave.type.push_back(dummy.at(0));
    }
    else if(dummy == ",")
    {
      inputFile >> dummy;
      temp_wave.number.push_back(stoi(dummy));
      inputFile >> dummy;
      temp_wave.type.push_back(dummy.at(0));
    }
    i++;
  }
  waves.push_back(temp_wave);
  return waves;
}

int checkCoor(int x,int y,vector<int> coor)
{
  for(int i=0 ; i < 8/*coor.size()/4*/ ; i++)
  {
    if(x>coor[i*4] && x<coor[i*4+1] && y>coor[i*4+2] && y<coor[i*4+3])
    {
      return i;
    }
  }
  return 8;
}

void removeTower(vector<Tower>& towers, int x,int y)
{
  towers.erase(remove_if(towers.begin(),towers.end(),[x,y](Tower const& t){return (t.coor.x==x)&&(t.coor.y==y);}),towers.end());
}

void removeEnemy(vector<Enemy>& enemies,vector<Bullet>& bullets, int yfinish, int& user_life, int& user_money)
{
  for(int i=0 ; i<enemies.size() ; i++)
  {
    if(enemies[i].coor.y > yfinish-30)
    {
      for(int j=0 ; j<bullets.size() ; j++)
      {
        if(bullets[j].index == i)
          bullets.erase(bullets.begin()+j);
        else if(bullets[j].index>i)
          bullets[j].index --;
      }
      user_life -= enemies[i].loss;
      enemies.erase(enemies.begin()+i);
    }
    else if(enemies[i].life == 0)
    {
      for(int j=0 ; j<bullets.size() ; j++)
      {
        if(bullets[j].index == i)
          bullets.erase(bullets.begin()+j);
        else if(bullets[j].index>i)
          bullets[j].index --;
      }
      user_money += enemies[i].prize;
      enemies.erase(enemies.begin()+i);
    }
  }
}

void addTower(vector<Tower>& towers, int x, int y, char tower_type, int& user_money)
{
  int invalid_key = 0;
  Tower temp_tower;
  switch(tower_type)
  {
    case 'a' :
              temp_tower.type = 'a';
              temp_tower.physmag = 0;
              temp_tower.cannon = 0;
              temp_tower.destruct = archer_destruct;
              temp_tower.time_limit = archer_time;
              temp_tower.cost = archer_cost;
              temp_tower.coor.x = x;
              temp_tower.coor.y = y;
              break;
    case 'c' :
              temp_tower.type = 'c';
              temp_tower.physmag = 0;
              temp_tower.cannon = 1;
              temp_tower.destruct = cannon_destruct;
              temp_tower.time_limit = cannon_time;
              temp_tower.cost = cannon_cost;
              temp_tower.coor.x = x;
              temp_tower.coor.y = y;
              break;
    case 'm' :
              temp_tower.type = 'm';
              temp_tower.physmag = 1;
              temp_tower.cannon = 0;
              temp_tower.destruct = mage_destruct;
              temp_tower.time_limit = mage_time;
              temp_tower.cost = mage_cost;
              temp_tower.coor.x = x;
              temp_tower.coor.y = y;
              break;
    case 'i' :
              temp_tower.type = 'i';
              temp_tower.physmag = 1;
              temp_tower.cannon = 1;
              temp_tower.destruct = icy_destruct;
              temp_tower.time_limit = icy_time;
              temp_tower.cost = icy_cost;
              temp_tower.coor.x = x;
              temp_tower.coor.y = y;
              break;
    default  :
              invalid_key = 1;
              break;
  }
  if(invalid_key == 0  && user_money-temp_tower.cost>0)
  {
    user_money -= temp_tower.cost;
    removeTower(towers,x,y);
    towers.push_back(temp_tower);
  }
}

void addEnemy(vector<Enemy>& enemies,int x, int y, int dir, Wave wave)
{
  Enemy temp_enemy;
  for(int i=0 ; i<wave.number.size() ; i++)
  {
    for(int j=0 ; j<wave.number[i] ; j++)
    {
      temp_enemy.type = wave.type[i];
      switch(temp_enemy.type)
      {
        case 'o':
                  temp_enemy.life = orc_life;
                  temp_enemy.speed = orc_speed;
                  temp_enemy.armor = 0;
                  temp_enemy.prize = orc_prize;
                  temp_enemy.loss = ow_loss;
                  break;
        case 'w':
                  temp_enemy.life = wolf_life;
                  temp_enemy.speed = wolf_speed;
                  temp_enemy.armor = 0;
                  temp_enemy.prize = wolf_prize;
                  temp_enemy.loss = ow_loss;
                  break;
        case 'a':
                  temp_enemy.life = armor_life;
                  temp_enemy.speed = armor_speed;
                  temp_enemy.armor = 1;
                  temp_enemy.prize = armor_prize;
                  temp_enemy.loss = ad_loss;
                  break;
        case 'd':
                  temp_enemy.life = demon_life;
                  temp_enemy.speed = demon_speed;
                  temp_enemy.armor = 2;
                  temp_enemy.prize = demon_prize;
                  temp_enemy.loss = ad_loss;
                  break;
      }
      temp_enemy.direction = dir;
      temp_enemy.coor.x = x;
      temp_enemy.coor.y = y;
      temp_enemy.random = rand()%(rand_max-rand_min+1)+rand_min;
      enemies.push_back(temp_enemy);
    }
  }
}

bool checkInPath(int x, int y, int xstart, int ystart, int xfinish, int yfinish)
{
  if(((y>ystart && y<yfinish)||(y<ystart && y>yfinish)||y==ystart)&&
      ((x>xstart && x<xfinish)||(x<xstart&&x>xfinish)||x==xstart))
    return 1;
  return 0;
}

bool checkInCircle(int x, int y, int ox, int oy)
{
  if(sqrt(pow((x-ox),2)+pow((y-oy),2))<tower_range)
    return 1;
  return 0;
}

bool checkHit(int x, int y, int xb, int yb)
{
  if(abs(xb-x)<15 && abs(yb-y)<15)
    return 1;
  return 0;
}

void moveEnemy(vector<Enemy>& enemies,vector<int> path,vector<int> dir)
{
  double cosine;
  int sign;
  for(int i=0 ; i<enemies.size(); i++)
  {
    for(int j=0 ; j<path.size()-2 ; j+=2)
    {
      if(checkInPath(enemies[i].coor.x,enemies[i].coor.y,path[j],path[j+1],path[j+2],path[j+3]))
      {
        int dx1 = path[j+2]-path[j];
        int dx = abs(dx1);
        int dy1 = path[j+3]-path[j+1];
        int dy = abs(dy1);
        if(dx1>0) sign = 1; else sign = -1;
        if(dx1==0)
        {
          enemies[i].coor.x = path[j];
          if(dy1>0) sign = 1; else sign = -1;
          enemies[i].coor.y += sign*orc_speed*cosine;
        }
        else
        {
          float cosine = dx/sqrt(pow(dx,2)+pow(dy,2));
          switch(enemies[i].type)
          {
            case 'o': enemies[i].coor.x += sign*(orc_speed*cosine); break;
            case 'w': enemies[i].coor.x += sign*(wolf_speed*cosine); break;
            case 'a': enemies[i].coor.x += sign*(armor_speed*cosine); break;
            case 'd': enemies[i].coor.x += sign*(demon_speed*cosine); break;
          }
          enemies[i].coor.y = path[j+1]+(enemies[i].coor.x - path[j])*dy1/dx1;
        }
        enemies[i].direction = dir[j/2];
        if(!checkInPath(enemies[i].coor.x,enemies[i].coor.y,path[j],path[j+1],path[j+2],path[j+3]))
        {
          enemies[i].coor.x = path[j+2];
          enemies[i].coor.y = path[j+3];
          enemies[i].direction = dir[j/2+1];
        }

        break;
      }
    }
  }
}

void shootEnemy(vector<Tower>& towers, vector<Enemy>& enemies, vector<Bullet>& bullets , int interval)
{
  Bullet temp;
  char temp_type;
  if(interval%archer_time<10)
    temp_type = 'a';
  else if(interval%cannon_time<10)
    temp_type = 'c';
  else if(interval%mage_time<10)
    temp_type = 'm';
  else if(interval%icy_time<10)
    temp_type = 'i';
  else
    temp_type = '0';
  for(int i=0 ; i<towers.size() && towers[i].type == temp_type ; i++)
  {
    for(int j=0 ; j<enemies.size() ; j++)
    {
      if(checkInCircle(enemies[j].coor.x,enemies[j].coor.y,towers[i].coor.x,towers[i].coor.y))
      {
        temp.start.x = towers[i].coor.x;
        temp.start.y = towers[i].coor.y;
        temp.now.x = towers[i].coor.x;
        temp.now.y = towers[i].coor.y;
        temp.end.x = enemies[j].coor.x;
        temp.end.y = enemies[j].coor.y;
        temp.index = j;
        temp.type = temp_type;
      }
      bullets.push_back(temp);
    }
  }
}

void updateBullet(vector<Enemy>& enemies, vector<Bullet>& bullets)
{
  for(int i=0 ; i<bullets.size() ; i++)
  {
    if(checkInCircle(bullets[i].now.x,bullets[i].now.y,bullets[i].start.x,bullets[i].start.y))
    {
      for(int j=0 ; j<enemies.size() ; j++)
      {
        if(bullets[i].index == j)
        {
          bullets[i].end.x = enemies[j].coor.x;
          bullets[i].end.y = enemies[j].coor.y;
          int dx1 = bullets[i].end.x-bullets[i].now.x;
          int dx = abs(dx1);
          int dy1 = bullets[i].end.y-bullets[i].now.y;
          int dy = abs(dy1);
          int sign;
          if(dx1>0) sign = 1; else sign = -1;
          int old = bullets[i].now.x;
          if(dx1==0)
          {
            bullets[i].now.y = bullets[i].end.y;
            continue;
          }
          else
          {
            float cosine = dx/sqrt(pow(dx,2)+pow(dy,2));
            bullets[i].now.x += sign*bullet_speed*cosine;
            bullets[i].now.y += (bullets[i].now.x - old)*dy1/dx1;
          }
        }
        if(checkHit(enemies[j].coor.x, enemies[j].coor.y,bullets[i].now.x,bullets[i].now.y))
        {
          switch(bullets[i].type)
          {
            case 'a': if(enemies[j].type=='a') enemies[j].life-=(archer_destruct/2); else enemies[j].life-=archer_destruct; break;
            case 'c': for(int k=0 ; k<enemies.size() ; k++)
                      {
                        if(checkInCircle(enemies[k].coor.x,enemies[k].coor.y,bullets[i].now.x,bullets[i].now.y))
                        {
                          if(enemies[j].type=='a')
                            enemies[j].life-=(cannon_destruct/2);
                          else
                            enemies[j].life-=cannon_destruct;
                        }
                      }
                      break;
            case 'm': if(enemies[j].type=='d') enemies[j].life-=(mage_destruct/2); else enemies[j].life-=mage_destruct; break;
            case 'i': if(enemies[j].type=='d') enemies[j].life-=(icy_destruct/2); else enemies[j].life-=icy_destruct; break;
          }
          bullets.erase(bullets.begin()+i);
        }
      }
    }
    else
    {
      bullets.erase(bullets.begin()+i);
    }
  }
}

vector<int> whichDir(vector<int> path)
{
  int dx, dy;
  int x1,x2,y1,y2;
  vector<int> dir;
  for(int i=0 ; i<path.size()-2 ; i+=2)
  {
    x1 = path[i];
    y1 = path[i+1];
    x2 = path[i+2];
    y2 = path[i+3];
    dx = x2 - x1;
    dy = y2 - y1;
    if(dx<0 && dy<0)
    {
      if(-dx>-dy)
        dir.push_back(3);
      else if(-dy>-dx)
        dir.push_back(2);
    }
    if(dx>0 && dy<0)
    {
      if(dx>-dy)
        dir.push_back(1);
      else if(dx<-dy)
        dir.push_back(2);
    }
    if(dx<0 && dy>0)
    {
      if(-dx>dy)
        dir.push_back(3);
      else if(-dx<dy)
        dir.push_back(4);
    }
    if(dx>0 && dy>0)
    {
      if(dx>dy)
        dir.push_back(1);
      else if(dx<dy)
        dir.push_back(4);
    }
  }
  return dir;
}

int main() {
  string pathfile,coorfile,wavefile,backgroundadd;
  cin>>pathfile>>coorfile>>wavefile>>backgroundadd;
  Window* game;
  Event ev;
  vector<Tower> towers;
  vector<Enemy> enemies;
  vector<Wave> waves;
  vector<Bullet> bullets;
  int x,y;
  int user_life = mylife;
  int user_money = mymoney;
  int tower_num = 8;
  bool valid_coor = 0;
  char tower_type = '0';
  vector<int> coor,path,dir;
  path = readPath(pathfile);
  dir = whichDir(path);
  coor = readCoor(coorfile);
  waves = readWaves(wavefile);
  srand(time(NULL));
  time_t start_time, end_time;
  auto started = std::chrono::high_resolution_clock::now();
  int elapsed;
  start_time = time(NULL);
  game = new Window(WINDOW_WIDTH,WINDOW_HEIGHT,"Kingdom Rush");
  game->clear();
  game->draw_bg(backgroundadd,0,0);
  game->update_screen();
  while(true)
  {
    ev = game -> pollForEvent();
    end_time = time(NULL);
    elapsed = end_time-start_time;
    if(elapsed > waves.back().time && waves.size()!=0)
    {
      addEnemy(enemies, path[0] , path[1] , dir[0] ,waves.back());
      waves.pop_back();
    }
    auto done = std::chrono::high_resolution_clock::now();
    int interval = (std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count());
    if(interval%200<5)
    {
      moveEnemy(enemies,path,dir);
      shootEnemy(towers, enemies, bullets , interval);
      updateBullet(enemies, bullets);
      removeEnemy(enemies,bullets,path.back(),user_life,user_money);
    }
    draw(backgroundadd,game,towers,enemies,bullets,user_life,user_money);

    if(waves.size()==0 && enemies.size()==0 && user_life!=0)
    {
      display_winning_message(game);
      game->~Window();
      break;
    }
    if(user_life==0)
    {
      display_losing_message(game);
      game->~Window();
      break;
    }

    if(ev.type() == QUIT)
    {
      game -> ~Window();
      break;
    }
    else if(ev.type() == MMOTION)
    {
      y = ev.mouseY();
      x = ev.mouseX();
      draw(backgroundadd,game,towers,enemies,bullets,user_life,user_money);
    }
    else if(ev.type() == KEY_PRESS)
    {
        int x = (coor[tower_num*4]+coor[tower_num*4+1])/2;
        int y = (coor[tower_num*4+2]+coor[tower_num*4+3])/2;
        tower_type = ev.pressedKey();
        if(valid_coor)
        {
          addTower(towers,x,y,tower_type,user_money);
        }
        valid_coor = 0;
        tower_num = 8;
        draw(backgroundadd,game,towers,enemies,bullets,user_life,user_money);
    }
    else if(ev.type() == LCLICK)
    {
      //cout<<x<<"\t"<<y<<endl;
      tower_num = checkCoor(x,y,coor);
      if(tower_num < 8)
        valid_coor = 1;
      else
        valid_coor = 0;
    }
  }
}
