#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <QRectF>

/* Auxiliary Functions */
QRectF newQRectF(QPointF, int);
bool conflict(const QRectF lhs, const QRectF rhs, int radius = 16);
bool conflict(const QPointF p, const QRectF lhs, int radius = 16);
bool isinside(const QPointF p, const QRectF lhs, int radius = 16);

#endif
