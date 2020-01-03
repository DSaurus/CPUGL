#include "pch.h"
#include "scene.h"

void Scene::rend() {
	std::vector<Line> rays;
	camera.getRays(rays);

	//Vertex Shader
	std::vector<Intersection> inters;
	for (auto ray : rays) {
		Intersection ray_inter;
		for (auto object : objects) {
			Intersection inter = object.get_intersection(ray);
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
		for (auto light : lights) {
			Color light_c = light.shading(inters[i], rays[i]);
			c = c + light_c;
		}
		colors.push_back(c);
	}
}