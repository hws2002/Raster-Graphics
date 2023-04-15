#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "scene_parser.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "group.hpp"
#include "light.hpp"

#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3) {
        cout << "Usage: ./bin/PA1 <input scene file> <output bmp file>" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2];  // only bmp is allowed.

    // TODO: Main RayCasting Logic
    // First, parse the scene using SceneParser.
    SceneParser sceneparser = SceneParser(inputFile.c_str());
    Camera* camera = sceneparser.getCamera();
    Image image = Image(camera->getWidth(), camera->getHeight());
    // Then loop over each pixel in the image, shooting a ray
    for (int x = 0; x < camera->getWidth(); x++) {
        for (int y = 0; y < camera->getHeight(); y++) {
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.
            Ray camRay = camera->generateRay(Vector2f(x, y));
            Group * baseGroup = sceneparser.getGroup();
            Hit hit;
            bool isIntersect = baseGroup->intersect(camRay, hit, 0);
            if (isIntersect) {// hit
                //TODO: calculate the color
                Vector3f finalColor = Vector3f::ZERO;
                for (int i = 0; i < sceneparser.getNumLights(); i++) {
                    Light *light = sceneparser.getLight(i);
                    Vector3f lightDir = light->getDirection(hit.getIntersectionPoint());
                    Vector3f lightColor = light->getColor();
                    Vector3f normal = hit.getNormal();
                    Vector3f lightIntensity = lightColor * max(0.0f, Vector3f::dot(normal, lightDir));
                    finalColor += lightIntensity;
                }
                cout << "hit" << endl;
            } else {
                // no hit
                image.SetPixel(x,y,sceneparser.getBackgroundColor());
            }
        }
    }
    cout << "--------------------------------------Hello! Computer Graphics!---------------------------------------" << endl;
    return 0;
}

