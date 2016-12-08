#pragma once

#include"iostream"
#include"string"
#include"queue"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;



typedef string dataType;

typedef struct  FamMemNode {                                      //存储节点的数据结构
	FamMemNode* pFirstChild = NULL;
	FamMemNode* pNextSibling = NULL;
	dataType  data;

}FamMemNode, *FamMemNodePtr;

class siblingTree {
public:
	bool createTree();
	bool modifyNode();
	void completeTree();
	void disSolveFamily();
	void insertMember();
	void exitProgram();



	siblingTree() :root(NULL) {};
	void outPut(FamMemNodePtr);
	FamMemNodePtr  Judge(FamMemNodePtr, dataType);
	FamMemNodePtr  getRoot() { return root; };
	FamMemNodePtr  locate(FamMemNodePtr, dataType);
private:
	FamMemNodePtr root;
};


