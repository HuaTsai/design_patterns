#include "disconnect_telecom.hpp"

DisconnectTelecom::DisconnectTelecom(std::shared_ptr<Telecom> telecom) : telecom_(telecom) {}

void DisconnectTelecom::Execute() { telecom_->Disconnect(); }  // NOLINT(readability-static-accessed-through-instance)

void DisconnectTelecom::Undo() { telecom_->Connect(); }  // NOLINT(readability-static-accessed-through-instance)

std::string DisconnectTelecom::name() const { return "DisconnectTelecom"; }
