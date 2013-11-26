/** Moon : Wrapper class for Earth model and related functions
 *
 * Contains meshes that make the Moon, indexes allowing easy access.
 * Functions related to the Earth will also be stored here
 */

#include "Prop.h"

#pragma once

class Moon : public Prop
{
public:
	Moon(void);
	~Moon(void);

	// Updated model
	virtual void update(void);

private:
	static const double mass;
	vec3 velocity;
};

