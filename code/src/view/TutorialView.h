#pragma once

#ifndef TUTORIALVIEW_H
#define TUTORIALVIEW_H

#include <QWidget>
#include "ui_Tutorial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Tutorial; }
QT_END_NAMESPACE

class Tutorial : public QWidget {
    Q_OBJECT

public:
    explicit Tutorial(QWidget* parent = nullptr);
    ~Tutorial();

private:
    Ui::Tutorial *ui;
};

#endif // TUTORIALVIEW_H
