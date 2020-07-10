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
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return sqrt(dx * dx + dy * dy);
}
double cmult(const QPointF a, const QPointF b, const QPointF c)
{
    return (b.x() - a.x()) * (c.y() - a.y())
            - (c.x() - a.x()) * (b.y() - a.y());
}
double pmult(const QPointF a, const QPointF b)
{
    return a.x() * b.x() + a.y() * b.y();
}
int sign(double x)
{
    if (fabs(x) < 1e-5)
        return 0;
    return x > 0 ? 1 : -1;
}
double dist_to_line(const QPointF a, const QLineF l)
{
    QPointF s1, s2, s3;
    s1.setX(l.p2().x() - l.p1().x());
    s1.setY(l.p2().y() - l.p1().y());

    s2.setX(a.x() - l.p1().x());
    s2.setY(a.y() - l.p1().y());

    s2.setX(a.x() - l.p2().x());
    s2.setY(a.y() - l.p2().y());

    if (l.p1().x() == l.p2().x() && l.p1().y() == l.p2().y())
        return distance(a, l.p1());
    if (sign(pmult(s1, s2)) < 0)
        return distance(a, l.p1());
    else if (sign(pmult(s1, s3)) > 0)
        return distance(a, l.p2());
    else
        return fabs(cmult(l.p1(), a, l.p2()) / distance(l.p1(), l.p2()));
}
bool nearline(const QPointF p, const QLineF lhs, double delta)
{
    return dist_to_line(p, lhs) < delta;
}
