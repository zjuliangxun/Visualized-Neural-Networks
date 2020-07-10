#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <QRectF>
#include <cmath>

/* Auxiliary Functions */
QRectF newQRectF(QPointF, int);
bool conflict(const QRectF lhs, const QRectF rhs, double radius = 24);
bool conflict(const QPointF p, const QRectF lhs, double radius = 24);
bool isinside(const QPointF p, const QRectF lhs, double radius = 24);
bool nearline(const QPointF p, const QLineF lhs, double delta = 2);

#endif
