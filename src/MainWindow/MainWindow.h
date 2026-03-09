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

#include "NumericTestWidget.h"

namespace VSCL {
class MainWindow : public QMainWindow {

public:
    MainWindow();

	enum Setting {
		QMLView,
		NumericTesting
	};

    void SetQMLFromPath(const QUrl& path);
	void SwapSetting();

protected:

private slots:
    void OpenQML();
    void ReloadQML();
    void About();

private:
	Setting CurrentSetting = Setting::NumericTesting;

	/*
	 *	QML Viewer
	 */

	// The Main Viewport
	QQuickWidget* MainQuick;

	// Path to the currently loaded QML
	QUrl CurrentQML;

	/*
	 *	Numeric widget display testing
	 */

	// The main tester view
	NumericTestWidget* NumericDisplaysTest;

	/*
	 *	Actions
	 */

    void CreateActions();
    void CreateMenus();

	QMenu* FileMenu;
    QMenu* EditMenu;
    QMenu* HelpMenu;

	QAction* QMLLoadAct;
    QAction* ExitAct;
    QAction* ReloadAct;
    QAction* AboutAct;
    QAction* SwapSettingAct;
}; // class MainWindow
} // namespace VSCL
