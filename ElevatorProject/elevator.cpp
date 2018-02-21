//unpredictable situation
//Second version
#include<iostream>
#include <fstream>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define mod (1e9+7)
#define ll long long
using namespace std;
int j, index, time_for_now = 0, num = 0, sum_time = 0, in = 0, out = 0, delta_path[5], delta_time[5], location = 1;
struct passengers {
	int time, location, direction;
	string status = "offline";
};
//创建五个乘客、假设有个第0个乘客
struct passengers man[7];
bool judge() {
	for (int i = 1;i <= 5;i++)
		if (man[i].status == "wait" || man[i].status == "in")
			return 1;
	return 0;
}
int main() {
	ifstream infile("input.txt");
	if (!infile)
	{
		cerr << "open infile wrong!\n";
		exit(1);
	}
	ofstream outfile("output.txt");
	if (!outfile)//判断文件打开是否成功
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
	while (!infile.eof()) {
		//输入每个人的时间、位置、方向(如果方向为0的话，将其赋值10）
		for (int i = 1;i <= 5;i++)
		{
			infile >> man[i].time >> man[i].location >> man[i].direction;
			if (man[i].direction == 0)
				man[i].direction = 10;
			man[i].status = "offline";
		}
		//给第0个乘客的终点赋值1
		man[0].direction = 1;
		sum_time = 0;
		time_for_now = 0;
		location = 0;
		for (j = 1;;) {
			//重置get和put
			in = 0;
			out = 0;
			//判断是否开始等待
			for (int i = 1;i <= 5;i++)
				if (time_for_now >= man[i].time&&man[i].status == "offline")
					man[i].status = "wait";
			//判断是否接客
			for (int z = 1;z <= 5 && time_for_now >= man[z].time;z++) {
				if (man[z].status == "in" || man[z].status == "out")
					continue;
				if (location == man[z].location)
				{
					man[z].status = "in";
					num++;
					in++;
				}
			}
			//判断是否送客
			for (int x = 1;x <= 5;x++)
				if (location == man[x].direction&&man[x].status == "in"&&time_for_now >= man[x].time)
				{
					out++;
					man[x].status = "out";
					index = x;
				}
			if (in != 0)
			{
				if (out == 0)
					outfile << time_for_now << "时，停靠在" << man[index].direction << "楼接" << in << "位客人" << endl;
				else
				{
					num -= out;
					outfile << time_for_now << "时，停靠在" << man[index].direction << "楼接" << in << "位客人" << "并送" << out << "位客人" << endl;
				}
			}
			else
				if (in == 0 && out != 0)
				{
					num -= out;
					outfile << time_for_now << "时，停靠在" << man[index].direction << "楼送" << out << "位客人" << endl;
				}
			if ((in + out) == 0 && judge())
				if (man[j].status == "wait")
				{
					if (man[j].location - location>0)
						location++;
					else
						location--;
				}
				else
				{
					if (man[j].direction - location>0)
						location++;
					else
						location--;
				}

			//设置循环结束
			if (man[1].status == "out"&&man[2].status == "out"&&man[3].status == "out"&&man[4].status == "out"&&man[5].status == "out")
			{
				outfile << "乘客的等待时间总和:" << sum_time << endl << endl;
				break;
			}
			//计算乘客等待总时间
			for (int i = 1;i <= 5;i++) {
				if (time_for_now >= man[i].time  && man[i].status != "out")
					sum_time++;
			}
			time_for_now++;
			j += out;
		}
		continue;
	}
	return 0;
}