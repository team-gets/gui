#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

#include <QWidget>
#include <QLayout>
#include <QQuickWidget>

#include <QActionGroup>

namespace VSCL {
class MainWindow : public QMainWindow {

public:
    MainWindow();

    void SetQMLFromPath(const QUrl& path);
protected:

private slots:
    void OpenQML();
    void ReloadQML();
    void About();

private:
	QQuickWidget* MainQuick;
	QUrl CurrentQML;

    void CreateActions();
    void CreateMenus();

	QMenu* FileMenu;
    QMenu* EditMenu;
    QMenu* HelpMenu;

	QAction* QMLLoadAct;
    QAction* ExitAct;
    QAction* ReloadAct;
    QAction* AboutAct;
}; // class MainWindow
} // namespace VSCL
