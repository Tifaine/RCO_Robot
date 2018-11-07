#include "loadXML.h"


Action* ouvrirXML(int* nbAction)
{
  FILE *fp;
  mxml_node_t *tree;
  mxml_node_t *node;
  mxml_node_t *nodeBis;
  int indiceActionEnCours=0;
  Action* tabActionTotal;
  fp = fopen("bin/temp.xml", "r");
  if(fp != NULL)
  {
    tree = mxmlLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK);
    fclose(fp);

//On doit pouvoir optimiser et enlever cette boucle... Mais pour l'instant, elle permet de compter le nombre d'action et de malloc comme il faut.
    for (node = mxmlFindElement(tree, tree,"Sequence",NULL, NULL,MXML_DESCEND);
    node != NULL;
    node = mxmlFindElement(node, tree,"Action",NULL, NULL,MXML_DESCEND))
    {
      const char *name = mxmlGetElement(node);
      if (strcmp(name, "Action") == 0 )
      {
        (*(nbAction))++;
      }
    }
    tabActionTotal = (Action*)malloc((*nbAction)*(sizeof(Action)));

    for (node = mxmlFindElement(tree, tree,"Sequence",NULL, NULL,MXML_DESCEND);
    node != NULL;
    node = mxmlFindElement(node, tree,"Action",NULL, NULL,MXML_DESCEND))
    {
      const char *name = mxmlGetElement(node);
      if (strcmp(name, "Action") == 0 )
      {

        tabActionTotal[indiceActionEnCours].numero = atoi(mxmlElementGetAttr(node, "numero"));
        if(mxmlElementGetAttr(node, "timeout") != NULL)
        {
          tabActionTotal[indiceActionEnCours].timeout = atoi(mxmlElementGetAttr(node, "timeout"));
        }else
        {
          tabActionTotal[indiceActionEnCours].timeout = 0;
        }

        const char* type = mxmlElementGetAttr(node, "type");
        nodeBis = mxmlFindElement(node, node,"fils",NULL, NULL,MXML_DESCEND);
        tabActionTotal[indiceActionEnCours].listFils = (char*) mxmlElementGetAttr(nodeBis, "liste");
        nodeBis = mxmlFindElement(node, node,"pere",NULL, NULL,MXML_DESCEND);
        tabActionTotal[indiceActionEnCours].listPere = (char*) mxmlElementGetAttr(nodeBis, "liste");
        nodeBis = mxmlFindElement(node, node,"timeout",NULL, NULL,MXML_DESCEND);
        if(nodeBis!=NULL)
        {
          tabActionTotal[indiceActionEnCours].listTimeOut = (char*) mxmlElementGetAttr(nodeBis, "liste");
        }
        nodeBis = mxmlFindElement(node, node,"parametres",NULL, NULL,MXML_DESCEND);
        printf("Type : %s numero %d fils : %s pere %s\n",type,tabActionTotal[indiceActionEnCours].numero,tabActionTotal[indiceActionEnCours].listFils,tabActionTotal[indiceActionEnCours].listPere);
        if(strcmp(type,"actionServo")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_SERVO;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(2*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "id");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "angle");
          printf("Servo %s %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1]);
        }else if(strcmp(type,"actionDyna")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_DYNA;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(3*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "id");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "angle");
          tabActionTotal[indiceActionEnCours].params[2] = (char*) mxmlElementGetAttr(nodeBis, "vitesse");
          printf("Dyna %s %s %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1],tabActionTotal[indiceActionEnCours].params[2]);
        }else if(strcmp(type,"actionRetourDyna")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_ATTENTE_DYNA;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(2*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "id");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "angle");
          printf("Retour Dyna %s %s \n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1]);
        }else if(strcmp(type,"actionPosition")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_POSITION;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(7*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "x");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "y");
          tabActionTotal[indiceActionEnCours].params[2] = (char*) mxmlElementGetAttr(nodeBis, "vitesse");
          tabActionTotal[indiceActionEnCours].params[3] = (char*) mxmlElementGetAttr(nodeBis, "acc");
          tabActionTotal[indiceActionEnCours].params[4] = (char*) mxmlElementGetAttr(nodeBis, "dec");
          tabActionTotal[indiceActionEnCours].params[5] = (char*) mxmlElementGetAttr(nodeBis, "sens");
          tabActionTotal[indiceActionEnCours].params[6] = (char*) mxmlElementGetAttr(nodeBis, "precision");
          printf("Position x: %s y: %s vitesse: %s acc: %s dec: %s sens: %s preci: %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1],tabActionTotal[indiceActionEnCours].params[2],tabActionTotal[indiceActionEnCours].params[3],tabActionTotal[indiceActionEnCours].params[4],tabActionTotal[indiceActionEnCours].params[5],tabActionTotal[indiceActionEnCours].params[6]);
        }else if(strcmp(type,"actionRotation")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_ORIENTATION;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(3*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "angle");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "vitesse");
          tabActionTotal[indiceActionEnCours].params[2] = (char*) mxmlElementGetAttr(nodeBis, "precision");
          printf("Orientation angle : %s, vitesse %s, preci %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1],tabActionTotal[indiceActionEnCours].params[2]);
        }else if(strcmp(type,"actionDeplacement")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_DEPLACEMENT;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(3*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "id");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "value");
          tabActionTotal[indiceActionEnCours].params[2] = (char*) mxmlElementGetAttr(nodeBis, "vitesse");
          printf("Deplacement id : %s, value %s, vitesse %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1],tabActionTotal[indiceActionEnCours].params[2]);
        }else if(strcmp(type,"actionValeur")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_SET_VALEUR;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(2*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "id");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "value");
          printf("Valeur id : %s, value %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1]);
        }else if(strcmp(type,"actionRetourBlocage")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_ATTENTE_BLOAGE;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(1*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "sensibilite");
          printf("Valeur sensibilite : %s\n",tabActionTotal[indiceActionEnCours].params[0]);
        }else if(strcmp(type,"actionPause")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_ATTENTE_TEMPS;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(1*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "temps");
          printf("Pause temps : %s\n",tabActionTotal[indiceActionEnCours].params[0]);
        }else if(strcmp(type,"actionVar")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_SET_VARIABLE;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(3*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "numero");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "cible");
          tabActionTotal[indiceActionEnCours].params[2] = (char*) mxmlElementGetAttr(nodeBis, "commande");
          printf("Var numero : %s cible : %s commande %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1],tabActionTotal[indiceActionEnCours].params[2]);
        }else if(strcmp(type,"actionRetourVar")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_GET_VARIABLE;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(4*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "numero");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "cible");
          tabActionTotal[indiceActionEnCours].params[2] = (char*) mxmlElementGetAttr(nodeBis, "condition");
          tabActionTotal[indiceActionEnCours].params[3] = (char*) mxmlElementGetAttr(nodeBis, "value");
          printf("Retour var numero : %s cible : %s condition %s value %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1],tabActionTotal[indiceActionEnCours].params[2],tabActionTotal[indiceActionEnCours].params[3]);
        }else if(strcmp(type,"actionGPIO")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_GPIO;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(2*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "pin");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "value");
          printf("Valeur pin : %s, value %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1]);
        }else if(strcmp(type,"actionRetourGpio")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_RETOUR_GPIO;
          tabActionTotal[indiceActionEnCours].params = (char**)malloc(2*sizeof(char*));
          tabActionTotal[indiceActionEnCours].params[0] = (char*) mxmlElementGetAttr(nodeBis, "pin");
          tabActionTotal[indiceActionEnCours].params[1] = (char*) mxmlElementGetAttr(nodeBis, "value");
          printf("Valeur pin : %s, value %s\n",tabActionTotal[indiceActionEnCours].params[0],tabActionTotal[indiceActionEnCours].params[1]);
        }else if(strcmp(type,"actionDepart")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_ENTREE;
          printf("Départ \n");
        }else if(strcmp(type,"actionFin")==0)
        {
          tabActionTotal[indiceActionEnCours].type = TYPE_FIN;
          printf("Fin\n");
        }else
        {
          printf("Type unknown !\n");
        }
        indiceActionEnCours++;
      }

    }
  }else
  {
    printf("Nope\n");
  }

  printf("\n\n\nFin parsage %d\n\n\n",tabActionTotal[28].type);
  return tabActionTotal;
}
