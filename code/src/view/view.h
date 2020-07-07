#pragma once

#ifndef VIEW_H
#define VIEW_H

#include <QtWidgets>
#include <memory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QVector>
#include "../app/notification.h"
#include "../app/command.h"
#include "../common/weights.h"
#include "../common/neurons.h"

class View : public QMainWindow {
	Q_OBJECT 
public:
	explicit View(QWidget* parent = 0);
	
	void update();
	void set_neurons(std::shared_ptr<QVector<Neuron> > neurons);
	void set_weights(std::shared_ptr<QVector<Weight> > weights);
	void set_select_command(std::shared_ptr<Command>);
	void set_add_none_command(std::shared_ptr<Command>);
	void set_add_sigmoid_command(std::shared_ptr<Command>);
	void set_add_relu_command(std::shared_ptr<Command>);
	void set_add_tanh_command(std::shared_ptr<Command>);
	void set_drag_command(std::shared_ptr<Command>);
	void set_connect_command(std::shared_ptr<Command>);
	std::shared_ptr<Notification> get_update_view_notification;

private slots:
	void select_button_clicked();
	void neuron_button_clicked();
	void sigmoid_button_clicked();
	void relu_button_clicked();
	void tanh_button_clicked();
	void board_clicked();

private:
	Ui::View *ui;
	std::shared_ptr<QVector<Neuron> > neurons;
	std::shared_ptr<QVector<Weight> > weights;
	std::shared_ptr<Command> select_command;
	std::shared_ptr<Command> add_none_command;
	std::shared_ptr<Command> add_sigmoid_command;
	std::shared_ptr<Command> add_relu_command;
	std::shared_ptr<Command> add_tanh_command;
	std::shared_ptr<Command> drag_command;
	std::shared_ptr<Command> connect_command;

	std::shared_ptr<Notification> update_view_notification;

};

#endif // !VIEW_H
