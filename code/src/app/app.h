#ifndef APP_H
#define APP_H

#include <memory>
#include "../view/NetView.h"
#include "../model/NetModel.h"
#include "../viewmodel/NetViewModel.h"

class App {
private:
	//must not be pointers
	NetView view;
	NetModel model;
	NetViewModel viewmodel;
public:
	App();
	void run();
};

#endif // !APP_H
