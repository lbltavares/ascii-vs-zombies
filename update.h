#ifndef UPDATE_H_INCLUDED
#define UPDATE_H_INCLUDED

void updateTurrets()
{
    long long ms = getCurrentMillis();
    for(int i = 0; i < MAX_TURRETS; i++)
    {
        if((turrets[i]->turretTime + turrets[i]->fireRate > ms) || turrets[i]->level == 0)
            continue;
        turrets[i]->turretTime = ms;

        createBullet(TURRET_XPOS+1, turrets[i]->y);
    }
}

void updateBullets()
{
    for(int i = 0; i < MAX_BULLETS; i++)
    {
        if(bullets[i]->active == 0)
            continue;

        gotoxy(bullets[i]->x+1, bullets[i]->y);
        char c = getCursorChar();

        if(c == ZOMBIE_1_SPRITE || c == ZOMBIE_2_SPRITE || c == ZOMBIE_3_SPRITE)
        {
            zombies[findZombie(bullets[i]->x+1, bullets[i]->y)]->hp -= 50;
            bullets[i]->active = 0;
            gotoxy(bullets[i]->x, bullets[i]->y);
            printf(" ");
        }
        else if(c != ' ')
        {
            bullets[i]->active = 0;
            gotoxy(bullets[i]->x, bullets[i]->y);
            printf(" ");
        }
    }
}

void updatePlayer()
{
    if(player->lives <= 0)
    {
        gameOver();
    }
}

int findZombie(int x, int y)
{
    for(int i = 0; i < MAX_ZOMBIES; i++)
    {
        if(zombies[i]->x == x && zombies[i]->y == y)
            return i;
    }
    return -1;
}

int findTurret(int y)
{
    for(int i = 0; i < MAX_TURRETS; i++)
    {
        if(turrets[i]->y == y)
            return i;
    }
    return -1;
}

void gameOver()
{
    system("cls");
    printf("GameOver!\n\n");
    running = 0;
}

void updateZombies()
{
    for(int i = 0; i < MAX_ZOMBIES; i++)
    {
        if(zombies[i]->active == 0)
            continue;

        if(zombies[i]->hp <= 0)
        {
            zombies[i]->active = 0;
            player->gold += zombies[i]->reward;
            zKilled++;
            drawStatus();
            gotoxy(zombies[i]->x, zombies[i]->y);
            printf(" ");
        }
        if(zombies[i]->x == TURRET_XPOS+1)
        {
            player->lives--;
            if(player->gold >= 100)
                player->gold -= 100;
            else
                player->gold = 100;
            zombies[i]->active = 0;
            int index = findTurret(zombies[i]->y);
            if(index != -1)
            {
                turrets[index]->level = 0;
                gotoxy(zombies[i]->x-1, zombies[i]->y);
                printf(" ");
            }
            gotoxy(zombies[i]->x, zombies[i]->y);
            printf(" ");
            drawStatus();
        }
    }
}

#endif // UPDATE_H_INCLUDED
