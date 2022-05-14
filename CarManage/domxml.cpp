#include "domxml.h"

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

DomXML::DomXML()
{
}

void DomXML::createXML(QString filePath)
{
    QFile file(filePath); //关联文件名字
    if(file.exists())
    {
        cout << "文件已存在";
        return; //存在不创建
    }
    else
    {
        //不存在才创建
        //只写方式打开
        bool isOK = file.open(QIODevice::WriteOnly);
        if(isOK) //打开成功
        {
            //创建xml文档对象
            QDomDocument doc;
            //创建头部格式 <?xml version="1.0" encoding="UTF-8"?>
            QDomProcessingInstruction ins;
            ins = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
            //追加元素
            doc.appendChild(ins);

            //根结点元素
            QDomElement root = doc.createElement("日销售清单");
            doc.appendChild(root);

            //保存
            QTextStream stream(&file); //文本流关联文件
            doc.save(stream, 4); // 4代表缩进字符
            file.close(); //关闭文件
        }
        else
        {
            cout << "WriteOnly error";
            return;
        }
    }

}

void DomXML::appendXML(QString filePath, QStringList list)
{
    QFile file(filePath);
    bool isOK = file.open(QIODevice::ReadOnly);
    if(true == isOK) //打开成功
    {
        //file和xml文档关联
        QDomDocument doc;
        isOK = doc.setContent(&file);
        if(isOK) //关联成功
        {
            file.close(); //关闭文件
            //获取根节点元素
            QDomElement root = doc.documentElement();

            //获取当前日期
            QDateTime date = QDateTime::currentDateTime();
            QString dateStr = date.toString("yyyy-MM-dd");

            //判断根节点下有没有子节点
            if(root.hasChildNodes()) //有子节点
            {
                //查找最后一个子节点
                QDomElement lastEmt = root.lastChildElement();
                if(lastEmt.attribute("date") == dateStr) // 有没有当前日期
                {
                    writeXML(doc, lastEmt, list);
                }
                else
                {
                    //创建日期 子节点
                    QDomElement dateEmt = doc.createElement("日期");
                    //给日期标签创建date属性
                    QDomAttr dateAttr = doc.createAttribute("date");
                    //设置属性的值
                    dateAttr.setNodeValue(dateStr);
                    //节点和属性关联
                    dateEmt.setAttributeNode(dateAttr);
                    //把日期节点追加到根节点上
                    root.appendChild(dateEmt);
                    writeXML(doc, dateEmt, list);
                }
            }
            else //没有子节点
            {
                //创建日期 子节点
                QDomElement dateEmt = doc.createElement("日期");
                //给日期标签创建date属性
                QDomAttr dateAttr = doc.createAttribute("date");
                //设置属性的值
                dateAttr.setNodeValue(dateStr);
                //节点和属性关联
                dateEmt.setAttributeNode(dateAttr);
                //把日期节点追加到根节点上
                root.appendChild(dateEmt);
                writeXML(doc, dateEmt, list);
            }

            //保存文件
            isOK = file.open(QIODevice::WriteOnly);
            if(isOK)
            {
                QTextStream stream(&file);
                doc.save(stream, 4);
                file.close();
            }
        }
        else
        {
            cout << "setContent error";
            return;
        }
    }
    else
    {
        cout << "ReadOnly error";
        return;
    }
}

void DomXML::writeXML(QDomDocument &doc, QDomElement &root, QStringList &list)
{
    //获取当前时间
    QDateTime date = QDateTime::currentDateTime();
    QString timeStr = date.toString("hh:mm:ss");

    //创建时间节点元素
    QDomElement timeEmt = doc.createElement("时间");
    //创建属性
    QDomAttr timeAttr = doc.createAttribute("time");
    //给属性设置值
    timeAttr.setNodeValue(timeStr);
    //时间节点元素和属性关联
    timeEmt.setAttributeNode(timeAttr);
    //把时间节点追加到日期节点后面
    root.appendChild(timeEmt);

    QStringList nodes;
    nodes << "厂家" << "品牌" << "报价" << "数量" << "金额";
    for(int i = 0; i < 5; ++i)
    {
        QDomElement tmpEmt = doc.createElement(nodes.at(i));
        QDomText text = doc.createTextNode(list.at(i));
        tmpEmt.appendChild(text);
        timeEmt.appendChild(tmpEmt);
    }
}

void DomXML::readXML(QString filePath,
                    QStringList &fList,
                    QStringList &bList,
                    QStringList &pList,
                    QStringList &nList,
                    QStringList &tList,
                    QStringList &timeList
                    )
{
    QFile file(filePath);
    bool isOK = file.open(QIODevice::ReadOnly);
    if(true == isOK) //打开成功
    {
        //file和xml文档关联
        QDomDocument doc;
        isOK = doc.setContent(&file);
        if(isOK) //关联成功
        {
            file.close();
            //获取当天日期
            QDateTime date = QDateTime::currentDateTime();
            QString dateStr = date.toString("yyyy-MM-dd");
            //获取根节点
            QDomElement root = doc.documentElement();
            if(root.hasChildNodes()) //有没有子节点
            {
                //找最后一个节点元素
                QDomElement lastEmt = root.lastChildElement();
                if(lastEmt.attribute("date") == dateStr) //判断有没有当天日期的子节点
                {
                    //找出当前日期下所有时间子节点
                    QDomNodeList list = lastEmt.childNodes();
                    for(int i = 0; i < list.size(); ++i)
                    {
                        QString time = list.at(i).toElement().attribute("time");
                        timeList.append(time);

                        //转换成元素，找到时间节点下的所有子节点
                        QDomNodeList subList = list.at(i).toElement().childNodes();

                        QString factory = subList.at(0).toElement().text();
                        fList.append(factory);

                        QString brand = subList.at(1).toElement().text();
                        bList.append(brand);

                        QString price = subList.at(2).toElement().text();
                        pList.append(price);

                        QString num = subList.at(3).toElement().text();
                        nList.append(num);

                        QString total = subList.at(4).toElement().text();
                        tList.append(total);
                    }
                }
                else
                {
                    cout << "没有当前日期";
                    return;
                }
            }
            else
            {
                cout << "没有子节点";
                return;
            }
        }
        else
        {
            cout << "setContent error";
            return;
        }
    }
    else
    {
        cout << "ReadOnly error";
        return;
    }
}
