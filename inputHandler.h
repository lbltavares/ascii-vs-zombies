#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED


void inputHandler(char input)
{
    if(input == 'w')
    {
        movePlayer(-1);
        drawPlayer();
    }else if(input == 's')
    {
        movePlayer(1);
        drawPlayer();
    }else if(input == ' ')
    {
        int turret_index = player->y-MAP_Y-1;
        if(player->gold >= turrets[turret_index]->upgradePrice && turrets[turret_index]->level < TURRET_MAX_LEVEL)
        {
            player->gold -= turrets[turret_index]->upgradePrice;
            upgradeTurret(turret_index);
            drawTurret(turret_index);
            drawStatus();
        }
    }
    else if(input == 'k')
    {
        gotoxy(0, 0);
        printf("%d", player->y);
    }
}

void movePlayer(int y)
{
    if(player->y+y > MAP_Y && player->y+y < MAP_Y+MAP_HEIGHT)
        player->y += y;
}

void upgradeTurret(int i)
{
    if(turrets[i]->level >= TURRET_MAX_LEVEL)
        return;

    turrets[i]->level++;
    turrets[i]->fireRate = 1000;
    turrets[i]->sprite = turrets[i]->spriteIndex[turrets[i]->level];
    turrets[i]->upgradePrice = (turrets[i]->level+1)*100;
    turrets[i]->y = player->y;
}

#endif // INPUTHANDLER_H_INCLUDED
