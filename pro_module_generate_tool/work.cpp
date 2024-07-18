#include "work.h"

#include <QDebug>
#include <QDir>
#include <QString>
#include <QUrl>

Work::Work(QObject *parent)
    : QObject(parent)
{
}

void Work::OnStartGen(const QString &root_path_url,
                      const QString &module_file_url)
{
    QUrl url;
    url.setUrl(root_path_url);
    QString root_path = url.toLocalFile();
    url.setUrl(module_file_url);
    QString module_pro = url.toLocalFile();

    CreatePri(module_pro);
    ModifyPro(module_pro);
    AppendList(module_pro, root_path);
}

void Work::Test()
{
}

void Work::CreatePri(const QString &pro_file)
{
    QFileInfo info;
    info.setFile(pro_file);

    QString module_name = info.baseName().toLower();
    QString pri_ref_name = module_name.toUpper();

    QString file_name =
        QString("%1/ref_%2.pri").arg(info.absolutePath()).arg(info.baseName());
    QFile f(file_name);

    QString content = QString(
                          "if (!contains(DEFINES, INC_PRI_%2)) {\n"
                          "    DEFINES += INC_PRI_%2\n"
                          "    INCLUDEPATH += $${PWD}\n"
                          "\n"
                          "    if (!contains(DEFINES, %2_LIBRARY)) {\n"
                          "        _LIB_NAME_%2 = %1\n"
                          "\n"
                          "        win32 {\n"
                          "            CONFIG(debug,debug|release){\n"
                          "                LIBS += -L$${DEBUG_PATH_WIN32} "
                          "-l$${_LIB_NAME_%2}d\n"
                          "            } else {\n"
                          "                LIBS += -L$${RELEASE_PATH_WIN32} "
                          "-l$${_LIB_NAME_%2}\n"
                          "            }\n"
                          "        }\n"
                          "\n"
                          "        unix {\n"
                          "            CONFIG(debug,debug|release){\n"
                          "                contains(QT_ARCH, arm64) {\n"
                          "                    LIBS += "
                          "-L$${DEBUG_PATH_LINUX_ARM64} -l$${_LIB_NAME_%2}d\n"
                          "                } else {\n"
                          "                    LIBS += "
                          "-L$${DEBUG_PATH_LINUX_X86} -l$${_LIB_NAME_%2}d\n"
                          "                }\n"
                          "            } else {\n"
                          "                contains(QT_ARCH, arm64) {\n"
                          "                    LIBS += "
                          "-L$${RELEASE_PATH_LINUX_ARM64} -l$${_LIB_NAME_%2}\n"
                          "                } else {\n"
                          "                    LIBS += "
                          "-L$${RELEASE_PATH_LINUX_X86} -l$${_LIB_NAME_%2}\n"
                          "                }\n"
                          "            }\n"
                          "        }\n"
                          "    }\n"
                          "}")
                          .arg(module_name)
                          .arg(pri_ref_name);

    f.open(QIODevice::WriteOnly);
    QTextStream s(&f);
    s << content;

    f.close();
}

void Work::ModifyPro(const QString &pro_file)
{
    QFileInfo info;
    info.setFile(pro_file);

    QString module_name = info.baseName().toLower();
    QString pri_ref_name = module_name.toUpper();
    QFile f(pro_file);

    f.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream s(&f);

    QString content =
        QString(
            "LIB_NAME = %1\n"
            "PROJECT_ROOT_PATH = $$absolute_path($${_PRO_FILE_PWD_}/../)\n"
            "include($$absolute_path($${PROJECT_ROOT_PATH}/common_dest.pri))\n"
            "include($$absolute_path($${PROJECT_ROOT_PATH}/module_list.pri))\n"
            "include($${PRI_%2})\n")
            .arg(module_name)
            .arg(pri_ref_name);

    s << content;

    f.close();
}

void Work::AppendList(const QString &pro_file, const QString &root_pro)
{
    QFileInfo info, info2;
    info.setFile(root_pro);
    info2.setFile(pro_file);

    QString module_name = info2.baseName().toLower();
    QString pri_ref_name = module_name.toUpper();

    QString list_file = QString("%1/module_list.pri").arg(info.absolutePath());

    QFile f(list_file);
    f.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream s(&f);

    QString content = QString("PRI_%2 = $${PROJECT_ROOT_PATH}/%1/ref_%1.pri\n")
                          .arg(module_name)
                          .arg(pri_ref_name);

    s << content;

    f.close();
}
