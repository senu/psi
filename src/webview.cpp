#include "webview.h"
#include <QWebFrame>
#include <QFile>
#include <QDebug>


WebView::WebView(QWidget* parent, IconServer* iconServer) : QWebView(parent) {

    settings()->setAttribute(QWebSettings::JavaEnabled, false);
    settings()->setAttribute(QWebSettings::PluginsEnabled, false);

    networkManager = new NetworkAccessManager(this, iconServer);

    page()->setNetworkAccessManager(networkManager);
    page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    //actions
    copyAction = page()->action(QWebPage::Copy);
    copyLinkAction = page()->action(QWebPage::CopyLinkToClipboard);
}


void WebView::scrollToBottom() {
    page()->mainFrame()->setScrollBarValue(
                                           Qt::Vertical,
                                           page()->mainFrame()->scrollBarMaximum(Qt::Vertical));
}


void WebView::scrollToTop() {
    page()->mainFrame()->setScrollBarValue(Qt::Vertical, 0);
}


void WebView::onAddToWhiteListRequested(const QString& url) {

    QMessageBox::StandardButton btn =
        QMessageBox::information(this, tr("Warning"),
                                 tr("Are you sure you want to add %1 to whiteList?").arg(url),
                                 QMessageBox::Yes | QMessageBox::No);

    if (btn == QMessageBox::Yes) {
        networkManager->addUrlToWhiteList(url);
        evaluateJS("psi_unban('" + escapeStringCopy(url) + "')");
    }
}


void WebView::contextMenuEvent(QContextMenuEvent* event) {

    QList<QAction*> actions;
    bool haveActions = false; //does context menu have appended actions?

    if (copyAction->isEnabled()) {
        actions.append(copyAction);
        haveActions = true;
    }

    if (copyLinkAction->isEnabled()) {
        actions.append(copyLinkAction);
        haveActions = true;
    }

    if (haveActions) {
        QAction* chosen = QMenu::exec(actions, event->globalPos());
        if (chosen == copyAction) {
            page()->triggerAction(QWebPage::Copy);
        }
        else if (chosen == copyLinkAction) {
            page()->triggerAction(QWebPage::CopyLinkToClipboard);
        }
    }
}


void WebView::escapeString(QString& str) {

    str.replace("\r\n", "\n"); //windows
    str.replace("\\", "\\\\");
    str.replace("\"", "\\\"");
    str.replace("\n", "\\\n");
    str.replace(QChar(8232), "\\\n"); //ctrl+enter
}


QString WebView::escapeStringCopy(QString str) {
    escapeString(str);
    return str;
}

void WebView::evaluateJS(QString scriptSource) {
    page()->mainFrame()->evaluateJavaScript(scriptSource);
    //qDebug() << "HTMLChatView::evaluateJS(" << scriptSource << ")\n";
}


void WebView::importJSChatFunctions() {
    QFile file(":/htmlChatView.js");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "WARNING: HTMLChaTView::importJSChatFunction() - loading Qt Resource failed";
        //NOTE: I (senu) assume that reading from Qt Resource always succeed - there's no error handling
    }

    QString jsCode = file.readAll();
    evaluateJS(jsCode);
}