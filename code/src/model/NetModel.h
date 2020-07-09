#ifndef MODEL_H
#define MODEL_H

#include <QtWidgets/QtWidgets>
#include <memory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtCore/QVector>
#include "../common/Common.h"

class NetModel :public PropertyTrigger{
private:
	//QVector<Neuron> neurons;
	//QVector<Weight> weights;
    Graph FNN;
public:
	//expose
    std::shared_ptr<Graph> get_FNN();
    //return commands
    std::function<bool(Neuron&&)> get_add_neuron_command();
//	Command get_connect_command();

	//get notifications-----through AddNotifications
	void set_update_display_data_notification(Notification&& notification);
	
	//commands' core
    bool add_neuron(Neuron&&);
//	void move(int);
};

#endif // !MODEL_H
