#ifndef DOMXML_H
#define DOMXML_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream> //文本流
#include <QDomDocument> //文件
#include <QDomProcessingInstruction> //格式头部
#include <QDomElement>  //元素
#include <QDateTime>
#include <QDebug>

class DomXML
{
public:
    DomXML();

    static void createXML(QString filePath); //创建xml空文件

    static void appendXML(QString filePath, QStringList list); //追加

    static void writeXML(QDomDocument &doc, QDomElement &root, QStringList &list);

    static void readXML(QString filePath,
                        QStringList &flist,
                        QStringList &bList,
                        QStringList &pList,
                        QStringList &nList,
                        QStringList &tList,
                        QStringList &timeList
                        );
};

#endif // DOMXML_H
