// Kevin Yang
//

#include "PCalculator.h"

int deleteNode(TreeNode* currentTreeNode, int leftData, int rightData, FILE *fpOutput)
{
    // printNode(currentTreeNode); // Testing what tree looks like when deleted

    // fpOutput;

    free(currentTreeNode->nodeData);
    free(currentTreeNode);

    return 0;
}

int printNode(TreeNode* currentTreeNode, int leftData, int rightData, FILE *fpOutput)
{
    // leftData, rightData;

    if (currentTreeNode->nodeData->dataType == OPERATOR)
        // cout << (char)currentTreeNode->nodeData->data << " ";
        fprintf(fpOutput, "%c", currentTreeNode->nodeData->data);
    else
        // cout << currentTreeNode->nodeData->data << " ";
        fprintf(fpOutput, "%d", currentTreeNode->nodeData->data);

    return 0;
}

int evaluate(TreeNode* currentTreeNode, int leftData, int rightData, FILE *fpOutput)
{
    int nodeValue = 0;

    // fpOutput;

    switch (currentTreeNode->nodeData->data)
    {
    case '+':
        nodeValue = leftData + rightData;
        break;
    case '-':
        nodeValue = leftData - rightData;
        break;
    case '*':
        nodeValue = leftData * rightData;
        break;
    case '/':
        nodeValue = leftData / rightData;
        break;
    default:
        nodeValue = currentTreeNode->nodeData->data;
        break;
    }
    return nodeValue;
}

// void PCalculator::preOrder(TreeNode* currentTreeNode) // PLR
int PCalculator::preOrder(TreeNode* currentTreeNode, FILE* fpOutput, int(*pVisit)(TreeNode*, int, int, FILE* fpOutput))
{
    int nodeValue = 0; int leftData = 0; int rightData = 0;

    if (currentTreeNode != NULL)
    {
        nodeValue = (*pVisit)(currentTreeNode, leftData, rightData, fpOutput); // parent
        // printNode(currentTreeNode); // parent
        leftData = preOrder(currentTreeNode->leftChild, fpOutput, pVisit);
        rightData = preOrder(currentTreeNode->rightChild, fpOutput, pVisit);
    }

    return nodeValue;
}

// postOrder L R P
//void PCalculator::postOrder(TreeNode* currentTreeNode)
int PCalculator::postOrder(TreeNode* currentTreeNode, FILE* fpOutput, int(*pVisit)(TreeNode*, int, int, FILE* fpOutput))
{
    int nodeValue = 0; int leftData = 0; int rightData = 0;

    if (currentTreeNode != NULL)
    {
        leftData = postOrder(currentTreeNode->leftChild, fpOutput, pVisit);
        rightData = postOrder(currentTreeNode->rightChild, fpOutput, pVisit);
        nodeValue = (*pVisit)(currentTreeNode, leftData, rightData, fpOutput); // parent
    }
    return nodeValue;
}

// int PCalculator::inOrder(TreeNode *currentTreeNode) //LPR
int PCalculator::inOrder(TreeNode* currentTreeNode, FILE* fpOutput, int(*pVisit)(TreeNode*, int, int, FILE* fpOutput))
{
    int nodeValue = 0; int leftData = 0; int rightData = 0;

      if (currentTreeNode != NULL)
      {
          leftData = inOrder(currentTreeNode->leftChild, fpOutput, pVisit);
          // printNode(currentTreeNode); //parent
          nodeValue = (*pVisit)(currentTreeNode, leftData, rightData, fpOutput); // parent
          rightData = inOrder(currentTreeNode->rightChild, fpOutput, pVisit);

      }
      return nodeValue;
}

void PCalculator::calculator(void) //main Method
{
    TreeNode *newTreeNode = NULL;
    DataNode *node = NULL;
    TreeNode *root = NULL; // point to begin of tree
    int resultCode = 0; // default to zero
    int result; // result of expression

    cout << "Enter a Math Expression> ";
    node = (DataNode*)malloc(sizeof(DataNode));

    while ((resultCode = scan(node, stdin)) != EOF) // NOT FAIL
    {
       // check for invalid data
        if (resultCode == FAIL)
        {
            cout << "Invalid Data - Will ignore entire expression - Retry\n";
            break;
        }
      newTreeNode = make_TreeNode(node);
      insertTreeNode(newTreeNode, &root);
      node = (DataNode*)malloc(sizeof(DataNode));
    }

    if (resultCode != FAIL)
    {
        cout << "IN ORDER PRINT Travsersal\n";
        result = inOrder(root, stdout, printNode);
        //cout << " = " << result << endl;

        //preOrder
        cout << "\nPre ORDER PRINT Trasversal\n";
        result = preOrder(root, stdout, printNode);
       // cout << " = " << result << endl;

        cout << "\nPost ORDER PRINT Trasversal\n";
        result = postOrder(root, stdout, printNode);
        //cout << " = " << result << endl;

        cout << endl;
        cout << "Post ORDER Evaluate Trasversal\n";
        // result = postOrderCalc(root);
        result = postOrder(root, stdout, evaluate);
        // inOrder(root);
        inOrder(root, stdout, printNode);
        cout << " = " << result << endl;

        cout << "Post Order Delete Trasversal\n";
        postOrder(root, stdout, printNode);
        cout << endl;
        result = postOrder(root, stdout, deleteNode);

    }
}

/*void PCalculator::postOrderDelete(TreeNode* currentTreeNode)
{
    if (currentTreeNode != (TreeNode*)NULL)
    {
        postOrderDelete(currentTreeNode->leftChild);
        postOrderDelete(currentTreeNode->rightChild);

        deleteNode(currentTreeNode);
    }
}

int PCalculator::postOrderCalc(TreeNode* currentTreeNode)
{
    int nodeValue = 0;
    int leftData = 0;
    int rightData = 0;

    if (currentTreeNode != (TreeNode*)NULL)
    {
        leftData = postOrderCalc(currentTreeNode->leftChild);
        rightData = postOrderCalc(currentTreeNode->rightChild);

        nodeValue = evaluate(currentTreeNode, leftData, rightData);
    }
    return nodeValue;
} */

// Making of a tree
void PCalculator::insertTreeNode(TreeNode *newTreeNode, TreeNode **root)
{
    /* is this the first TreeNode? */
    if (*root == (TreeNode*)NULL )
    {
        *root = newTreeNode;
    }
    else
    {
        switch (newTreeNode->nodeData->dataType)
        {
            case OPERATOR:
                newTreeNode->leftChild = *root;
                *root = newTreeNode;
                break;
            case DATA:
                (*root)->rightChild = newTreeNode;
                break;
        }
    }
    return;
}

TreeNode* PCalculator::make_TreeNode(DataNode *data)
{
  TreeNode * newptr = NULL;

  if ((newptr = (TreeNode *)malloc(sizeof(TreeNode))) != (TreeNode *) NULL)
  {
      newptr->nodeData = data;
      newptr->leftChild = (TreeNode *)NULL;
      newptr->rightChild = (TreeNode *)NULL;
  }
  /* return NULL if the Treenode was not allocated */
  return (newptr);
}

int PCalculator::scan(DataNode* node, FILE* fptr)
{
    char c = 0;
    int resultCode = SUCCEED;
    while (isspace(c = (char)fgetc(fptr)) && (c != '\n'))
        ; /* eat the whitespace */

    switch (c) {
    case '+': case '-':
    case '*': case '/':
        (*node).dataType = OPERATOR;
        (*node).data = c;
        /* resultCode = SUCCEED; */ /* as it is initialized */
        break;
    case '0': case '1':
    case '2': case '3':
    case '4': case '5':
    case '6': case '7':
    case '8': case '9':
        (*node).dataType = DATA;
        (*node).data = c - '0';
        /* resultCode = SUCCEED; */ /* as it is initialized */
        break;

    case '\n': case EOF:
        (*node).data = 0;
        resultCode = EOF;
        break;
    default:
        /* anything else is an error */
        (*node).data = c;
        resultCode = FAIL;
        break;
    }
    return resultCode;
}
