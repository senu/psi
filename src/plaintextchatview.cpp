#include "plaintextchatview.h"


__PlainTextChatView::__PlainTextChatView(QWidget *parent) : ChatView(parent), textview(this) {

    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(&textview);

    setLayout(layout);
}


void __PlainTextChatView::appendEvent(const ChatEvent* event, bool alreadyAppended) {

    ChatView::appendEvent(event, alreadyAppended);

    QString part = event->getRightTemplateAndFillItWithData(theme);
    appendText(part);
}


void __PlainTextChatView::appendMessage(const MessageChatEvent* event, bool alreadyAppended) {

    ChatView::appendMessage(event, alreadyAppended);

    QString part;

    if (event->isLocal()) {
        part = theme.createOutgoingMessagePart(event);
    }
    else {
        part = theme.createIncomingMessagePart(event);
    }

    appendText(part);
}


void __PlainTextChatView::clear() {
}


void __PlainTextChatView::init() {
    reappendEvents();
    emit initDocumentFinished();
}


void __PlainTextChatView::scrollToBottom() {
    verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}


void __PlainTextChatView::scrollToTop() {
    verticalScrollBar()->setValue(verticalScrollBar()->minimum());
}


bool __PlainTextChatView::atBottom() const {
    // '32' is 32 pixels margin, which was used in the old code
    return (verticalScrollBar()->maximum() - verticalScrollBar()->value()) <= 32;
    //TODO reimplement in html cv?
}


QScrollBar * __PlainTextChatView::verticalScrollBar() const {
    return textview.verticalScrollBar();
}


void __PlainTextChatView::setReadOnly(bool readOnly) {
    textview.setReadOnly(readOnly);
}