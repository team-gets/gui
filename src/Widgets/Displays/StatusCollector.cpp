#include "StatusCollector.hpp"

#include <format>
#include <QStyle>

namespace VSCL{

QString buildStatusStyleSheet(const std::string& objectName, Status status) {
    std::string color = StatusColorMap.at(status);
    
    std::string sheet = std::format(
        "QGroupBox#{} {{"
        "  border: 2px {};"
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
};

void setGroupBoxStatus(QGroupBox *box, Status status) {
    const std::string objectName = box->objectName().toStdString();
    QString sheet = buildStatusStyleSheet(objectName, status);

    box->setStyleSheet(sheet);

    box->style()->unpolish(box);
    box->style()->polish(box);
	box->update();
}

} // namespace VSCL