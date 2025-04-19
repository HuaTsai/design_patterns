#include <client/fake_http_client.hpp>
#include <print>
#include <processor/blacklist_url_processor.hpp>
#include <processor/load_balancing_url_processor.hpp>
#include <processor/service_discovery_url_processor.hpp>

int main() {
  auto client = std::make_shared<ServiceDiscoveryUrlProcerssor>(
      "../config/services.txt",
      std::make_shared<LoadBalancingUrlProcessor>(std::make_shared<BlacklistUrlProcessor>(
          "../config/blacklist.txt", std::make_shared<FakeHttpClient>())));
  auto response1 = client->SendRequest({"http://waterballsa.tw/test"})[0];
  std::print("{}\n", response1);
  auto response2 = client->SendRequest({"http://waterballsa.tw/test"})[0];
  std::print("{}\n", response2);
  auto response3 = client->SendRequest({"http://waterballsa.tw/test"})[0];
  std::print("{}\n", response3);
  auto response4 = client->SendRequest({"http://waterballsa.tw/test"})[0];
  std::print("{}\n", response4);
}
