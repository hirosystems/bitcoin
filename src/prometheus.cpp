#include <logging.h>
#include <util/system.h>
#include <support/events.h>

#include <prometheus/counter.h>
#include <prometheus/registry.h>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <sys/param.h>
#include <unistd.h>
#include <prometheus.h> // promserver
#include <mutex>
/* push */
// #include <prometheus/gateway.h>
/* pull */
#include <prometheus/exposer.h>


void StartPrometheus() {
  using namespace prometheus;
  std::mutex mutex;
  std::string promserverBind;
  LogPrintf("Prometheus Server: starting %d worker threads\n", DEFAULT_PROMSERVER_THREADS);
  promserverBind = gArgs.GetArg("-promserverbind", DEFAULT_PROMSERVER_BIND);
  LogPrintf("%s: Setting Promserver Bind: %u\n", __func__, promserverBind);
  prometheus::Exposer exposer{promserverBind, DEFAULT_PROMSERVER_THREADS};
  auto& counter_family = BuildCounter()
                             .Name("time_running_seconds_total")
                             .Help("How many seconds is this server running?")
                             .Labels({{"label", "value"}})
                             .Register(*registry);
  auto& second_counter = counter_family.Add({});

  // ask the exposer to scrape the registry on incoming scrapes
  exposer.RegisterCollectable(registry);
  mutex.lock();
  for (;;) {
    if (STOP_PROMSERVER_THREAD)
      break;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // increment the counter by one (second)
    second_counter.Increment();
  }
  mutex.unlock();
  return;
}
