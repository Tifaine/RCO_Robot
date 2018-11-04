#include "odometrie.h"
#include <stdio.h>
#include <stdlib.h>

void calculPosition(roboclaw* rc, Robot* robot)
{

}

void initOdometrie(roboclaw* rc, Robot* robot)
{
  robot->coeffLongG=  0.0489441484;
  robot->coeffLongD=  0.0489296636;
  robot->coeffAngleG= 0.0108754758;
  robot->coeffAngleD= 0.0108584183;
  
  if(roboclaw_encoders(rc,  0x80, &(robot->codeurGauche), &(robot->codeurDroit)) != ROBOCLAW_OK )
		{
			fprintf(stderr, "problem communicating with roboclaw, terminating\n");
		}
}
