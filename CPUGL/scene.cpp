#include "pch.h"
#include "scene.h"
#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"

bool depth_compare(Intersection a, Intersection b) {
	return a.ray_depth < b.ray_depth;
}

void Scene::rend() {
	int width = 500, height = 500;
	std::vector<Line> rays;
	camera.getRays(rays, width, height);

	//Vertex Shader
	std::vector<std::vector<Intersection> > inters;
	inters.resize(rays.size());
	int rayid = 0;
	for (auto ray : rays) {
		for (auto object : objects) {
			Intersection inter = object->get_intersection(ray);
			inter.transparent = object->transparent;
			//std::cout << inter.transparent << std::endl;
			inters[rayid].push_back(inter);
		}
		rayid++;
	}

	//Fragment Shader
	double ambient = 0.2;
	double diffuse = 0.6;
	double specular = 0.2;
	double phone_s = 2;
	std::vector<Color> colors;
	for (int i = 0; i < rays.size(); i++) {
		Color c;
		Color transparent_c(1, 1, 1);
		sort(inters[i].begin(), inters[i].end(), depth_compare);
		for (auto inter : inters[i]) {
			if (inter.ray_depth < 1e8) {
				//std::cout << inter.transparent << std::endl;
				if (inter.transparent == 1) {
					transparent_c = transparent_c * inter.col;
					//std::cout << "!" << std::endl;
					continue;
				}
				c = inter.col * ambient;
				for (auto light : lights) {
					// shadow
					Vector l_v = inter.o - light.o;
					Line ray = Line(light.o, l_v);
					double ray_depth = sqrt(l_v*l_v), min_ray_depth = 1e9;
					for (auto object : objects) {
						if (object->transparent == 1) continue;
						Intersection inter = object->get_intersection(ray);
						min_ray_depth = std::min(min_ray_depth, inter.ray_depth);
					}
					if (min_ray_depth + 1e-6 < ray_depth) {
						continue;
					}

					// phone light
					Color light_c = light.phone_shading(inter, rays[i], diffuse, specular, phone_s);
					c = c + light_c;
				}
				break;
			}
		}
		colors.push_back(c*transparent_c);
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