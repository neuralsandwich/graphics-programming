/** Sputnik : Wrapper class for Sputnik model and related functions
 *
 * Contains meshes that make Sputnik, indexes allowing easy access.
 * Functions related to the Sputnik will also be stored here
 */

#include "Prop.h"

#pragma once

class Sputnik : public Prop
{
public:
	static const int sphere  = 0;
	static const int sputnik = 1;
	static const int tarpine = 2;
	static const int legs    = 3;

	Sputnik(void);
	Sputnik(mesh models);
	~Sputnik(void);

		// Updated model
	virtual void update(void);

private:
	static const double mass;
	vec3 velocity;
};