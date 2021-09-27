#include "configuration.h"

Configuration::Configuration(QObject* parent, QString t_configPath) : QObject(parent)
{
  init(t_configPath);
}

Configuration* Configuration::instance(QObject* parent, QString t_configPath)
{
  if (m_instance == nullptr)
  {
    m_instance = new Configuration(parent, t_configPath);
  }

  return m_instance;
}

Configuration* Configuration::instance(QObject* parent)
{

  if (m_instance == nullptr)
  {
    m_instance = new Configuration(parent);
  }

  return m_instance;
}

void Configuration::init(QString t_fileName)
{
  QString valueFromFile;
  QFile file;
  file.setFileName(t_fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    qCritical() << file.errorString();
    return;
  }

  valueFromFile = file.readAll();
  file.close();

  QJsonDocument documentJson = QJsonDocument::fromJson(valueFromFile.toUtf8());
  m_config = documentJson.object();
}

QVariant Configuration::readData(QString data)
{
  QJsonValue value = m_config.value(QString(data));
  return value.toVariant();
}

Configuration::~Configuration()
{

}

// Initialize static member of class DatabaseManager
Configuration* Configuration::m_instance = nullptr;

