#pragma once
#include <string>
#include <map>
#include <QString>
#include <QGroupBox>

namespace VSCL {
enum class Status {
    Armed,      // Red
    Disarmed,   // Yellow
    Standby,    // Blue
    Opened,     // Green
    Closed      // Grey
};

static const std::map<Status, std::string> StatusColorMap = {
    {Status::Armed, "solid red"},
    {Status::Disarmed, "solid yellow"},
    {Status::Standby, "solid blue"},
    {Status::Opened, "solid green"},
    {Status::Closed, "solid gray"}
};

QString buildStatusStyleSheet(const std::string& objectName, Status status);
void setGroupBoxStatus(QGroupBox* box, Status status);
} // namespace VSCL