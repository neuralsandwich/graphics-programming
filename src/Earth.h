/** Earth : Wrapper class for Earth model and related functions
 *
 * Contains meshes that make the Earth, indexes allowing easy access.
 * Functions related to the Earth will also be stored here
 */

#include "Prop.h"

#pragma once

class Earth : public Prop
{
public:
	// Read only variables
	static const int earth = 0;
	static const int clouds = 1;
	static const int atmosphere = 2;

	// Constructor
	Earth(void);
	// Destructor
	~Earth(void);

	// Updated model
	virtual void update(void);
	// Update Clouds
	void update_clouds(void);
private:
	static const double mass;
	vec3 velocity;
};

