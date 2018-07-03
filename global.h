#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

int running;
int zKilled;
int zombie_delay;
long long goldSpawnTime;
long long zombieCreateTime;

typedef struct
{
    int x, y, oldx, oldy;
    int lives, gold;
    char sprite;
}Player;

typedef struct
{
    int active;
    int x, y;
    long long bulletTime;
    char sprite;
}Bullet;

typedef struct
{
    int y;
    int level;
    int fireRate;
    int upgradePrice;
    int spriteIndex[TURRET_MAX_LEVEL+1];
    long long turretTime;
    char sprite;
}Turret;

typedef struct
{
    int active;
    int level;
    int reward;
    int hp;
    int hitPoints;
    int x, y;
    int spriteIndex[ZOMBIE_MAX_LEVEL+1];
    long long zombieTime;
    char sprite
}Zombie;

Player *player;
Turret *turrets[MAX_TURRETS];
Bullet *bullets[MAX_BULLETS];
Zombie *zombies[MAX_ZOMBIES];
#endif // GLOBAL_H_INCLUDED
