#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 *  @file   MainWindow.h
 *  @brief  Simple Search Albumes
 *  @details this is very basic search using sqlite
 *  @author Ehsan shavandi
 *  @date   2021-09-19
 ***********************************************/

#include <QMainWindow>
#include "configuration.h"
#include "databasemanager.h"
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;

  /*!
   * \brief initialize application properties
   * \return void
   */
  void init();
  /*!
   * \brief boot ui setup like button mode for first run
   * \return void
   */
  void bootUi();
  /*!
   * \brief connect all required signals and slots
   * \return void
   */
  void createSignalSlots();
  /*!
   * \brief enables the search button when user writing in lineEdit
   * \param text
   * \return void
   */
  void setEnabledSearchButton(const QString& text);
  /*!
   * \brief show all albums(select * from albums)
   * \details show all albums need in two state,
   *  first is application is initialized and socond is when there is no character in lineEdit
   * \return void
   */
  void showAllAlbumes();

  /*!
   * \brief search for specific album
   * \details this will fired as search button is clicked
   * \return void
   */
  void search();
  /*!
   * \brief m_cnfg, property for work with config file
   */
  Configuration* m_cnfg;
  /*!
   * \brief m_dbManager, property for work db
   */
  DatabaseManager*  m_dbManager;
  /*!
   * \brief m_dbManager, property for work connection
   */
  QSqlDatabase  m_db;

  /*!
   * \brief close event
   * */
  // QWidget interface
 protected:
  void closeEvent(QCloseEvent* event) override;
};
#endif // MAINWINDOW_H
