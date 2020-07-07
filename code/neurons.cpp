#include "neurons.h"

int Neuron::_radius = 16;

bool Neuron::conflict(const Neuron &rhs)
{
	QPoint center = _shape.center();
	QPoint new_center = rhs._shape.center();
	int dx = new_center.x() - center.x();
	int dy = new_center.y() - center.y();
	return (dx * dx + dy * dy <= 4 * _radius * _radius);
}