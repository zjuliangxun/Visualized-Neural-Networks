#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <QRectF>

/* Auxiliary Functions */
QRectF newQRectF(QPointF, int);
bool conflict(const QRectF lhs, const QRectF rhs, double radius = 24);
bool conflict(const QPointF p, const QRectF lhs, double radius = 24);
bool isinside(const QPointF p, const QRectF lhs, double radius = 24);

#endif
