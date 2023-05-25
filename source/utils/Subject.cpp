#include "../../include/utils/Subject.h"
#include "../../include/utils/Observer.h"


void Subject::addObserver(Observer* ob ) {
    observer = ob;
}

void Subject::notify(const Entity& entity,Events event) {
    if (observer != nullptr) observer->onNotify(entity, event);
}
