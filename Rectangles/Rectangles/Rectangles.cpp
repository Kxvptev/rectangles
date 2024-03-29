#include "pch.h"
#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fin;
	fin.open("rect.in");
	ofstream fout;
	fout.open("rect.out");

	long long oxSize;
	long long oySize;
	int num;

	fin >> oxSize >> oySize >> num;

	deque <pair <long long, bool>> rectangles;

	long long x1, x2, y1, y2;
	double targetX, targetY;

	for (int i = 0; i < num; ++i)
	{
		fin >> x1 >> y2 >> x2 >> y1;

		if (x1 == 0 && y2 == 0)
		{
			rectangles.push_back(make_pair(0, 0));
			rectangles.push_back(make_pair(oxSize + oySize, 1));
		}

		else
		{
			if (x2 == 0)
			{
				targetX = 0;
				targetY = oySize;
			}
			else if (y2 == 0)
			{
				targetX = oxSize;
				targetY = 0;
			}
			else
			{
				targetX = oxSize;
				targetY = (double)(y2 * targetX / x2);

				if (targetY - floor(targetY) != 0)
					targetY = ceil(targetY);

				if (targetY > oySize)
				{
					targetY = oySize;
					targetX = (double)(x2 * targetY / y2);

					if (targetX - floor(targetX) != 0)
						targetX = floor(targetX);
				}
			}

			long long left, right;

			left = targetY;
			if (targetY == oySize)
				left += oxSize - targetX;

			targetX = oxSize;

			if (x1 == 0) 
			{
				targetX = 0;
				targetY = oySize;
			}
			else if (y1 == 0) 
			{
				targetX = oxSize;
				targetY = 0;
			}
			else
			{
				targetY = (double)(y1 * targetX / x1);

				if (targetY - floor(targetY) != 0)
					targetY = floor(targetY);

				if (targetY > oySize)
				{
					targetY = oySize;
					targetX = (double)(x1 * targetY / y1);

					if (targetX - floor(targetX) != 0)
						targetX = ceil(targetX);
				}
			}

			right = targetY;

			if (targetY == oySize)
				right += oxSize - targetX;
			
			if (left <= right && left <= oxSize + oySize)
			{
				rectangles.push_back(make_pair(left, 0));
				rectangles.push_back(make_pair(right, 1));
			}
		}

	}

	sort(rectangles.begin(), rectangles.end());

	int interseptions = 0;
	int tempIntersept = 0;
	long long B;

	auto iter = rectangles.begin();
	
	while (iter != rectangles.end())
	{
		long long tempB = (*iter).first;

		while (iter != rectangles.end() && (*iter).first == tempB && (*iter).second == 0)
		{
			tempIntersept++;
			iter++;
		}

		if (tempIntersept >= interseptions) 
		{
			B = tempB;
			interseptions = tempIntersept;
		}

		while (iter != rectangles.end() && (*iter).first == tempB && (*iter).second == 1)
		{
			tempIntersept--;
			iter++;
		}
	}

	if (interseptions == 0) 
		fout << interseptions << " " << oxSize << " " << oySize << "\n";
	else if (B <= oySize)
		fout << interseptions << " " << oxSize << " " << B << "\n";
	else
		fout << interseptions << " " << oxSize + oySize - B << " " << oySize << "\n";


	fin.close();
	fout.close();

	return 0;
}