#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QLayout>
#include <QMenuBar>
#include <QActionGroup>
#include <QLabel>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QStatusBar>
#include <QApplication>

namespace Gets {
class MainWindow : public QMainWindow {

public:
    MainWindow();

protected:

private slots:
    void Undo();
    void Redo();
    void About();
    void AboutQt();

private:
    void CreateActions();
    void CreateMenus();

	QMenu* FileMenu;
    QMenu* EditMenu;
    QMenu* HelpMenu;

    QAction* ExitAct;
    QAction* UndoAct;
    QAction* RedoAct;
    QAction* AboutAct;
    QLabel* InfoLabel;
};
} // namespace Gets
