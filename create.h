#ifndef CREATE_H_INCLUDED
#define CREATE_H_INCLUDED

void createBullet(int x, int y)
{
    for(int i = 0; i < MAX_BULLETS; i++)
    {
        if(bullets[i]->active != 0)
            continue;

        bullets[i]->active = 1;
        bullets[i]->x = x;
        bullets[i]->y = y;
        bullets[i]->sprite = '-';
        bullets[i]->bulletTime = 0;
        break;
    }
}

void createZombie()
{
    long long ms = getCurrentMillis();
    if(zombieCreateTime + zombie_delay > ms)
        return;
    zombieCreateTime = ms;

    int zombie_type;
    if(zKilled <= 4)
        zombie_type = 1;
    else if(zKilled <= 10)
        zombie_type = RANDOM(1, 2);
    else
        zombie_type = RANDOM(1, 3);

    for(int i = 0; i < MAX_ZOMBIES; i++)
    {
        if(zombies[i]->active == 0)
        {
            if(zombie_type == 1)
            {
                zombies[i]->level = 1;
                zombies[i]->active = 1;
                zombies[i]->x = MAP_X+MAP_WIDTH-1;
                zombies[i]->y = RANDOM(1, MAP_HEIGHT-1);
                zombies[i]->sprite = ZOMBIE_1_SPRITE;
                zombies[i]->zombieTime = 0;
                zombies[i]->hp = ZOMBIE_1_HP;
            }else if(zombie_type == 2)
            {
                zombies[i]->level = 2;
                zombies[i]->active = 1;
                zombies[i]->x = MAP_X+MAP_WIDTH-1;
                zombies[i]->y = RANDOM(1, MAP_HEIGHT-1);
                zombies[i]->sprite = ZOMBIE_2_SPRITE;
                zombies[i]->zombieTime = 0;
                zombies[i]->hp = ZOMBIE_2_HP;
            }else if(zombie_type == 3)
            {
                zombies[i]->level = 3;
                zombies[i]->active = 1;
                zombies[i]->x = MAP_X+MAP_WIDTH-1;
                zombies[i]->y = RANDOM(1, MAP_HEIGHT-1);
                zombies[i]->sprite = ZOMBIE_3_SPRITE;
                zombies[i]->zombieTime = 0;
                zombies[i]->hp = ZOMBIE_3_HP;
            }
            break;
        }
    }
}

#endif // CREATE_H_INCLUDED
