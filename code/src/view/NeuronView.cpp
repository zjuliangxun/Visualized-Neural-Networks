#include "NeuronView.h"
#include "ui_NeuronView.h"

NeuronView::NeuronView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NeuronView)
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
NeuronView::~NeuronView()
{
    if (validator)
        delete validator;
}

void NeuronView::saveData()
{
    emit sendData(getData());
    this->close();
}
void NeuronView::ignoreData()
{
    /*  */
    this->close();
}
void NeuronView::setValue(double value, NeuronType t)
{
    ui->lineEdit->setText(QString::number(value));
    if (t != nTarget)
        ui->comboBox->setCurrentIndex(t);
    else
        ui->comboBox->setDisabled(true);
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
NeuronType NeuronView::getType()
{
    int id = ui->comboBox->currentIndex();
    NeuronType t = nNone;
    switch (id) {
    case 1:
        t = nSigmoid;
        break;
    case 2:
        t = nRelu;
        break;
    case 3:
        t = nTanh;
        break;
    default:
        t = nNone;
        break;
    }
    return t;
}
QPair<QPair<int, double>, NeuronType> NeuronView::getData()
{
    QPair<QPair<int, double>, NeuronType> data(getValue(), getType());
    return data;
}
