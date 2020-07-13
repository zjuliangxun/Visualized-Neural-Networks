#pragma once

#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H


#include <QWidget>
#include "ui_About.h"

QT_BEGIN_NAMESPACE
namespace Ui { class About; }
QT_END_NAMESPACE

class About : public QWidget {
    Q_OBJECT

public:
    explicit About(QWidget* parent = nullptr);
    ~About();

private:
    Ui::About *ui;
};


#endif // ABOUTVIEW_H
