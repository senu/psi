/*
 * msgmle.h - subclass of PsiTextView to handle various hotkeys
 * Copyright (C) 2001-2003  Justin Karneges, Michail Pishchagin
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef MSGMLE_H
#define MSGMLE_H

#include <QTextEdit>

#include "psitextview.h"
#include "psichatedit.h"

class ChatEdit;
class QEvent;
class QKeyEvent;
class QResizeEvent;
class QTimer;
class SpellHighlighter;

/** 
 * Old ChatView. Obsolete/Deprecated.
 *
 * Currently used in StatusDlg and FileTransfer Dialog. 
 * It exist only because if it was replaced with other widget I (senu) wouldn't have
 * time to fully test substituion.
 *
 * If you want feature-rich TextView use webkit-based HTMLChatView or DeprecatedChatView.
 * If you want to display simple Message/Event use EventView or PsiTextView. 
 * If you want editor use [line][HTML]ChatEdit.
 *
 */
class DeprecatedChatView : public PsiTextView
{
    Q_OBJECT
public:
    DeprecatedChatView(QWidget* parent);
    ~DeprecatedChatView();

    void setDialog(QWidget* dialog);

    // reimplemented
    QSize sizeHint() const;

    void appendText(const QString &text);
    bool handleCopyEvent(QObject *object, QEvent *event, ChatEdit *chatEdit);

    QString formatTimeStamp(const QDateTime &time);

protected:
    // override the tab/esc behavior
    bool focusNextPrevChild(bool next);
    void keyPressEvent(QKeyEvent *);

    protected
slots:
    void autoCopy();

private:
    QWidget* dialog_;
};

#endif
