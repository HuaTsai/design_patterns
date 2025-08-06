#include "connect_telecom.hpp"

ConnectTelecom::ConnectTelecom(std::shared_ptr<Telecom> telecom) : telecom_(telecom) {}

void ConnectTelecom::Execute() { Telecom::Connect(); }

void ConnectTelecom::Undo() { Telecom::Disconnect(); }

std::string ConnectTelecom::name() const { return "ConnectTelecom"; }
