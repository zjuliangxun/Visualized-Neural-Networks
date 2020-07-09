#ifndef NETVIEW_H
#define NETVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class NetView; }
QT_END_NAMESPACE

class NetView : public QMainWindow
{
    Q_OBJECT

public:
    NetView(QWidget *parent = nullptr);
    ~NetView();

private:
    Ui::NetView *ui;
};
#endif // NETVIEW_H
