#include"windows.h"
#include"process.h"
#include"stdio.h"
#include"iostream"
using namespace std;

int a; //��������
boolean flag[2] = { false,false };
int turn;

unsigned __stdcall Process0(void* param)
{
	do
	{
		flag[0] = true;
		turn = 1; //��ʱP0δ�����ٽ�������Ȼ����P1�����ٽ�����
		while(flag[1] && turn == 1);
		//flag[1]Ϊ���ʾP1ϣ�������ٽ�����turnΪ1��ʾP1���Խ����ٽ��������P0�ȴ���
		a = a + 1;
		cout << "PROCESS0:a = " << a << endl;
		flag[0] = false;//��ʾP0�˳������ٽ�����
	} while (true);
}

unsigned __stdcall Process1(void* param)
{
	do
	{
		flag[1] = true;
		turn = 0;//��ʱP1δ�����ٽ����� ��Ȼ����P0�����ٽ�����
		while(flag[0] && turn == 0);
		//flag[0]Ϊ���ʾP0ϣ�������ٽ�����turnΪ0��ʾP0���Խ����ٽ��������P1�ȴ���
		a = a - 1;
		cout << "PROCESS1:a = " << a << endl;
		flag[1] = false;//��ʾP1�˳������ٽ�����
	} while (true);
}

int main()
{
	_beginthreadex(NULL, 0, Process0, NULL, 0, NULL); 
	_beginthreadex(NULL, 0, Process1, NULL, 0, NULL); 
	for (int k = 0;k < 10000;k++) //�����߳�����
	{
		Sleep(10000000);
	}
	return 0;
}