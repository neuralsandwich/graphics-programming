/** Sputnik : Wrapper class for Sputnik model and related functions
 *
 * Contains meshes that make Sputnik, indexes allowing easy access.
 * Functions related to the Sputnik will also be stored here
 */

#include "Prop.h"

#pragma once

class Sputnik : Prop
{
public:
	Sputnik(void);
	~Sputnik(void);

		// Updated model
	virtual void update(void);
private:
	const double mass = 83.60e3;
	vec3 velocity;
};