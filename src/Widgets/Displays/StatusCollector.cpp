#include "StatusCollector.hpp"

#include <format>
#include <QStyle>

namespace VSCL{

QString BuildStatusStyleSheet(const std::string& object_name, Status status) {
    std::string color = STATUS_COLOR_MAP.at(status);
    
    std::string sheet = std::format(
        "QGroupBox#{} {{"
        "  border: 2px solid {};"
        "  border-radius: 5px;"
        "  margin-top: 20px;"
        "}}"
        "QGroupBox#statusColumn::title {{"
        "  subcontrol-origin: margin;"
        "  subcontrol-position: top left;"
        "  padding: 0 0px;"
        "}}",
    object_name,
    color
    );  

    return QString::fromStdString(sheet);
}

void SetGroupBoxStatus(QGroupBox *box, Status status) {
    const std::string objectName = box->objectName().toStdString();
    QString sheet = BuildStatusStyleSheet(objectName, status);

    box->setStyleSheet(sheet);

    box->style()->unpolish(box);
    box->style()->polish(box);
	box->update();
}

QString BuildButtonStyleSheet(Status status) {
    std::string color = STATUS_COLOR_MAP.at(status);

    std::string sheet = std::format(
        " QPushButton {{ background-color: {}; color: black; }}",
        color
    );

    return QString::fromStdString(sheet);
}

void SetButtonStatus(QPushButton* button, Status status) {
    QString sheet = BuildButtonStyleSheet(status);

    button->setStyleSheet(sheet);

    button->style()->unpolish(button);
    button->style()->polish(button);
	button->update();
}

} // namespace VSCL
