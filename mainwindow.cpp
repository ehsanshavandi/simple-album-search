#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  init();
  bootUi();
  createSignalSlots();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::init()
{
  m_cnfg = Configuration::instance(this);
  //  qInfo() << m_cnfg.readData("sqlitePath").toString();
  m_dbManager = DatabaseManager::instance(this, m_cnfg->readData("sqlitePath").toString());
  m_db = m_dbManager->createConnection();
}

void MainWindow::bootUi()
{
  ui->btnSearch->setEnabled(false);
  showAllAlbumes();
}

void MainWindow::createSignalSlots()
{
  connect(ui->btnSearch, &QPushButton::clicked, this, &MainWindow::search);
  connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::setEnabledSearchButton);
}

void MainWindow::setEnabledSearchButton(const QString& text)
{
  if (text == "" || text == nullptr)
  {
    ui->btnSearch->setEnabled(false);
    showAllAlbumes();
  }
  else
    ui->btnSearch->setEnabled(true);
}

void MainWindow::showAllAlbumes()
{
  QSqlQuery query;
  query.exec("SELECT AlbumId, Title, ArtistId, Column1 FROM Album");

  while (query.next())
  {
    int id = query.value(0).toInt();
    QString title = query.value(1).toString();
    int artistId = query.value(2).toInt();
    QString row = "id: " + QString::number(id) + ", "
                  + "title: " + title + ", " +
                  "artistId: " + QString::number(artistId);
    ui->listWidget->addItem(row);
  }
}

void MainWindow::search()
{
  // first clear list widget
  ui->listWidget->clear();

  // make sql query
  QSqlQuery query;
  query.prepare("SELECT AlbumId, Title, ArtistId, Column1 FROM Album WHERE Title LIKE '%'||:title||'%'");
  query.bindValue(":title", ui->lineEdit->text());

  if (!query.exec())
  {
    QMessageBox::critical(this, "Error", query.lastError().text());
    return;
  }

  while (query.next())
  {
    int id = query.value(0).toInt();
    QString title = query.value(1).toString();
    int artistId = query.value(2).toInt();
    QString row = "id: " + QString::number(id) + ", "
                  + "title: " + title + ", " +
                  "artistId: " + QString::number(artistId);
    ui->listWidget->addItem(row);
  }

}

void MainWindow::closeEvent(QCloseEvent* event)
{
  event->accept();
}

