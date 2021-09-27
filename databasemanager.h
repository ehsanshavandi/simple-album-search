#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QString>


class DatabaseManager : public QObject {
  Q_OBJECT
 public:
  // delete copy constructor and assingment operator
  DatabaseManager(DatabaseManager const&) = delete;
  void operator=(DatabaseManager const&) = delete;

  static DatabaseManager* instance(QObject* parent, QString const&  t_dbPath);
  ~DatabaseManager();

  bool openConncetion();
  void closeConncetion();
  QSqlDatabase createConnection();

 signals:

 private:
  // singletone pattern
  explicit DatabaseManager(QObject* parent = nullptr, QString const&  t_dbPath = "/");
  static DatabaseManager* m_instance;

  QSqlDatabase db() const;
  QSqlDatabase m_db;
  QString m_dbPath;
};

#endif // DATABASEMANAGER_H
