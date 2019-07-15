#include "settings.hh"

CSettings::CSettings()
{
    QString configXMLPath = QCoreApplication::applicationDirPath()+SETTING_FILE_NAME;
    QFile file(configXMLPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader reader(&file);
        while (!reader.atEnd() && !reader.hasError())
        {
            QXmlStreamReader::TokenType token = reader.readNext();

            if (token == QXmlStreamReader::StartElement)
            {
                if (reader.name() == "appenvironment" || reader.name() == "oa_app_version")
                {
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (attributes.hasAttribute("value"))
                    {
                        QString strValue = attributes.value("value").toString();
                        //mapList.insert(reader.name().toString(), strValue);
                    }
                }
            }
        }
        //解析出错
        if (reader.hasError())
        {
            QString errorInfo = QStringLiteral("XML解析错误：%1  行号：%2  列号：%3  字符位移：%4").
                arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
            qDebug() << errorInfo;
        }

        file.close();
        reader.clear();
    }
    return mapList;
}

CSettings::~CSettings()
{

}
