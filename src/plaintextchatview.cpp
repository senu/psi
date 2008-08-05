#include "plaintextchatview.h"


__PlainTextChatView::__PlainTextChatView(QWidget *parent) : ChatView(parent), textview(this) {

    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(&textview);

    setFocusPolicy(Qt::NoFocus);
    textview.setFocusPolicy(Qt::NoFocus);

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
}


QScrollBar * __PlainTextChatView::verticalScrollBar() const {
    return textview.verticalScrollBar();
}


void __PlainTextChatView::scrollUp() {
    verticalScrollBar()->setValue(verticalScrollBar()->value() - verticalScrollBar()->pageStep() / 2);
}


void __PlainTextChatView::scrollDown() {
    verticalScrollBar()->setValue(verticalScrollBar()->value() + verticalScrollBar()->pageStep() / 2);
}


void __PlainTextChatView::appendText(const QString &text) {
    bool doScrollToBottom = atBottom();

    // prevent scrolling back to selected text when 
    // restoring selection
    int scrollbarValue = verticalScrollBar()->value();

    textview.appendText(text);

    if (doScrollToBottom)
        scrollToBottom();
    else
        verticalScrollBar()->setValue(scrollbarValue);
}


QSize __PlainTextChatView::sizeHint() const {
    return minimumSizeHint();
}