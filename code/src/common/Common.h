#pragma once
#include<any>
#include<functional>

#include "./weights.h"
#include "./neurons.h"
#include "./Graph.h"

#define NOTIF_DRAW 10
#define NOTIF_CHANGE 11

using namespace std;

typedef std::function<bool(std::any&&)> Command;
typedef std::function<void(uint32_t)>  Notification;

class PropertyTrigger
{
public:
//	PropertyTrigger() noexcept;
//	PropertyTrigger(const PropertyTrigger&) = delete;
//	PropertyTrigger& operator=(const PropertyTrigger&) = delete;
//	~PropertyTrigger() noexcept;

	void ClearNotifications() noexcept;
	uintptr_t AddNotification(Notification&& pn);
	void RemoveNotification(uintptr_t uCookie) noexcept;

	void Fire(uint32_t uID);
	
private:
	std::vector<Notification> VecPN;
};


