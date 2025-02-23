#include "connect_telecom.hpp"

ConnectTelecom::ConnectTelecom(std::shared_ptr<Telecom> telecom) : telecom_(telecom) {}

void ConnectTelecom::Execute() { telecom_->Connect(); }

void ConnectTelecom::Undo() { telecom_->Disconnect(); }

std::string ConnectTelecom::name() const { return "ConnectTelecom"; }
