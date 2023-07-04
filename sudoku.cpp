#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <time.h>
#include <cmath>

#include "tool.h"

using namespace std;

int result[100000000];	   // 用于存放指向存放终局数据数组的指针
short solve_map[9][9];	   // 用于存放求唯一解每格可填数字

class sudo
{
private:
	int sudo_map[9][9];
	int count; // 目前终局数
	int num;   // 要求终局数
	int hole;  // 挖空数

public:
	sudo(){};
	sudo(int n)
	{
		count = 0;
		num = n;
	}
	void creat_End();
	void write_to_file(string filename, int sudo[9][9]);
	void create_Que(int count, int que_num, int hole, int unique);
	int FindSole(int i, int j);
};

void sudo::creat_End()
{
	int first_line[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // 数独模型第一行初始值
	int row[8] = {1, 2, 3, 4, 5, 6, 7, 8};			 // 进行行变化对应行的下标
	for (int i = 0; i < 9; i++)
	{
		srand(time(NULL));
		int row=rand()%9;
		int col=rand()%9;
		swap(first_line[row],first_line[col]);
	}
	
	int arr_change[8] = {3, 6, 1, 4, 7, 2, 5, 8};	 // 由第一行的数分别向左移动 3、6、1、4、7、2、5、8 可以得到一个完整的数独终局
	do
	{
		for (int k = 0; k < 9; k++) // 为第一行赋值
			this->sudo_map[0][k] = first_line[k];
		// 根据map的关系和第一行的某个排列生成其他行，得到一个数独终局的模板
		for (int i = 1; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
				this->sudo_map[i][j] = first_line[(arr_change[i - 1] + j) % 9]; // 分别将first_line进行不同程度移位后的行赋给后续的行
		}
		do
		{
			do
			{
				do
				{
					// 将产生的矩阵存入result数组中
					for (int k = 0; k < 9; k++)
						result[k + 81 * this->count] = first_line[k]; // 存第一行数据
					for (int i = 1; i < 9; i++)
						for (int j = 0; j < 9; j++)
							result[i * 9 + j + 81 * this->count] = this->sudo_map[row[i - 1]][j]; // 将数独终局存入一个一维数组中,便于输出
					this->count++;
					if (this->count == this->num) // 终局数达到要求了
						return;
				} while (Perm(row + 5, row + 7));	// 对第7、8、9行进行排列
			} while (Perm(row + 2, row + 4));		// 对第4、5、6行进行排列
		} while (Perm(row, row + 1));				// 对第2、3行进行排列
	} while (Perm(first_line + 1, first_line + 8)); // 每对第一行的后8位进行排列后便据此生成一个新的数独终局模板
	return;
}

// count为数独游戏数目 que_num为终局序号 hole为挖空数目 unique为是否唯一解
void sudo::create_Que(int count, int que_num, int hole, int unique)
{
	for (int n = 0; n < count; n++)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				solve_map[i][j] = pow(2,result[i * 9 + j + que_num]-1);
			}
		}
		srand(time(NULL));
		int nums = hole;
		while (nums)
		{
			int row = rand() % 9;
			int col = rand() % 9;
			if (solve_map[row][col] != 0)
			{
				solve_map[row][col] = 0;
				nums--;
			}
		}
		if (unique)
			for (int i = 0; i < 9; i++)
			{
				int tmp = n;
				for (int j = 0; j < 9; j++)
				{
					n--;
					if (FindSole(i, j) != 1)
						break;
					n++;
				}
				if(n!=tmp)
					break;
			}
		write_to_file("sudo_que.txt",sudo_map);
	}

}

void sudo::write_to_file(string filename, int sudo[9][9])
{
	ofstream fp;
	fp.open(filename, ios::app);
	if (!fp)
	{
		cout << "打开文件失败" << endl;
		return;
	}
	for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (sudo[i][j] != 0)
						fp<<sudo[i][j];
					else
						fp<<' ';
					fp<<' ';
				}
				fp<<endl;
			}
	cout << "ok" << endl;
}

int sudo::FindSole(int i, int j)
{
	short sum, sum_row, sum_col, sum_squ; // 行、列、宫
	if (CountOneBit(solve_map[i][j]) > 1) // 排除已填的空
	{
		sum_squ = 0;
		for (int i0 = i / 3 * 3; i0 < i / 3 * 3 + 3; i0++) // 遍历小九宫，找出已有数
			for (int j0 = j / 3 * 3; j0 < j / 3 * 3 + 3; j0++)
				if (CountOneBit(solve_map[i0][j0]) == 1)
					sum_squ += solve_map[i0][j0]; // 宫中不可能数集合
		sum_row = 0;
		for (int j0 = 0; j0 < 9; j0++) // 遍历行，找出已有数
			if (CountOneBit(solve_map[i][j0]) == 1)
				sum_row += solve_map[i][j0]; // 行不可能数集合
		sum_col = 0;
		for (int i0 = 0; i0 < 9; i0++) // 遍历列，找出已有数
			if (CountOneBit(solve_map[i0][j]) == 1)
				sum_col += solve_map[i0][j]; // 列不可能数集合
		sum = sum_squ | sum_row | sum_col;	 // 行、列、宫不可能数并集
		solve_map[i][j] &= ~sum;			 // 从n中排除不可能数,原理：&1不变，&0变成0
		return solve_map[i][j];
	}
	return 0; // 该空有已知数，退出
}

int main(){
	
}
