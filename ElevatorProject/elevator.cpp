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
//��������˿͡������и���0���˿�
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
	if (!outfile)//�ж��ļ����Ƿ�ɹ�
	{
		cerr << "open outfile wrong!\n";
		exit(1);
	}
	while (!infile.eof()) {
		//����ÿ���˵�ʱ�䡢λ�á�����(�������Ϊ0�Ļ������丳ֵ10��
		for (int i = 1;i <= 5;i++)
		{
			infile >> man[i].time >> man[i].location >> man[i].direction;
			if (man[i].direction == 0)
				man[i].direction = 10;
			man[i].status = "offline";
		}
		//����0���˿͵��յ㸳ֵ1
		man[0].direction = 1;
		sum_time = 0;
		time_for_now = 0;
		location = 0;
		for (j = 1;;) {
			//����get��put
			in = 0;
			out = 0;
			//�ж��Ƿ�ʼ�ȴ�
			for (int i = 1;i <= 5;i++)
				if (time_for_now >= man[i].time&&man[i].status == "offline")
					man[i].status = "wait";
			//�ж��Ƿ�ӿ�
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
			//�ж��Ƿ��Ϳ�
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
					outfile << time_for_now << "ʱ��ͣ����" << man[index].direction << "¥��" << in << "λ����" << endl;
				else
				{
					num -= out;
					outfile << time_for_now << "ʱ��ͣ����" << man[index].direction << "¥��" << in << "λ����" << "����" << out << "λ����" << endl;
				}
			}
			else
				if (in == 0 && out != 0)
				{
					num -= out;
					outfile << time_for_now << "ʱ��ͣ����" << man[index].direction << "¥��" << out << "λ����" << endl;
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

			//����ѭ������
			if (man[1].status == "out"&&man[2].status == "out"&&man[3].status == "out"&&man[4].status == "out"&&man[5].status == "out")
			{
				outfile << "�˿͵ĵȴ�ʱ���ܺ�:" << sum_time << endl << endl;
				break;
			}
			//����˿͵ȴ���ʱ��
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