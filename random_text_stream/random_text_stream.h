#ifndef RANDOM_TEXT_STREAM_H
#define RANDOM_TEXT_STREAM_H

#include <QStringList>

#include "random_text_stream_global.h"

class QFile;
class RANDOM_TEXT_STREAM_EXPORT RandomTextStream
{
public:
    RandomTextStream(QFile* f);

    void write();
    int lines() const;
    void addLine(const QString& content = "");
    bool removeLine(int id);
    QString getLine(int id) const;
    bool setLine(int id, const QString& content = "");
    bool setLineForced(int id, const QString& content = "");
    bool appendAtLine(int id, const QString& content);
    bool appendAtLineForced(int id, const QString& content);

private:
    bool isValidLineId(int id) const;
    void forceLineId(int id);

private:
    QFile* f;
    QStringList buffer;
};

#endif  // RANDOM_TEXT_STREAM_H
