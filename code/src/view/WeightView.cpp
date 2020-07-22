#include "WeightView.h"
#include "ui_WeightView.h"

WeightView::WeightView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WeightView)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    validator = new QDoubleValidator(this);
    validator->setRange(-99.99, 99.99, 7);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit->setValidator(validator);


    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveData()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(ignoreData()));
}
WeightView::~WeightView()
{
    if (validator)
        delete validator;
}
void WeightView::saveData()
{
    emit sendData(getWeight());
    this->close();
}
void WeightView::ignoreData()
{
    this->close();
}
void WeightView::setWeight(double value)
{
    ui->lineEdit->setText(QString::number(value));
}
void WeightView::setID(int id)
{
    weight_id = id;
}
QPair<int, double> WeightView::getWeight()
{
    double weight = ui->lineEdit->text().toDouble();
    QPair<int, double> param(weight_id, weight);
    return param;
}
