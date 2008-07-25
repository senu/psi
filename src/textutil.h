#ifndef TEXTUTIL_H
#define TEXTUTIL_H

class QString;

namespace TextUtil 
{
	QString escape(const QString& unescaped);
	QString unescape(const QString& escaped);

	QString quote(const QString &, int width=60, bool quoteEmpty=false);
	QString plain2rich(const QString &);
	QString rich2plain(const QString &);
	QString resolveEntities(const QString &);
	QString linkify(const QString &);
	QString legacyFormat(const QString &);
    /** Replaces text to emoticons: <icon> or <img src="icon://"> if useImgTag is true*/
	QString emoticonify(const QString &in, bool useImgTag);
};

#endif
