#include "StatusCollector.hpp"

#include <format>
#include <QStyle>

namespace VSCL{

QString buildStatusStyleSheet(const std::string& objectName, Status status) {
    std::string color = StatusColorMap.at(status);
    
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
    objectName,
    color
    );  

    return QString::fromStdString(sheet);
}

void setGroupBoxStatus(QGroupBox *box, Status status) {
    const std::string objectName = box->objectName().toStdString();
    QString sheet = buildStatusStyleSheet(objectName, status);

    box->setStyleSheet(sheet);

    box->style()->unpolish(box);
    box->style()->polish(box);
	box->update();
}

QString buildButtonStyleSheet(Status status) {
    std::string color = StatusColorMap.at(status);

    std::string sheet = std::format(
        " QPushButton {{ background-color: {}; color: black; }}",
        color
    );

    return QString::fromStdString(sheet);
}

void setButtonStatus(QPushButton* button, Status status) {
    QString sheet = buildButtonStyleSheet(status);

    button->setStyleSheet(sheet);

    button->style()->unpolish(button);
    button->style()->polish(button);
	button->update();
}

} // namespace VSCL
