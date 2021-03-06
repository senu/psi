#include <QWebFrame>
#include <QMenu>
#include <QContextMenuEvent>

#include "eventview.h"
#include "iconserver.h"


EventView::EventView(QWidget* parent, IconServer* iconServer) : WebView(parent, iconServer) {

    connect(page(), SIGNAL(linkClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));

    connect(this, SIGNAL(loadFinished(bool)), this, SLOT(loadAndBindJS(bool)));
    connect(&jsNotifier, SIGNAL(onInitFinished()), this, SLOT(onInitDocumentFinished()));
    connect(&jsNotifier, SIGNAL(onAddToWhiteListRequested(const QString&)), SLOT(onAddToWhiteListRequested(const QString&)));
}


void EventView::displayText(const QString& xhtmlText) {

    eventBody = xhtmlText;

    QString xhtml("<html><body></body></html>");
    setHtml(xhtml);
}


QString EventView::getHtml() {
    return page()->mainFrame()->toHtml();
}


void EventView::onLinkClicked(const QUrl& url) {
    emit openURL(url.toString());
}


void EventView::loadAndBindJS(bool ok) {
    if (!ok) {
        qDebug() << "WARNING: EventView::onEmptyDocumentLoaded() - load failed"; //NOTE: see note in HTMLChatView.cpp
        return;
    }

    importJSChatFunctions();
    page()->mainFrame()->addToJavaScriptWindowObject("jsNotifier", &jsNotifier);
    evaluateJS("psi_initDocument(\"\", \"\")");
}


void EventView::onInitDocumentFinished() {
    evaluateJS("psi_appendNextMessage(\"%message%\", \"" + escapeStringCopy(eventBody) + "\"" + ")");

}
