#ifndef MODEL_H
#define MODEL_H

#include <QtWidgets>
#include <memory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QVector>
#include "../app/notification.h"
#include "../app/command.h"
#include "../common/weights.h"
#include "../common/neurons.h"

class Model {
private:
	QVector<Neuron> neurons;
	QVector<Weight> weights;
	std::shared_ptr<Notification> update_display_data_notification;

public:
	Model() {}
	void set_update_display_data_notification(std::shared_ptr<Notification> notification);
	QVector<Neuron>& get_neurons();
	QVector<Weight>& get_weights();
	void select();
	void add_none();
	void add_sigmoid();
	void add_relu();
	void add_tanh();
	void move(int);
};

#endif // !MODEL_H
