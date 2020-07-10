#include "Common.h"
uintptr_t PropertyTrigger::AddNotification(Notification&& pn) {
    VecPN.push_back(std::move(pn));
    return 1;
}

void PropertyTrigger::ClearNotifications() noexcept {
    VecPN.clear();
}

void PropertyTrigger::RemoveNotification(uintptr_t uCookie) noexcept {
    VecPN.clear();//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}

void PropertyTrigger::Fire(uint32_t i) {
    for (auto j : VecPN) {
        (j)(i);
    }
}
