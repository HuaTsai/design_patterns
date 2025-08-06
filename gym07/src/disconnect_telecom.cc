#include "disconnect_telecom.hpp"

DisconnectTelecom::DisconnectTelecom(std::shared_ptr<Telecom> telecom) : telecom_(telecom) {}

void DisconnectTelecom::Execute() { Telecom::Disconnect(); }

void DisconnectTelecom::Undo() { Telecom::Connect(); }

std::string DisconnectTelecom::name() const { return "DisconnectTelecom"; }
