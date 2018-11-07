#include "management.h"

char* listActionEnCours = "0,1,2,3,4,5,6,7,8";

void gestionAction(Action* listAction, Robot* robot)
{

}

void updateActionEnCours(Action* listAction)
{
  // Returns first token
  char src[30];
  strcpy(src,listActionEnCours);
    char *token = strtok(src, ",");

    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, ",");
    }
}
