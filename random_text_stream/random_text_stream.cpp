#include "random_text_stream.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

RandomTextStream::RandomTextStream(QIODevice *f)
    : f(f)
{
}

RandomTextStream::RandomTextStream()
{
}

RandomTextStream::~RandomTextStream()
{
}

void RandomTextStream::setFile(QIODevice *f)
{
    this->f = f;
}

void RandomTextStream::write(const QString &codec)
{
    QTextStream s(f);
    if (codec != "") s.setCodec(codec.toUtf8());

    for (int i = 0; i < lines.size(); ++i)
        s << lines[i] << "\n";
}

int RandomTextStream::lineCount() const
{
    return lines.size();
}

void RandomTextStream::output() const
{
    for (int i = 0; i < lines.size(); ++i)
        qDebug() << i << lines[i];
}

void RandomTextStream::appendLine(const QString &content)
{
    lines.append(content);
}

bool RandomTextStream::removeLine(int id)
{
    if (!isValidLineId(id)) return false;

    lines.removeAt(id);
    return true;
}

QString RandomTextStream::getLine(int id) const
{
    if (!isValidLineId(id)) return "";
    return lines[id];
}

bool RandomTextStream::setLine(int id, const QString &content)
{
    if (!isValidLineId(id)) return false;

    lines[id] = content;
    return true;
}

bool RandomTextStream::setLineForced(int id, const QString &content)
{
    if (id < 0) return false;

    forceLineId(id);
    return setLine(id, content);
}

bool RandomTextStream::appendAtLine(int id, const QString &content)
{
    if (!isValidLineId(id)) return false;
    lines[id].append(content);
    return true;
}

bool RandomTextStream::appendAtLineForced(int id, const QString &content)
{
    if (id < 0) return false;

    forceLineId(id);
    return appendAtLine(id, content);
}

bool RandomTextStream::isValidLineId(int id) const
{
    if (id < 0) return false;
    return lines.size() > id;
}

void RandomTextStream::forceLineId(int id)
{
    int line_count = lineCount();
    if (line_count > id) return;

    for (int i = line_count; i <= id; ++i)
        appendLine();
}
