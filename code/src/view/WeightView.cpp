#include "WeightView.h"
#include "ui_WeightView.h"

WeightView::WeightView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WeightView)
{
    ui->setupUi(this);
    validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit->setValidator(validator);
}
WeightView::~WeightView()
{
    if (validator)
        delete validator;
}

void WeightView::setWeight(double value)
{
    ui->lineEdit->setText(QString::number(value));
}
double WeightView::getWeight()
{
    double value = ui->lineEdit->text().toDouble();
    return value;
}
