#ifndef NETVIEWMODEL_H
#define NETVIEWMODEL_H

#include <QtWidgets/QtWidgets>
#include <memory>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtCore/QVector>
#include "../common/Common.h"
#include"../model/NetModel.h"

class NetViewModel:public PropertyTrigger {
private:
    std::shared_ptr<NetModel> m_NetM;

public:
    NetViewModel();

    //GET COMANDS
    Command get_add_neuron_command();
    Command get_connect_command();

	//EXPOSE ATTR
    std::shared_ptr<Graph> get_FNN();

	//SEND NOTIFICATIONS TO MODEL
	Notification get_Notification();

	//ATTACH  MODEL
    void attach_Model(std::shared_ptr<NetModel> refModel) noexcept;
    std::shared_ptr<NetModel> detach_Model() noexcept;

    //void notified();Fire()
};


#endif // !NETVIEWMODEL_H
