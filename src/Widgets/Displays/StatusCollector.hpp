#pragma once
#include <string>
#include <map>
#include <QString>
#include <QGroupBox>
#include <QPushButton>

namespace VSCL {
enum class Status {
    Armed,      // Red
    Disarmed,   // White
    Standby,    // White  # true/false of Standby
    Active,    // Yellow
    Opened,     // Green
    Closed      // Grey 
};

static const std::map<Status, std::string> StatusColorMap = {
    {Status::Armed, "red"},
    {Status::Disarmed, "#fbfbfb"}, 
    {Status::Standby, "yellow"},
    {Status::Active, "#fbfbfb"},
    {Status::Opened, "green"},
    {Status::Closed, "gray"}
};

QString buildStatusStyleSheet(const std::string& objectName, Status status);
void setGroupBoxStatus(QGroupBox* box, Status status);

QString buildButtonStyleSheet(Status status);
void setButtonStatus(QPushButton* button, Status status);

} // namespace VSCL