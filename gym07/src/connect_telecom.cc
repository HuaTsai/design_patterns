#include "connect_telecom.hpp"

ConnectTelecom::ConnectTelecom(std::shared_ptr<Telecom> telecom) : telecom_(telecom) {}

void ConnectTelecom::Execute() { telecom_->Connect(); }  // NOLINT(readability-static-accessed-through-instance)

void ConnectTelecom::Undo() { telecom_->Disconnect(); }  // NOLINT(readability-static-accessed-through-instance)

std::string ConnectTelecom::name() const { return "ConnectTelecom"; }
