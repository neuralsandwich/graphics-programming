/** Sol : Wrapper class for Earth Sol and related functions
 *
 * Contains meshes that make the Sol, indexes allowing easy access.
 * Functions related to the Sol will also be stored here
 */

#include "Prop.h"

#pragma once

class Sol : public Prop
{
public:
	Sol(void);
	~Sol(void);

	// Update model
	virtual void update(void);
	// Update sun rotation
	void rotate(void);

private:
	static const double mass;
	vec3 velocity;
};

