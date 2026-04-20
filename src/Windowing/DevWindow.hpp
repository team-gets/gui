#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QStackedWidget>

#include <QWidget>
#include <QLayout>
#include <QQuickWidget>

#include <QActionGroup>

#include "NumericTestWidget.hpp"

namespace VSCL {
class DevWindow : public QMainWindow {

public:
    DevWindow();

	enum SETTING {
		QML_VIEW,
		NUMERIC_TESTING
	};

    void SetQMLFromPath(const QUrl& path);
	void SwapSetting();
	QStackedWidget* GetStackedWidget();

protected:

private slots:
    void OpenQML();
    void ReloadQML();
    void About();

private:
	SETTING CurrentSetting = SETTING::NUMERIC_TESTING;
	QStackedWidget* Stacker;

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
}; // class DevWindow
} // namespace VSCL
