#include "disconnect_telecom.hpp"

DisconnectTelecom::DisconnectTelecom(std::shared_ptr<Telecom> telecom) : telecom_(telecom) {}

void DisconnectTelecom::Execute() { telecom_->Disconnect(); }  // NOLINT

void DisconnectTelecom::Undo() { telecom_->Connect(); }  // NOLINT

std::string DisconnectTelecom::name() const { return "DisconnectTelecom"; }
