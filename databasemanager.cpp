#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject* parent, QString const&  t_dbPath) : QObject(parent)
{
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_dbPath = QString(t_dbPath);
  m_db.setDatabaseName(m_dbPath);
}

DatabaseManager* DatabaseManager::instance(QObject* parent, QString const&  t_dbPath)
{
  if (m_instance == nullptr)
  {
    m_instance = new DatabaseManager(parent, t_dbPath);
  }

  return m_instance;
}

DatabaseManager::~DatabaseManager()
{
  closeConncetion();
}

bool DatabaseManager::openConncetion()
{
  if (!m_db.open())
  {
    qWarning() << m_db.lastError();
    return false;
  }
  else
  {
    qInfo() << "Connected to db";
    return true;
  }
}

void DatabaseManager::closeConncetion()
{
  qInfo() << "close db";

  if (m_db.open()) m_db.close();
}

QSqlDatabase DatabaseManager::createConnection()
{
  openConncetion();
  QSqlDatabase dbConnection = db();
  return dbConnection;
}

QSqlDatabase DatabaseManager::db() const
{
  return m_db;
}

// Initialize static member of class DatabaseManager
DatabaseManager* DatabaseManager::m_instance = nullptr;
