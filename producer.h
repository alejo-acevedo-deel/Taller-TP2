#ifndef PRODUCER_H_
#define PRODUCER_H_
#include <stdio.h>
#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include "compressor.h"
#include "safe_queue.h"


class Producer {
  std::ifstream &in_file;
  Compressor compressor;
  std::mutex &mutex;
  size_t compressed;
  size_t index;
  size_t threads_num;
  std::atomic<bool> work_done;
  SafeQueue my_queue;

 public:
  Producer(std::ifstream &in_file,
           size_t queue_limit,
           size_t size_block,
           std::mutex &mutex,
           size_t index,
           size_t threads_num);
  const std::vector<uint8_t> get_product();
  void set_work_done();
  bool get_work_done();
  ~Producer();
  void operator()();

 private:
  size_t calc_offset();
  int read_file();
  bool is_file_ended();
};

#endif  //  PRODUCER_H_

