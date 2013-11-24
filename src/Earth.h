/** Earth
 *
 *
 */

#include "Prop.h"

#pragma once

class Earth : Prop
{
public:
	Earth(void);
	~Earth(void);

	virtual void update(void);

	const int earth = 0;
	const int clouds = 1;
	const int atmosphere = 2;
};

