#include "StatusCollector.hpp"

#include <QStyle>

namespace VSCL{
QString BuildStatusStyleSheet(const QString& object_name, Status status) {
    const std::string& color = STATUS_COLOR_MAP.at(status);
    return QString(
        " QGroupBox#%1 {"
        "  border: 2px solid %2;"
        "  border-radius: 5px;"
        "  margin-top: 20px;"
        "}"
        " QGroupBox#StatusRow::title {"
        "  subcontrol-origin: margin;"
        "  subcontrol-position: top left;"
        "  padding: 0 0px;"
        "}"
        ).arg(object_name).arg(QString::fromStdString(color));
}

void SetGroupBoxStatus(QGroupBox *box, Status status) {
    const QString objectName = box->objectName();
    const QString sheet = BuildStatusStyleSheet(objectName, status);

    box->setStyleSheet(sheet);

    box->style()->unpolish(box);
    box->style()->polish(box);
	box->update();
}

QString BuildButtonStyleSheet(Status status) {
    const std::string& color = STATUS_COLOR_MAP.at(status);
    return QString(" QPushButton { background-color: %1; color: black; }")
    	.arg(QString::fromStdString(color));
}

void SetButtonStatus(QPushButton* button, Status status) {
    const QString sheet = BuildButtonStyleSheet(status);
    button->setStyleSheet(sheet);

    button->style()->unpolish(button);
    button->style()->polish(button);
	button->update();
}

} // namespace VSCL
