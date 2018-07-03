#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

void drawObjects()
{
    drawMap();
    drawStatus();
    drawPlayer();
}

void drawMap()
{
    drawframe(MAP_X, MAP_Y, MAP_X+MAP_WIDTH, MAP_Y+MAP_HEIGHT, 7, 7, "");
}

void drawStatus()
{
    drawframe(STATUS_X, STATUS_Y, STATUS_X+STATUS_WIDTH, STATUS_Y+STATUS_HEIGHT, 7, 7, "");

    int xpos_lives = 1;
    int ypos_lives = 1;
    int xpos_gold  = 1;
    int ypos_gold  = 2;
    int xpos_zombies = 1;
    int ypos_zombies = 3;
    gotoxy(STATUS_X+xpos_lives, STATUS_Y+ypos_lives);
    for(int x = 0; x < STATUS_WIDTH-1; x++) printf(" ");
    gotoxy(STATUS_X+xpos_lives, STATUS_Y+ypos_lives);
    printf("Lives: %d", player->lives);

    gotoxy(STATUS_X+xpos_gold, STATUS_Y+ypos_gold);
    for(int x = 0; x < STATUS_WIDTH-1; x++) printf(" ");
    gotoxy(STATUS_X+xpos_gold, STATUS_Y+ypos_gold);
    printf("Gold: %d", player->gold);

    gotoxy(STATUS_X+xpos_zombies, STATUS_Y+ypos_zombies);
    for(int x = 0; x < STATUS_WIDTH-1; x++) printf(" ");
    gotoxy(STATUS_X+xpos_zombies, STATUS_Y+ypos_zombies);
    printf("Zombies Killed: %d", zKilled);
}

void drawPlayer()
{
    gotoxy(player->oldx, player->oldy);
    printf(" ");
    gotoxy(player->x, player->y);
    printf("%c", player->sprite);
    player->oldx = player->x;
    player->oldy = player->y;
}

void drawTurret(int i)
{
    gotoxy(TURRET_XPOS, MAP_Y+1+i);
    printf("%c", turrets[i]->sprite);
}

void drawBullets()
{
    long long ms = getCurrentMillis();
    for(int i = 0; i < MAX_BULLETS; i++)
    {
        if(bullets[i]->active == 0)
            continue;
        if(bullets[i]->bulletTime + BULLET_SPEED > ms)
            continue;
        bullets[i]->bulletTime = ms;

        gotoxy(bullets[i]->x, bullets[i]->y);
        printf(" ");

        bullets[i]->x++;
        gotoxy(bullets[i]->x, bullets[i]->y);
        printf("%c", bullets[i]->sprite);
    }
}

void drawZombies()
{
    long long ms = getCurrentMillis();
    int zSpeed;
    for(int i = 0; i < MAX_ZOMBIES; i++)
    {
        if(zombies[i]->active == 0)
            continue;
        if(zombies[i]->level == 1)
            zSpeed = ZOMBIE_1_SPEED;
        else if(zombies[i]->level == 2)
            zSpeed = ZOMBIE_2_SPEED;
        else if(zombies[i]->level == 3)
            zSpeed = ZOMBIE_3_SPEED;

        if(zombies[i]->zombieTime + zSpeed > ms)
            continue;
        zombies[i]->zombieTime = ms;

        gotoxy(zombies[i]->x, zombies[i]->y);
        printf(" ");

        zombies[i]->x--;
        gotoxy(zombies[i]->x, zombies[i]->y);
        printf("%c", zombies[i]->sprite);
    }
}

#endif // DRAW_H_INCLUDED
