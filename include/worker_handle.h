// Copyright (c) 2018 The GAM Authors 

#ifndef INCLUDE_WORKER_HANDLE_H_
#define INCLUDE_WORKER_HANDLE_H_

#include <mutex>
#include "worker.h"
#include "workrequest.h"

class WorkerHandle {
  boost::lockfree::queue<WorkRequest*>* wqueue; //work queue used to communicate with worker
  Worker* worker;
  //app-side pipe fd
  int send_pipe[2];
  int recv_pipe[2];
  static mutex lock;
#ifdef USE_PTHREAD_COND
  pthread_mutex_t cond_lock;
  pthread_cond_t cond;
#endif
#if !defined(USE_PIPE_W_TO_H) || (!defined(USE_BOOST_QUEUE) && !defined(USE_PIPE_H_TO_W))
  volatile int* notify_buf;
  int notify_buf_size;
#endif
public:
  WorkerHandle(Worker* w);
  void RegisterThread();
  void DeRegisterThread();
  int SendRequest(WorkRequest* wr);
  inline int GetWorkerId() {return worker->GetWorkerId();}
  ~WorkerHandle();
};



#endif /* INCLUDE_WORKER_HANDLE_H_ */
