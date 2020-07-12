#include "ConfigView.h"
#include "ui_ConfigView.h"


ConfigView::ConfigView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfigView)
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
ConfigView::~ConfigView()
{
    if (validator)
        delete validator;
}

void ConfigView::saveData()
{
    emit sendData(getValue());
    this->close();
}
void ConfigView::ignoreData()
{
    /*  */
    this->close();
}
void ConfigView::setValue(double value, QString func)
{
    ui->lineEdit->setText(QString::number(value));
    if (func == QString("L2")) {
        ui->comboBox->setCurrentIndex(0);
    }
    if (func == QString("L1")) {
        ui->comboBox->setCurrentIndex(1);
    }
}
QPair<double, QString> ConfigView::getValue()
{
    double value = ui->lineEdit->text().toDouble();
    QString func;
    if (ui->comboBox->currentIndex() == 0) {
        func = "L2";
    }
    if (ui->comboBox->currentIndex() == 1) {
        func = "L1";
    }
    QPair<double, QString> param(value, func);
    return param;
}
