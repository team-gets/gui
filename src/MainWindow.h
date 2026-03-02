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

namespace Gets {
class MainWindow : public QMainWindow {

public:
    MainWindow();

    void SetQMLFromPath(const QUrl& path);
protected:

private slots:
    void OpenQML();
    void Undo();
    void Redo();
    void About();

private:
	QQuickWidget* MainQuick;

    void CreateActions();
    void CreateMenus();

	QMenu* FileMenu;
    QMenu* EditMenu;
    QMenu* HelpMenu;

	QAction* QMLLoadAct;
    QAction* ExitAct;
    QAction* UndoAct;
    QAction* RedoAct;
    QAction* AboutAct;
}; // class MainWindow
} // namespace Gets
