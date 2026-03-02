#include "MainWindow.h"

namespace Gets {
MainWindow::MainWindow() {
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    InfoLabel = new QLabel(tr("<i>Blank</i>"));
    InfoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    InfoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(topFiller);
    layout->addWidget(InfoLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    CreateActions();
    CreateMenus();

    QString message = tr("Howdy");
    statusBar()->showMessage(message);

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

void MainWindow::Undo() {
    InfoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void MainWindow::Redo() {
    InfoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void MainWindow::About() {
    InfoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("The <b>Menu</b> example shows how to create "
               "menu-bar menus and context menus."));
}

void MainWindow::AboutQt() {
    InfoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
} // void MainWindow::AboutQt()

void MainWindow::CreateMenus() {
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addAction(ExitAct);

    EditMenu = menuBar()->addMenu(tr("&Edit"));
    EditMenu->addAction(UndoAct);
    EditMenu->addAction(RedoAct);

    HelpMenu = menuBar()->addMenu(tr("&Help"));
    HelpMenu->addAction(AboutAct);
} // void MainWindow::CreateMenus()

void MainWindow::CreateActions() {
    ExitAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit),
                          tr("Exit"), this);
    ExitAct->setShortcuts(QKeySequence::Quit);
    ExitAct->setStatusTip(tr("Exit the application"));
    connect(ExitAct, &QAction::triggered, this, &QWidget::close);

    UndoAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditUndo),
                          tr("Undo"), this);
    UndoAct->setShortcuts(QKeySequence::Undo);
    UndoAct->setStatusTip(tr("Undo the last operation"));
    connect(UndoAct, &QAction::triggered, this, &MainWindow::Undo);

    RedoAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::EditRedo),
                          tr("Redo"), this);
    RedoAct->setShortcuts(QKeySequence::Redo);
    RedoAct->setStatusTip(tr("Redo the last operation"));
    connect(RedoAct, &QAction::triggered, this, &MainWindow::Redo);

	AboutAct = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout),
                           tr("&About"), this);
    AboutAct->setStatusTip(tr("Show the application's About box"));
    connect(AboutAct, &QAction::triggered, this, &MainWindow::About);
} // void MainWindow::CreateActions()

} // namespace Gets
