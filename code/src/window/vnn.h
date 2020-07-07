#ifndef VNN_H
#define VNN_H


#include <QSharedPointer>
#include <QtWidgets/QMainWindow>
class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget* parent = Q_NULLPTR);
    ~Window();

private slots:

private:
    UI::Window* ui;


};
#endif // !VNN_H
