#include "random_text_stream.h"

#include <QFile>
#include <QTextStream>

RandomTextStream::RandomTextStream(QFile *f)
    : f(f)
    , buffer({})
{
}

void RandomTextStream::write()
{
    QTextStream s(f);
    for (int i = 0; i < buffer.size(); ++i)
        s << buffer[i] << "\n";
}

int RandomTextStream::lines() const
{
    return buffer.size();
}

void RandomTextStream::addLine(const QString &content)
{
    buffer.append(content);
}

bool RandomTextStream::removeLine(int id)
{
    if (!isValidLineId(id)) return false;

    buffer.removeAt(id);
    return true;
}

QString RandomTextStream::getLine(int id) const
{
    if (!isValidLineId(id)) return "";
    return buffer[id];
}

bool RandomTextStream::setLine(int id, const QString &content)
{
    if (!isValidLineId(id)) return false;

    buffer[id] = content;
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
    buffer[id].append(content);
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
    return buffer.size() > id;
}

void RandomTextStream::forceLineId(int id)
{
    int line_count = lines();
    if (line_count > id) return;

    for (int i = line_count; i <= id; ++i)
        addLine();
}
