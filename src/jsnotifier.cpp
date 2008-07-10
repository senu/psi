#include "jsnotifier.h"


void JSNotifier::initFinished() {
	emit onInitFinished();
}

void JSNotifier::appendFinished() {
	emit onAppendFinished();
}
