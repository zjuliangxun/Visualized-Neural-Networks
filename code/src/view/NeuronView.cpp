#include "NeuronView.h"
#include "ui_NeuronView.h"

NeuronView::NeuronView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NeuronView)
{
    ui->setupUi(this);
    validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit->setValidator(validator);
}
NeuronView::~NeuronView()
{
    if (validator)
        delete validator;
}

void NeuronView::setValue(double value)
{
    ui->lineEdit->setText(QString::number(value));
}
double NeuronView::getValue()
{
    double value = ui->lineEdit->text().toDouble();
    return value;
}
