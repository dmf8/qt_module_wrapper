#ifndef RANDOM_TEXT_STREAM_H
#define RANDOM_TEXT_STREAM_H

#include <QStringList>

#include "random_text_stream_global.h"

class QIODevice;
class RANDOM_TEXT_STREAM_EXPORT RandomTextStream
{
public:
    RandomTextStream(QIODevice* f);
    RandomTextStream();
    ~RandomTextStream();

    // io
    void setFile(QIODevice* f);
    void write(const QString& codec = "");
    void write(QTextCodec* codec);
    // status
    int lineCount() const;
    void output() const;

    // operate
    void appendLine(const QString& content = "");
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
    QIODevice* f;
    QStringList lines;
};

#endif  // RANDOM_TEXT_STREAM_H
