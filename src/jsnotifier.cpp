#include "jsnotifier.h"


void JSNotifier::initFinished() {
    emit onInitFinished();
}


void JSNotifier::appendFinished() {
    emit onAppendFinished();
}


void JSNotifier::addToWhiteListRequested(const QString& url) {
    emit onAddToWhiteListRequested(url);
}
