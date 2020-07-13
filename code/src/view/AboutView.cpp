#include "AboutView.h"

About::About(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::About)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}
About::~About()
{
}
