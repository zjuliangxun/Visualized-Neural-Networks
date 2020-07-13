#include "TutorialView.h"

Tutorial::Tutorial(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tutorial)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}
Tutorial::~Tutorial()
{
}
