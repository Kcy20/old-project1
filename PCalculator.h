// Kevin Yang 

#ifndef Calculator_hpp
#define Calculator_hpp
#include <fstream>
#include <iostream>
using namespace std;

#define OPERATOR 0
#define DATA 1

#define FAIL 1
#define SUCCEED 0

typedef
struct
{
  int data;
  int dataType;
} DataNode;

typedef
struct node
{
  DataNode  *nodeData;

  struct node  *leftChild;
  struct node  *rightChild;
} TreeNode;

// Methods that can be passed outside of class.
int evaluate(TreeNode* currentTreeNode, int leftData, int rightData, FILE *fpOutput);
int deleteNode(TreeNode* currentTreeNode, int leftData, int rightData, FILE* fpOutput);
int printNode(TreeNode* currentTreeNode, int leftData, int rightData, FILE* fpOutput);

class PCalculator
{
public:
    void calculator(void);

private:
    // building the tree - dont touch
    int scan(DataNode *data, FILE *fptr);
    TreeNode* make_TreeNode(DataNode *data);
    void insertTreeNode(TreeNode *newTreeNode, TreeNode **root);

    // traversals
    int inOrder(TreeNode* currentTreeNode, FILE * fpOutput, int(*pVisit)(TreeNode*, int, int, FILE *fpOutput));
    int preOrder(TreeNode* currentTreeNode, FILE *fpOutput, int(*pVisit)(TreeNode*, int, int, FILE *fpOutput));
    int postOrder(TreeNode* currentTreeNode, FILE *fpOutput, int(*pVisit)(TreeNode *, int , int, FILE *fpOutput));

    // remove and pass in evaulate, delete, print
    // int postOrderCalc(TreeNode* currentTreeNode);
    // void postOrderDelete(TreeNode* currentTreeNode);

    // moved out of class
    // int evaluate(TreeNode* currentTreeNode, int leftData, int rightData);
   // void deleteNode(TreeNode* currentTreeNode, int leftData, int rightData);
   // int printNode(TreeNode* currentTreeNode, int leftData, int rightData);
};


# endif /* Calculator_hpp */
