#include "pch.h"
#include "scene.h"
#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"

void Scene::rend() {
	int width = 200, height = 200;
	std::vector<Line> rays;
	camera.getRays(rays, width, height);

	//Vertex Shader
	std::vector<Intersection> inters;
	for (auto ray : rays) {
		Intersection ray_inter;
		for (auto object : objects) {
			Intersection inter = object->get_intersection(ray);
			if (inter.ray_depth < ray_inter.ray_depth) {
				ray_inter = inter;
			}
		}
		inters.push_back(ray_inter);
	}

	//Fragment Shader
	std::vector<Color> colors;
	for (int i = 0; i < rays.size(); i++) {
		Color c;
		if (inters[i].ray_depth < 1e8) {
			for (auto light : lights) {
				Color light_c = light.shading(inters[i], rays[i]);
				c = c + light_c;
			}
			c = Color(0, 0, 1);
		}
		colors.push_back(c);
	}

	//Show
	cv::Mat debug_show(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
	int ind = 0;
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			debug_show.at<cv::Vec3b>(r, c)[2] = colors[ind].r*250;
			debug_show.at<cv::Vec3b>(r, c)[1] = colors[ind].g * 250;
			debug_show.at<cv::Vec3b>(r, c)[0] = colors[ind].b * 250;
			ind++;
		}
	}
	cv::imshow("debug", debug_show);
	cv::waitKey();
}