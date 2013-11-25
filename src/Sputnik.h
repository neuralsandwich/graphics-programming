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
	const int sphere  = 0;
	const int sputnik = 1;
	const int tarpine = 2;
	const int legs    = 3;

	Sputnik(void);
	~Sputnik(void);

		// Updated model
	virtual void update(void);
private:
	const double mass = 83.60e3;
	vec3 velocity;
};