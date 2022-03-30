#include"windows.h"
#include"process.h"
#include"stdio.h"
#include"iostream"
using namespace std;

int a; //共享数据
boolean flag[2] = { false,false };
int turn;

unsigned __stdcall Process0(void* param)
{
	do
	{
		flag[0] = true;
		turn = 1; //此时P0未进入临界区，仍然允许P1进入临界区。
		while(flag[1] && turn == 1);
		//flag[1]为真表示P1希望访问临界区，turn为1表示P1可以进入临界区，因此P0等待。
		a = a + 1;
		cout << "PROCESS0:a = " << a << endl;
		flag[0] = false;//表示P0退出访问临界区。
	} while (true);
}

unsigned __stdcall Process1(void* param)
{
	do
	{
		flag[1] = true;
		turn = 0;//此时P1未进入临界区， 仍然允许P0进入临界区。
		while(flag[0] && turn == 0);
		//flag[0]为真表示P0希望访问临界区，turn为0表示P0可以进入临界区，因此P1等待。
		a = a - 1;
		cout << "PROCESS1:a = " << a << endl;
		flag[1] = false;//表示P1退出访问临界区。
	} while (true);
}

int main()
{
	_beginthreadex(NULL, 0, Process0, NULL, 0, NULL); 
	_beginthreadex(NULL, 0, Process1, NULL, 0, NULL); 
	for (int k = 0;k < 10000;k++) //让主线程休眠
	{
		Sleep(10000000);
	}
	return 0;
}