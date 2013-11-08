#ifndef USERCONTROLS_H
#define USERCONTROLS_H

#include <render_framework\render_framework.h>

using namespace render_framework;

class UserControls
{
public:
	UserControls();
	void moveCamera(free_camera* cam, float deltaTime);
	void rotateCamera(free_camera* cam, float deltaTime);
};
#endif // USERCONTROLS_H