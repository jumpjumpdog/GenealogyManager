#include"siblingTree.h"
#include"cstdlib"
#include"queue"

/*      complete�������ڸ�û������Ľڵ㽨������
        insert�������ڸ��Ѿ�������Ľڵ㽨������ 
 */


FamMemNodePtr   siblingTree::locate(FamMemNodePtr ptr,dataType data)  //����Ŀ��ڵ㣬����ҵ����򷵻�Ŀ��ڵ�ĸ��ڵ�
{
	std::queue <FamMemNodePtr> myQueue;                           //��ջ�洢FamMemNodePtr�Ķ���
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
	cout << pAncenstor->data << "��һ��������:";                       //���pAncenstor�ڵ�ĵ�һ������
	pAncenstor = pAncenstor->pFirstChild;
	while (pAncenstor) {
		cout << pAncenstor->data << "  ";
		pAncenstor = pAncenstor->pNextSibling;
	}
	cout << endl << endl << endl;
}

bool siblingTree::createTree() {                                     //�����һ������ ��������
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������" ;

	root = new FamMemNode();
	if (!root)
	{
		cerr << "�ڴ����ʧ�ܣ�" << endl;
		return false;
	}
	cin >> root->data;
	cout  << "�˼��׵������ǣ�" << root->data << endl<<endl<<endl;;
	return true;
}


void siblingTree::completeTree() {                       //���Ƽ��ף�������ĳ�����ȵ���Ů
	if (!root)
	{
		cout << "����Ϊ��" << endl;
		return;
	}
	dataType nameParent;
	FamMemNodePtr targetNode, temp,recordNode;
	int number;
	cout << "������Ҫ������ͥ���˵�������";
	cin >> nameParent;

    
	if (root->data == nameParent)
	{
		targetNode = root;
		recordNode = targetNode;
	}
	else
	{
		targetNode = locate(root, nameParent);
		if (!targetNode) {                                         //���������ָ���Ľڵ㣬��������
			cout << "δ�ҵ�" << nameParent << endl;
			return;
		}
		else {
			targetNode = Judge(targetNode, nameParent);                //��ʱ��targetNode����ָ��Ŀ��ڵ�
			recordNode = targetNode;
		}
	}
	
	cout  << "������" << nameParent << "�Ķ�Ů������";             
	cin >> number;
	temp = new FamMemNode;

	cout  << "����������" << nameParent << "��Ů������";
	cin >> temp->data;

	targetNode->pFirstChild = temp;                      //���Ȳ�����Ŀ��ڵ��к��ӵ������
	targetNode = temp;

	for (int i = 1; i < number; i++) {
		temp = new FamMemNode;
		cin >> temp->data;
		targetNode->pNextSibling = temp;
		targetNode = targetNode->pNextSibling;
	}  

	outPut(recordNode);                                      //���ָ���ڵ�ĵ�һ������
}




void siblingTree::insertMember() {                               //��ӳ�Ա��������ĳ�����ȵ�����

	dataType parentName;
	FamMemNodePtr targetNode,recordNode;
	cout << "��������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	cin >> parentName;
	if (root->data == parentName)
	{
		targetNode = root;
		recordNode = targetNode;
	}
	else
	{
		targetNode = locate(root, parentName);               //�ҵ�Ŀ��ڵ�,�򷵻�Ŀ��ڵ�ĸ��ڵ���ֵܽڵ�
		if (!targetNode)
		{
			cout << "δ�ҵ�" << parentName << "�ڵ�" << endl;          //���Ŀ��ڵ㲻����
			return;
		}
		recordNode = targetNode;
		targetNode = Judge(targetNode, parentName);                             //�õ�������Ŀ��ڵ�,recordNode�ڵ����ڼ�¼Ŀ��ڵ㣬�����Ժ�Ĳ���
	}
	
	if (targetNode->pFirstChild)                                       //���Ŀ��ڵ㱾����ں���
	{
		targetNode = targetNode->pFirstChild;
		while (targetNode->pNextSibling) {
			targetNode = targetNode->pNextSibling;
		}
		targetNode->pNextSibling = new FamMemNode();
		targetNode->pNextSibling->data = parentName;
		targetNode = targetNode->pNextSibling;
	}
	else {                                                                //���Ŀ��ڵ㱾�����ں���
		targetNode->pFirstChild = new FamMemNode();
		targetNode->pFirstChild->data = parentName;
		targetNode = targetNode->pFirstChild;
	}



	cout << "������" << parentName << "����ӵĶ��ӣ���Ů���������֣�";
	cin >> targetNode->data;
	if (recordNode->pFirstChild&&recordNode->pFirstChild->data == parentName)
		outPut(recordNode->pFirstChild);
	else
		outPut(recordNode->pNextSibling);
}


void siblingTree::disSolveFamily() {                            //��ɢĳ����ͥ��������ʵ�ֵ��ǽ�ɢ����ĳ���������ڵļ�ͥ
	if (!root)
	{
		cout << "����Ϊ��" << endl;
		exit(0);
	}
	FamMemNodePtr targetNode, recordNode;

	dataType nameParent;
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	cin >> nameParent;
	if (nameParent == root->data) {                           //���Ҫ��ɢ����������ͥ����ֱ�ӽ�ɢ��
		delete root;
		root = NULL;
		cout << endl << endl << endl;
		return;
	}

	targetNode = locate(root, nameParent);
	if (!targetNode)
	{
		cout << "δ�ҵ�Ҫɾ��������" << endl<<endl<<endl;
		return;
	}

	recordNode = targetNode;                                    //targetNode�˴���¼����Ŀ��ڵ�ĸ��ڵ�
	targetNode = Judge(targetNode, nameParent);                  //��ʱtargetNodeָ�����Ŀ��ڵ�
	if (targetNode->pNextSibling) {
		if(recordNode->pFirstChild&&recordNode->pFirstChild->data == nameParent)                          //�ж�Ŀ��ڵ���recordNode���ӽڵ㻹���ֵܽڵ�
		       recordNode->pFirstChild = targetNode->pNextSibling;              //���Ҫɾ�����������ֵܽڵ㣬��ô�����ȵ����ȵ���ָ��ָ�����ȵ��ֵ�
		else {
			recordNode->pNextSibling = targetNode->pNextSibling;                 
		}
	}
	else {
		if (recordNode->pFirstChild&&recordNode->pFirstChild->data == nameParent)                          //�ж�Ŀ��ڵ���recordNode���ӽڵ㻹���ֵܽڵ�
			recordNode->pFirstChild = NULL;              //���Ҫɾ�����������ֵܽڵ㣬��ô�����ȵ����ȵ���ָ��ָ�����ȵ��ֵ�
		else {
			recordNode->pNextSibling = NULL;
		}
	}

	outPut(targetNode);                                              //�����ɾ��Ŀ��ڵ��ͥ
	delete targetNode;
	return;

}

bool siblingTree::modifyNode() {
	dataType   initialName, updatedName;
	FamMemNodePtr targetNode;


	cout << "������Ҫ�����������˵ĵ�ǰ������";
	cin >> initialName;
	cout << "��������ĺ��������";
	cin >> updatedName;

	if (root&&root->data == initialName)
		  targetNode = root;
	else
	{
		targetNode = locate(root, initialName);
		if (!targetNode) {
			cout << initialName << "������" << endl;
			return false;
		}
		targetNode = Judge(targetNode, initialName);
	}
	  
	if (!targetNode)
	{
		cout << "δ�ҵ�" << initialName << endl;
		return false;
	}

	targetNode->data = updatedName;
	cout << initialName << "����Ϊ" << updatedName << endl << endl << endl;
	return true;

}



void siblingTree::exitProgram() {
	exit(0);
}