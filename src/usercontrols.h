#ifndef USERCONTROLS_H
#define USERCONTROLS_H

#include <render_framework\render_framework.h>

using namespace render_framework;

class UserControls
{
public:
	void moveCamera(std::shared_ptr<arc_ball_camera> cam, float deltaTime);
};
#endif // USERCONTROLS_H