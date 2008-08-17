#ifndef _ICONSERVER_H
#define	_ICONSERVER_H

#include <QString>
#include <QHash>
#include <QStringList>
#include <QList>
#include <QPair>
#include <QMutex>
#include <QBuffer>
#include <QPixmap>


/**
 * Conains icons and avatars for Webkit use.
 *
 * It has similar to the IconsetFactory + AvatarFactory functionality.
 *
 * When webkit encounter for example \<img src="icon://smile.png"\> it will call  
 * IconServer::getIcon("smile.png") 
 *
 * You have to registerIcon() before webkit could use it. 
 * You can register any data (e.g. you can "download" HTML using icon:// URL).
 *
 * You have to delete this object afer all Webkit (ChatDialogs) instances are deleted.
 * 
 * NOTE: dataMutex is mutable
 */
class IconServer : public QObject {

    Q_OBJECT
public:

    IconServer() : QObject() {}
    
    /**
     * Registers icon.
     *
     * name => data. \param data should contain image data eg. BMP, PNG *
     * It will replace old icon.
     *
     * NOTE: dataMutex is modified 
     */
    void registerIcon(const QString& name, QByteArray data);

    /** 
     * Returns image data or empty QByteArray if \param name was't registered.
     *
     * NOTE: dataMutex is modified 
     */
    QByteArray getIcon(const QString& name) const;

    /** Converts QPixmap to QByteArray using PNG format */
    static QByteArray pixmapToPng(const QPixmap& pixmap);

    public 
slots:
    /** 
     * Unregisters all icons from (icon)names 
     *
     * NOTE: dataMutex is modified 
     */
    void unregisterAll(const QStringList& names);

    /**
     * Registers all icons (name => icon) 
     *
     * NOTE: dataMutex is modified 
     */
    void registerAll(QStringList names, const QList<const QPixmap*>& icons); //qt moc cannot handle const list<pair>& 


protected:
    /** Icon dictionary */
    QHash<QString, QByteArray> dict;

    /** Webkit runs in separate thread, so we need synchronize get/register icon */
    mutable QMutex dataMutex;
};

#endif	
