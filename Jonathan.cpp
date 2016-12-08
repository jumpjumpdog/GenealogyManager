#include"siblingTree.h"


using std::ios;

enum Choice
{
	None = 0,A='A', B='B', C='C', D='D', E='E'
};


int main() {
	cout.width(20);
	cout.setf(ios::left);	
	cout << "**          " << "���׹���ϵͳ"<< "             **"<<endl;
	cout << "=================================================="<<endl;
	cout << "**                ��ѡ��Ҫִ�еĲ�����          **"<<endl;
	cout << "**           A  --  ���Ƽ�ͥ                    **"<<endl;
	cout << "**           B  --  ��Ӽ�ͥ��Ա                **"<<endl;
	cout << "**           C  --  ��ɢ�ֲ���ͥ                **"<<endl;
	cout << "**           D  --  ���ļ�ͥ��Ա����            **"<<endl;
	cout << "**           E  --  �˳�����                    **"<<endl;
	cout << "=================================================="<<endl;


	char int_choice;
	Choice choice = None;
	auto myFamily = new siblingTree();
	myFamily->createTree();



	while (true) {
		cout << "������Ҫִ�еĲ�����";
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