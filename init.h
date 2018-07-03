#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

void initObjects()
{
    initPlayer(5, 400, 'P');
    initTurrets();
    initBullets();
    initZombies();
}

void initPlayer(int lives, int gold, char sprite)
{
    player = malloc(sizeof(Player));
    player->lives = lives;
    player->gold = gold;
    player->sprite = sprite;
    player->x = PLAYER_XPOS;
    player->y = MAP_X+MAP_HEIGHT/2;
    player->oldx = player->x;
    player->oldy = player->y;
}

void initTurrets()
{
    for(int i = 0; i < MAX_TURRETS; i++)
    {
        turrets[i] = malloc(sizeof(Turret));
        turrets[i]->level = 0;
        turrets[i]->fireRate = 0;
        turrets[i]->upgradePrice = (turrets[i]->level+1)*100;
        turrets[i]->turretTime = 0;

        turrets[i]->spriteIndex[0] = ' ';
        turrets[i]->spriteIndex[1] = TURRET_1_SPRITE;
        turrets[i]->spriteIndex[2] = TURRET_2_SPRITE;
        turrets[i]->spriteIndex[3] = TURRET_3_SPRITE;

        turrets[i]->sprite = turrets[i]->spriteIndex[turrets[i]->level];
    }
}

void initBullets()
{
    for(int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i] = malloc(sizeof(Bullet));
        bullets[i]->active = 0;
        bullets[i]->x = 0;
        bullets[i]->y = 0;
        bullets[i]->sprite = ' ';
        bullets[i]->bulletTime = 0;
    }
}

void initZombies()
{
    for(int i = 0; i < MAX_ZOMBIES; i++)
    {
        zombies[i] = malloc(sizeof(Zombie));
        zombies[i]->active = 0;
        zombies[i]->x = 0;
        zombies[i]->y = 0;
        zombies[i]->sprite = ' ';
        zombies[i]->zombieTime = 0;
        zombies[i]->hp = ZOMBIE_1_HP;
        zombies[i]->reward = ZOMBIE_1_REWARD;
        zombies[i]->level = 1;

        zombies[i]->spriteIndex[0] = ' ';
        zombies[i]->spriteIndex[1] = ZOMBIE_1_SPRITE;
        zombies[i]->spriteIndex[2] = ZOMBIE_2_SPRITE;
        zombies[i]->spriteIndex[3] = ZOMBIE_3_SPRITE;
    }
}



#endif // INIT_H_INCLUDED
