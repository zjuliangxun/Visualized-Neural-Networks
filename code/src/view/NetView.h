#pragma once

#ifndef NETVIEW_H
#define NETVIEW_H

#include <memory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QVector>
#include <QGraphicsItem>
#include"../viewmodel/NetViewModel.h"
#include "../common/Common.h"

enum EditMode {
	selectNeuron, addNeuron, addWeight
};
enum DragMode {
    noDrag, preDrag, canDrag
};

QT_BEGIN_NAMESPACE
namespace Ui { class NetView; }
QT_END_NAMESPACE


class NetView : public QMainWindow {
	Q_OBJECT 
public:
    explicit NetView(QWidget* parent = nullptr);
    ~NetView();
	

    //BIND COMMANDS
    void set_add_neuron_command(Command&&);
//	void set_connect_command(Command&&);

	//ATTACH DATA AND MODELS
    void set_FNN(std::shared_ptr<Graph>);
	void attach_ViewModel(std::shared_ptr<NetViewModel> refModel) noexcept;
	std::shared_ptr <NetViewModel > detach_ViewModel() noexcept;

	//retrun NOTIFICATION(IMPLEMENTED BY VIEW)
	Notification tell_update_view_notification();

private slots:
	void select_button_clicked();
	void neuron_button_clicked();
	void sigmoid_button_clicked();
	void relu_button_clicked();
	void tanh_button_clicked();
	void target_button_clicked();

private:
	/*Ui::View *ui;*/
	//MODELS AND DATA BIND
	std::shared_ptr<Graph> FNN;
	std::shared_ptr<NetViewModel> m_NetVM;

    //COMMANDS
    Command add_neuron_command;
//	Command connect_command;

	// edit state
	EditMode edit_mode;
    DragMode drag_mode;
    Neuron current_neuron;
    QVector<bool> selected_neurons;
    int selected_neuron;

	// shape of the Graph
    QVector<QRect> shape_neurons;
    QRect shape_current_neuron;
    //QVector<QGraphicsEllipseItem> shape_neurons;
    //QGraphicsEllipseItem shape_current_neuron;
    /*QVector<> shape_Weights*/

    Ui::NetView *ui;

protected:
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
//    void mouseDoubleClickEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void paintEvent(QPaintEvent*);

};


#endif // !VIEW_H
