#include "pch.h"
#include "scene.h"
#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"

void Scene::rend() {
	int width = 500, height = 500;
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
	double ambient = 0.2;
	double diffuse = 0.6;
	double specular = 0.2;
	double phone_s = 2;
	std::vector<Color> colors;
	for (int i = 0; i < rays.size(); i++) {
		Color c;
		if (inters[i].ray_depth < 1e8) {
			c = inters[i].col * ambient;
			for (auto light : lights) {
				// shadow
				Vector l_v = inters[i].o - light.o;
				Line ray = Line(light.o, l_v);
				double ray_depth = sqrt(l_v*l_v), min_ray_depth = 1e9;
				for (auto object : objects) {
					Intersection inter = object->get_intersection(ray);
					min_ray_depth = std::min(min_ray_depth, inter.ray_depth);
				}
				if (min_ray_depth + 1e-6 < ray_depth) {
					continue;
				}

				// phone light
				Color light_c = light.phone_shading(inters[i], rays[i], diffuse, specular, phone_s);
				c = c + light_c;
			}
		}
		colors.push_back(c);
	}

	//Show
	cv::Mat debug_show(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
	int ind = 0;
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
			debug_show.at<cv::Vec3b>(r, c)[2] = std::min(255.0, colors[ind].r * 255);
			debug_show.at<cv::Vec3b>(r, c)[1] = std::min(255.0, colors[ind].g * 255);
			debug_show.at<cv::Vec3b>(r, c)[0] = std::min(255.0, colors[ind].b * 255);
			ind++;
		}
	}
	cv::imshow("debug", debug_show);
	cv::waitKey();
}