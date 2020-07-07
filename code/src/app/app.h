#ifndef APP_H
#define APP_H

#include <memory>
#include "view.h"
#include "model.h"
#include "viewmodel.h"

class APP {
private:
	std::shared_ptr<View> view;
	std::shared_ptr<Model> model;
	std::shared_ptr<ViewModel> viewmodel;
public:
	App();
	void run();
};

#endif // !APP_H
