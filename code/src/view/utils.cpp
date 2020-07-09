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
bool conflict(const QRectF lhs, const QRectF rhs, int radius)
{
    QPointF center = lhs.center();
    QPointF new_center = rhs.center();
    int dx = new_center.x() - center.x();
    int dy = new_center.y() - center.y();
    return (dx * dx + dy * dy <= 4 * radius * radius);
}
bool conflict(const QPointF p, const QRectF lhs, int radius)
{
    QPointF center = lhs.center();
    int dx = p.x() - center.x();
    int dy = p.y() - center.y();
    return (dx * dx + dy * dy <= 4 * radius * radius);
}
bool isinside(const QPointF p, const QRectF lhs, int radius)
{
    QPointF center = lhs.center();
    int dx = p.x() - center.x();
    int dy = p.y() - center.y();
    return (dx * dx + dy * dy <= radius * radius);
}

