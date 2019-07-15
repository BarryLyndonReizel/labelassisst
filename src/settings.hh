#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <QFile>
#include <QCoreApplication>
#include <QXmlStreamReader>

#define SETTING_FILE_NAME "labelAssistSettings.xml"

class CSettings
{
public:
    CSettings();
    ~CSettings();
};

#endif // SETTINGS_HH
