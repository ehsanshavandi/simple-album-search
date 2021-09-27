#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QIODevice>

class Configuration : public QObject {
  Q_OBJECT
 public:
  // delete copy constructor and assingment operator
  Configuration(Configuration const&) = delete;
  void operator=(Configuration const&) = delete;

  static Configuration* instance(QObject* parent, QString t_configPath);
  static Configuration* instance(QObject* parent);
  QVariant readData(QString data);

  ~Configuration();
 signals:

 private:
  explicit Configuration(QObject* parent = nullptr, QString t_configPath = "config.json");
  static Configuration* m_instance;
  void init(QString t_fileName);
  QJsonObject m_config;

};

#endif // CONFIGURATION_H
