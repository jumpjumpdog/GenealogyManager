#include"siblingTree.h"


using std::ios;

enum Choice
{
	None = 0,A='A', B='B', C='C', D='D', E='E'
};


int main() {
	cout.width(20);
	cout.setf(ios::left);	
	cout << "**          " << "家谱管理系统"<< "             **"<<endl;
	cout << "=================================================="<<endl;
	cout << "**                请选择要执行的操作：          **"<<endl;
	cout << "**           A  --  完善家庭                    **"<<endl;
	cout << "**           B  --  添加家庭成员                **"<<endl;
	cout << "**           C  --  解散局部家庭                **"<<endl;
	cout << "**           D  --  更改家庭成员姓名            **"<<endl;
	cout << "**           E  --  退出程序                    **"<<endl;
	cout << "=================================================="<<endl;


	char int_choice;
	Choice choice = None;
	auto myFamily = new siblingTree();
	myFamily->createTree();



	while (true) {
		cout << "请输入要执行的操作：";
		cin >> int_choice;
		choice = (Choice)int_choice;
		switch (choice)
		{
		case A:
			myFamily->completeTree(); break;
		case B:
			myFamily->insertMember(); break;
		case C:
			myFamily->disSolveFamily(); break;
		case D:
			myFamily->modifyNode(); break;
		case E:
			myFamily->exitProgram(); break;
		default:
			break;
		}
	}
	


	return 0;
}