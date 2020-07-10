#include "utils.h"

QRectF newQRectF(QPointF center, int radius)
{
    QPointF upper_left(center), lower_right(center);
    upper_left.setX(upper_left.x() - radius);
    upper_left.setY(upper_left.y() - radius);
    lower_right.setX(lower_right.x() + radius);
    lower_right.setY(lower_right.y() + radius);
    return QRectF(upper_left, lower_right);
}
bool conflict(const QRectF lhs, const QRectF rhs, double radius)
{
    QPointF center = lhs.center();
    QPointF new_center = rhs.center();
    double dx = new_center.x() - center.x();
    double dy = new_center.y() - center.y();
    return (dx * dx + dy * dy <= 4 * radius * radius);
}
bool conflict(const QPointF p, const QRectF lhs, double radius)
{
    QPointF center = lhs.center();
    double dx = p.x() - center.x();
    double dy = p.y() - center.y();
    return (dx * dx + dy * dy <= 4 * radius * radius);
}
bool isinside(const QPointF p, const QRectF lhs, double radius)
{
    QPointF center = lhs.center();
    double dx = p.x() - center.x();
    double dy = p.y() - center.y();
    return (dx * dx + dy * dy <= radius * radius);
}

