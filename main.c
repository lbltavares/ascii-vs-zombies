#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "define.h"
#include "global.h"

#include "init.h"
#include "inputHandler.h"
#include "update.h"
#include "create.h"
#include "draw.h"

int gameLoop()
{
    char input;
    while(running)
    {
        if(kbhit()) input = getch();
        inputHandler(input);

        if(goldSpawnTime + GOLD_SPAWN_TIME*1000 < getCurrentMillis())
        {
            goldSpawnTime = getCurrentMillis();
            player->gold += 10;
            drawStatus();
        }
        if(zKilled <= 4)
            zombie_delay = 5000;
        else if(zKilled <= 8)
            zombie_delay = 3500;
        else if(zKilled <= 15)
            zombie_delay = 2000;

        createZombie();

        updateTurrets();
        updateBullets();
        updateZombies();

        drawBullets();
        drawZombies();

        updatePlayer();

        input = 0;
    }
    return 0;
}


int main()
{
    setConsoleSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    hidecursor();
    initObjects();
    drawObjects();
    running = 1;
    zKilled = 0;
    zombieCreateTime = 0;
    goldSpawnTime = 0;
    zombie_delay = 5000;

    return gameLoop();
}
