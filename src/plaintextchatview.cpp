#include "plaintextchatview.h"


PlainTextChatView::PlainTextChatView(QWidget *parent, PlainTextChatTheme theme_)
: ChatView(parent),
textview(this),
theme(theme_) {

    textview.setFont(theme.chatFont());

    layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(&textview);

    setFocusPolicy(Qt::NoFocus);
    textview.setFocusPolicy(Qt::NoFocus);

    connect(&textview, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
    setLayout(layout);
}


void PlainTextChatView::appendEvent(const ChatEvent* event, bool alreadyAppended) {

    ChatView::appendEvent(event, alreadyAppended);

    QString part = event->getRightTemplateAndFillItWithData(theme);
    appendText(part);
}


void PlainTextChatView::appendMessage(const MessageChatEvent* event, bool alreadyAppended) {

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


void PlainTextChatView::clear() {
}


void PlainTextChatView::init() {
    reappendEvents();
    emit initDocumentFinished();
}


bool PlainTextChatView::atBottom() const {
    // '32' is 32 pixels margin, which was used in the old code
    return (verticalScrollBar()->maximum() - verticalScrollBar()->value()) <= 32;
}


QScrollBar * PlainTextChatView::verticalScrollBar() const {
    return textview.verticalScrollBar();
}


void PlainTextChatView::scrollUp() {
    verticalScrollBar()->setValue(verticalScrollBar()->value() - verticalScrollBar()->pageStep() / 2);
}


void PlainTextChatView::scrollDown() {
    verticalScrollBar()->setValue(verticalScrollBar()->value() + verticalScrollBar()->pageStep() / 2);
}


void PlainTextChatView::appendText(const QString &text) {
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


QSize PlainTextChatView::sizeHint() const {
    return minimumSizeHint();
}


bool PlainTextChatView::internalFind(const QString& str, bool startFromBeginning) {

    if (startFromBeginning) {
        QTextCursor cursor = textview.textCursor();
        cursor.movePosition(QTextCursor::Start, QTextCursor::KeepAnchor);
        cursor.clearSelection();
        textview.setTextCursor(cursor);
    }

    bool found = textview.find(str);

    if (!found) {
        if (!startFromBeginning) {
            return internalFind(str, true);
        }

        return false;
    }

    return true;
}


bool PlainTextChatView::hasSelectedText() const {
    return textview.hasSelectedText();
}


void PlainTextChatView::copySelectedText() {
    textview.copy();
}

void PlainTextChatView::scrollToTop() {
    textview.scrollToTop();
}

void PlainTextChatView::scrollToBottom() {
    textview.scrollToBottom();
}