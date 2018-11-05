#include "loadXML.h"


int ouvrirXML()
{
  FILE *fp;
  mxml_node_t *tree;
  mxml_node_t *node;
  mxml_node_t *nodeBis;
  fp = fopen("bin/init.xml", "r");
  if(fp != NULL)
  {
    tree = mxmlLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK);
    fclose(fp);

    for (node = mxmlFindElement(tree, tree,"Sequence",NULL, NULL,MXML_DESCEND);
      node != NULL;
      node = mxmlFindElement(node, tree,"Action",NULL, NULL,MXML_DESCEND))
        {
          const char *name = mxmlGetElement(node);
          if (strcmp(name, "Action") == 0 )
          {
            Action act;
            act.numero = atoi(mxmlElementGetAttr(node, "numero"));

            const char* type = mxmlElementGetAttr(node, "type");
            nodeBis = mxmlFindElement(node, node,"fils",NULL, NULL,MXML_DESCEND);
            act.listFils = (char*) mxmlElementGetAttr(nodeBis, "liste");
            nodeBis = mxmlFindElement(node, node,"pere",NULL, NULL,MXML_DESCEND);
            act.listPere = (char*) mxmlElementGetAttr(nodeBis, "liste");
            nodeBis = mxmlFindElement(node, node,"parametres",NULL, NULL,MXML_DESCEND);
            if(strcmp(type,"actionServo")==0)
            {
              act.params = (char**)malloc(2*sizeof(char*));
              act.params[0] = (char*) mxmlElementGetAttr(nodeBis, "id");
              act.params[1] = (char*) mxmlElementGetAttr(nodeBis, "angle");
            }
            printf("Type : %s numero %d fils : %s pere %s\n",type,act.numero,act.listFils,act.listPere);
          }

        }
  }else
  {
    printf("Nope\n");
  }


      return 1;
    }
