#include"siblingTree.h"
#include"cstdlib"
#include"queue"

/*      complete函数用于给没有子孙的节点建立家族
        insert函数用于给已经有子孙的节点建立家族 
 */


FamMemNodePtr   siblingTree::locate(FamMemNodePtr ptr,dataType data)  //查找目标节点，如果找到，则返回目标节点的父节点
{
	std::queue <FamMemNodePtr> myQueue;                           //建栈存储FamMemNodePtr的队列
		myQueue.push(ptr);
		while (!myQueue.empty()) {
			ptr = myQueue.front();
			myQueue.pop();
			if ( (ptr->pFirstChild&&(ptr->pFirstChild->data == data)) || (ptr->pNextSibling&&(ptr->pNextSibling->data == data)))
				return ptr;
			else
			{
				if (ptr->pNextSibling)
					myQueue.push(ptr->pNextSibling);
				if (ptr->pFirstChild)
					myQueue.push(ptr->pFirstChild);	
		     }	
	}
		return NULL;
}


FamMemNodePtr siblingTree::Judge(FamMemNodePtr  pAncenstor, dataType data) {

	if (pAncenstor->pFirstChild&&pAncenstor->pFirstChild->data == data)
		return pAncenstor->pFirstChild;
	else
		return pAncenstor->pNextSibling;
};

void siblingTree::outPut(FamMemNodePtr pAncenstor) {
	cout << pAncenstor->data << "第一代子孙是:";                       //输出pAncenstor节点的第一代子孙
	pAncenstor = pAncenstor->pFirstChild;
	while (pAncenstor) {
		cout << pAncenstor->data << "  ";
		pAncenstor = pAncenstor->pNextSibling;
	}
	cout << endl << endl << endl;
}

bool siblingTree::createTree() {                                     //输入第一个人名 当作祖先
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：" ;

	root = new FamMemNode();
	if (!root)
	{
		cerr << "内存分配失败！" << endl;
		return false;
	}
	cin >> root->data;
	cout  << "此家谱的祖先是：" << root->data << endl<<endl<<endl;;
	return true;
}


void siblingTree::completeTree() {                       //完善家谱，即完善某个祖先的子女
	if (!root)
	{
		cout << "家谱为空" << endl;
		return;
	}
	dataType nameParent;
	FamMemNodePtr targetNode, temp,recordNode;
	int number;
	cout << "请输入要建立家庭的人的姓名：";
	cin >> nameParent;

    
	if (root->data == nameParent)
	{
		targetNode = root;
		recordNode = targetNode;
	}
	else
	{
		targetNode = locate(root, nameParent);
		if (!targetNode) {                                         //如果不存在指定的节点，函数结束
			cout << "未找到" << nameParent << endl;
			return;
		}
		else {
			targetNode = Judge(targetNode, nameParent);                //此时，targetNode真正指向目标节点
			recordNode = targetNode;
		}
	}
	
	cout  << "请输入" << nameParent << "的儿女的人数";             
	cin >> number;
	temp = new FamMemNode;

	cout  << "请依次输入" << nameParent << "儿女的姓名";
	cin >> temp->data;

	targetNode->pFirstChild = temp;                      //首先不考虑目标节点有孩子的情况；
	targetNode = temp;

	for (int i = 1; i < number; i++) {
		temp = new FamMemNode;
		cin >> temp->data;
		targetNode->pNextSibling = temp;
		targetNode = targetNode->pNextSibling;
	}  

	outPut(recordNode);                                      //输出指定节点的第一代子孙
}




void siblingTree::insertMember() {                               //添加成员，即增加某个祖先的子孙

	dataType parentName;
	FamMemNodePtr targetNode,recordNode;
	cout << "请输入你要添加儿子（或女儿）的人的姓名：";
	cin >> parentName;
	if (root->data == parentName)
	{
		targetNode = root;
		recordNode = targetNode;
	}
	else
	{
		targetNode = locate(root, parentName);               //找到目标节点,则返回目标节点的父节点或兄弟节点
		if (!targetNode)
		{
			cout << "未找到" << parentName << "节点" << endl;          //如果目标节点不存在
			return;
		}
		recordNode = targetNode;
		targetNode = Judge(targetNode, parentName);                             //得到真正的目标节点,recordNode节点用于记录目标节点，方便以后的操作
	}
	
	if (targetNode->pFirstChild)                                       //如果目标节点本身存在孩子
	{
		targetNode = targetNode->pFirstChild;
		while (targetNode->pNextSibling) {
			targetNode = targetNode->pNextSibling;
		}
		targetNode->pNextSibling = new FamMemNode();
		targetNode->pNextSibling->data = parentName;
		targetNode = targetNode->pNextSibling;
	}
	else {                                                                //如果目标节点本身不存在孩子
		targetNode->pFirstChild = new FamMemNode();
		targetNode->pFirstChild->data = parentName;
		targetNode = targetNode->pFirstChild;
	}



	cout << "请输入" << parentName << "新添加的儿子（或女儿）的名字：";
	cin >> targetNode->data;
	if (recordNode->pFirstChild&&recordNode->pFirstChild->data == parentName)
		outPut(recordNode->pFirstChild);
	else
		outPut(recordNode->pNextSibling);
}


void siblingTree::disSolveFamily() {                            //解散某个家庭，本程序实现的是解散包括某个祖先在内的家庭
	if (!root)
	{
		cout << "家谱为空" << endl;
		exit(0);
	}
	FamMemNodePtr targetNode, recordNode;

	dataType nameParent;
	cout << "请输入要解散家庭的人的姓名：";
	cin >> nameParent;
	if (nameParent == root->data) {                           //如果要解散的是整个家庭，则直接解散；
		delete root;
		root = NULL;
		cout << endl << endl << endl;
		return;
	}

	targetNode = locate(root, nameParent);
	if (!targetNode)
	{
		cout << "未找到要删除的祖先" << endl<<endl<<endl;
		return;
	}

	recordNode = targetNode;                                    //targetNode此处记录的是目标节点的父节点
	targetNode = Judge(targetNode, nameParent);                  //此时targetNode指向的是目标节点
	if (targetNode->pNextSibling) {
		if(recordNode->pFirstChild&&recordNode->pFirstChild->data == nameParent)                          //判断目标节点是recordNode的子节点还是兄弟节点
		       recordNode->pFirstChild = targetNode->pNextSibling;              //如果要删除的祖先有兄弟节点，那么将祖先的祖先的子指针指向祖先的兄弟
		else {
			recordNode->pNextSibling = targetNode->pNextSibling;                 
		}
	}
	else {
		if (recordNode->pFirstChild&&recordNode->pFirstChild->data == nameParent)                          //判断目标节点是recordNode的子节点还是兄弟节点
			recordNode->pFirstChild = NULL;              //如果要删除的祖先有兄弟节点，那么将祖先的祖先的子指针指向祖先的兄弟
		else {
			recordNode->pNextSibling = NULL;
		}
	}

	outPut(targetNode);                                              //输出并删除目标节点家庭
	delete targetNode;
	return;

}

bool siblingTree::modifyNode() {
	dataType   initialName, updatedName;
	FamMemNodePtr targetNode;


	cout << "请输入要更改姓名的人的当前姓名：";
	cin >> initialName;
	cout << "请输入更改后的姓名：";
	cin >> updatedName;

	if (root&&root->data == initialName)
		  targetNode = root;
	else
	{
		targetNode = locate(root, initialName);
		if (!targetNode) {
			cout << initialName << "不存在" << endl;
			return false;
		}
		targetNode = Judge(targetNode, initialName);
	}
	  
	if (!targetNode)
	{
		cout << "未找到" << initialName << endl;
		return false;
	}

	targetNode->data = updatedName;
	cout << initialName << "改名为" << updatedName << endl << endl << endl;
	return true;

}



void siblingTree::exitProgram() {
	exit(0);
}