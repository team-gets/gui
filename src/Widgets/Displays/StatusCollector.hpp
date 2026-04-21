#pragma once
#include <string>
#include <map>
#include <QString>
#include <QGroupBox>
#include <QPushButton>

namespace VSCL {
enum class Status {
    ARMED,      // Red
    DISARMED,   // White
    STANDBY,    // White  # true/false of Standby
    ACTIVE,    // Yellow
    OPENED,     // Green
    CLOSED      // Grey 
};

static const std::map<Status, std::string> STATUS_COLOR_MAP = {
    {Status::ARMED, "red"},
    {Status::DISARMED, "#fbfbfb"}, 
    {Status::STANDBY, "#fbfbfb"},
    {Status::ACTIVE, "yellow"},
    {Status::OPENED, "green"},
    {Status::CLOSED, "gray"}
};

QString BuildStatusStyleSheet(const std::string& object_name, Status status);
void SetGroupBoxStatus(QGroupBox* box, Status status);

QString BuildButtonStyleSheet(Status status);
void SetButtonStatus(QPushButton* button, Status status);

} // namespace VSCL
