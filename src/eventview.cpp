#include <QWebFrame>
#include "eventview.h"
#include "iconserver.h"


EventView::EventView(QWidget* parent, IconServer* iconServer) : QWebView(parent) {

    //security
    settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
    settings()->setAttribute(QWebSettings::JavaEnabled, false);
    settings()->setAttribute(QWebSettings::PluginsEnabled, false);

    networkManager = new NetworkAccessManager(0, iconServer);
    page()->setNetworkAccessManager(networkManager);

    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    setContextMenuPolicy(Qt::NoContextMenu);

    connect(page(), SIGNAL(linkClicked(const QUrl&)), this, SLOT(onLinkClicked(const QUrl&)));
}


void EventView::displayText(const QString& xhtmlText) {
    QString xhtml("<html><body style=\"background-color:green\">%1</body></html>"); //TODO 15 make it pretty
    setHtml(xhtml.arg(xhtmlText));
}


QString EventView::getHtml() {
    return page()->mainFrame()->toHtml();
}


void EventView::scrollToTop() {
    page()->mainFrame()->setScrollBarValue(Qt::Vertical, page()->mainFrame()->scrollBarMinimum(Qt::Vertical));
}


void EventView::onLinkClicked(const QUrl& url) {
    emit openURL(url.toString());
}