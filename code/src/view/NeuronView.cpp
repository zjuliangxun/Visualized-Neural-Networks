#include "NeuronView.h"
#include "ui_NeuronView.h"

NeuronView::NeuronView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NeuronView)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    validator = new QDoubleValidator(this);
    validator->setRange(-99.99, 99.99);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit->setValidator(validator);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(saveData()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(ignoreData()));
}
NeuronView::~NeuronView()
{
    if (validator)
        delete validator;
}

void NeuronView::saveData()
{
    emit sendData(getValue());
    this->close();
}
void NeuronView::ignoreData()
{
    /*  */
    this->close();
}
void NeuronView::setValue(double value)
{
    ui->lineEdit->setText(QString::number(value));
}
void NeuronView::setID(int id)
{
    neuron_id = id;
}
QPair<int, double> NeuronView::getValue()
{
    double value = ui->lineEdit->text().toDouble();
    QPair<int, double> param(neuron_id, value);
    return param;
}
