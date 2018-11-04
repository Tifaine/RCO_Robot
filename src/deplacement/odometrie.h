#ifndef ODOMETRIE_H
#define ODOMETRIE_H

#include "../lib/roboclaw/roboclaw.h"
#include "../struct/structRobot.h"

void calculPosition(roboclaw* rc, Robot* robot);
void initOdometrie(roboclaw* rc, Robot* robot);

#endif //ODOMETRIE_H
