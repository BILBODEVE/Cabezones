#include "Colisionable.h"

bool Colisionable::isCollision(Colisionable& obj) const
{
	return getBounds().intersects(obj.getBounds());
}
