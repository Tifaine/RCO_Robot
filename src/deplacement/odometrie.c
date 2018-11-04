#include "odometrie.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int32_t codeurGauchePrecedent;
int32_t codeurDroitPrecedent;

float orientationPre;

int32_t deltaComptG;
int32_t deltaComptD;

float dAngle, dDeplacement, dX, dY;

void calculPosition(roboclaw* rc, Robot* robot)
{
  codeurGauchePrecedent = robot->codeurGauche;
  codeurDroitPrecedent = robot->codeurDroit;
  orientationPre = robot->orientationRobot;

  roboclaw_encoders(rc,  0x80, &(robot->codeurGauche), &(robot->codeurDroit));
  deltaComptG = robot->codeurGauche - codeurGauchePrecedent;
  deltaComptD = robot->codeurDroit - codeurDroitPrecedent;

  robot->orientationRobot += robot->coeffAngleD * deltaComptD - robot->coeffAngleG * deltaComptG;
  if(robot->orientationRobot > 180)
  {
    orientationPre -= 360;
    robot->orientationRobot-=360.;
  }else if(robot->orientationRobot < -180.)
  {
    orientationPre += 360.;
    robot->orientationRobot += 360.;
  }

  dAngle = (robot->orientationRobot + orientationPre)/2.;
  dDeplacement = (robot->coeffLongD * deltaComptD + robot->coeffLongG * deltaComptG) / 2.;
  dX = dDeplacement * cos((double)(dAngle * (M_PI / 180)));
  dY = dDeplacement * sin((double)(dAngle * (M_PI / 180)));

  robot->distanceParcourue+=dDeplacement;

  robot->xRobot += dX;
  robot->yRobot += dY;
}

void initOdometrie(roboclaw* rc, Robot* robot)
{
  robot->coeffLongG=  -0.0489441484;
  robot->coeffLongD=  0.0489296636;
  robot->coeffAngleG= -0.0108754758;
  robot->coeffAngleD= 0.0108584183;

  if(roboclaw_encoders(rc,  0x80, &(robot->codeurGauche), &(robot->codeurDroit)) != ROBOCLAW_OK )
  {
    fprintf(stderr, "problem communicating with roboclaw, terminating\n");
  }else
  {
    codeurGauchePrecedent = robot->codeurGauche;
    codeurDroitPrecedent = robot->codeurDroit;
    orientationPre = robot->orientationRobot;
  }
}
