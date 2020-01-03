// CPUGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include "scene.h"

int main()
{
	Scene scene;
	scene.camera.o = Point(0, 0, 1);
	scene.camera.tri.o = Point(-1, 1, 0.5);
	scene.camera.tri.v1 = Vector(2, 0, 0);
	scene.camera.tri.v2 = Vector(0, -2, 0);
	SphereObject sphere;
	sphere.o = Point(0, 0, 0);
	sphere.r = 0.5;
	sphere.col = Color(0, 0, 1);
	scene.objects.push_back(&sphere);
	scene.rend();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
