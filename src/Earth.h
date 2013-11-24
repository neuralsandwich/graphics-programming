/** Earth : Wrapper class for Earth model and related functions
 *
 * Contains meshes that make the Earth, indexes allowing easy access.
 * Functions related to the Earth will also be stored here
 */

#include "Prop.h"

#pragma once

class Earth : Prop
{
public:
	// Read only variables
	const int earth = 0;
	const int clouds = 1;
	const int atmosphere = 2;

	// Constructor
	Earth(void);
	// Destructor
	~Earth(void);

	// Updated model
	virtual void update(void);
	// Update Clouds
	void update_clouds(void);
private:
	const double mass = 5.9721986e24;
	vec3 velocity;
};

