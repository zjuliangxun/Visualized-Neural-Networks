#ifndef APP_H
#define APP_H

#include <memory>
#include "../view/NetView.h"
#include "../model/NetModel.h"
#include "../viewmodel/NetViewModel.h"

class App {
private:
	//must not be pointers
    shared_ptr<NetView> view;
    shared_ptr<NetModel> model;
    shared_ptr<NetViewModel> viewmodel;
public:
	App();
    ~App();
	void run();
};

#endif // !APP_H
