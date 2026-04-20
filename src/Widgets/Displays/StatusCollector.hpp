#pragma once
#include <string>
#include <map>
#include <QString>
#include <QGroupBox>
#include <QPushButton>

namespace VSCL {
enum class STATUS {
    ARMED,      // Red
    DISARMED,   // White
    STANDBY,    // White  # true/false of Standby
    ACTIVE,    // Yellow
    OPENED,     // Green
    CLOSED      // Grey 
};

static const std::map<STATUS, std::string> STATUS_COLOR_MAP = {
    {STATUS::ARMED, "red"},
    {STATUS::DISARMED, "#fbfbfb"}, 
    {STATUS::STANDBY, "#fbfbfb"},
    {STATUS::ACTIVE, "yellow"},
    {STATUS::OPENED, "green"},
    {STATUS::CLOSED, "gray"}
};

QString BuildStatusStyleSheet(const std::string& object_name, STATUS status);
void SetGroupBoxStatus(QGroupBox* box, STATUS status);

QString BuildButtonStyleSheet(STATUS status);
void SetButtonStatus(QPushButton* button, STATUS status);

} // namespace VSCL