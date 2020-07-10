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
double distance(const QPointF a, const QPointF b)
{
    qreal dx = a.x() - b.x();
    qreal dy = a.y() - b.y();
    return qSqrt(dx * dx + dy * dy);
}
double dist_to_line(const QPointF a, const QLineF l)
{
    QPointF p, p1, p2;
    p = a, p1 = l.p1(), p2 = l.p2();
    double cross = (p2.x() - p1.x()) * (p.x() - p1.x())
                    + (p2.y() - p1.y()) * (p.y() - p1.y());
    if (cross <= 0)
        return distance(p, p1);

    double d2 = distance(p1, p2) * distance(p1, p2);
    if (cross >= d2)
        return distance(p, p2);

    double r = cross / d2;
    double px = p1.x() + (p2.x() - p1.x()) * r;
    double py = p1.y() + (p2.y() - p1.y()) * r;
    return distance(p, QPointF(px, py));
}
bool nearline(const QPointF p, const QLineF lhs, double delta)
{
    return dist_to_line(p, lhs) < delta;
}
