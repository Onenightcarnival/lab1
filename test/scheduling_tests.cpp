#include "../src/scheduling.h"
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

TEST(SchedulingTest, SchedulingTest1) {
  pqueue_arrival pq = read_workload("workloads/workload_01.txt");
  EXPECT_EQ(pq.size(), 3);
}

TEST(SchedulingTest, SchedulingTest2) {
  pqueue_arrival pq = read_workload("workloads/not_a_file.txt");
  EXPECT_EQ(pq.size(), 0);
}

TEST(SchedulingTest, SchedulingTest3) {
  pqueue_arrival pq = read_workload("workloads/workload_01.txt");
  Process x1 = pq.top();
  pq.pop();
  EXPECT_EQ(x1.arrival, 0);
  Process x2 = pq.top();
  pq.pop();
  EXPECT_EQ(x2.arrival, 0);
  Process x3 = pq.top();
  pq.pop();
  EXPECT_EQ(x3.arrival, 0);  
}

TEST(SchedulingTest, SchedulingTest4) {
  pqueue_arrival pq = read_workload("workloads/workload_01.txt");
  Process x1 = pq.top();
  pq.pop();
  EXPECT_EQ(x1.duration, 10);
  Process x2 = pq.top();
  pq.pop();
  EXPECT_EQ(x2.duration, 10);
  Process x3 = pq.top();
  pq.pop();
  EXPECT_EQ(x3.duration, 10);  
}

TEST(SchedulingTest, SchedulingTest5) {
  pqueue_arrival pq = read_workload("workloads/workload_05.txt");
  list<Process> l = fifo(pq);
  while(!l.empty()){
    printf("a: %d d: %d f: %d c: %d\n", l.front().arrival, l.front().duration, l.front().first_run, l.front().completion);
    l.pop_front();
  }
}

TEST(SchedulingTest, SchedulingTest6) {
  pqueue_arrival pq = read_workload("workloads/workload_05.txt");
  list<Process> l = sjf(pq);
  while(!l.empty()){
    printf("a: %d d: %d f: %d c: %d\n", l.front().arrival, l.front().duration, l.front().first_run, l.front().completion);
    l.pop_front();
  }
}

TEST(SchedulingTest, SchedulingTest7) {
  pqueue_arrival pq = read_workload("workloads/workload_01.txt");
  list<Process> l = stcf(pq);
  while(!l.empty()){
    printf("a: %d d: %d f: %d c: %d\n", l.front().arrival, l.front().duration, l.front().first_run, l.front().completion);
    l.pop_front();
  }
}

TEST(SchedulingTest, SchedulingTest8) {
  pqueue_arrival pq = read_workload("workloads/workload_02.txt");
  list<Process> l = stcf(pq);
  while(!l.empty()){
    printf("a: %d d: %d f: %d c: %d\n", l.front().arrival, l.front().duration, l.front().first_run, l.front().completion);
    l.pop_front();
  }
}

TEST(SchedulingTest, SchedulingTest9) {
  pqueue_arrival pq = read_workload("workloads/workload_03.txt");
  list<Process> l = stcf(pq);
  while(!l.empty()){
    printf("a: %d d: %d f: %d c: %d\n", l.front().arrival, l.front().duration, l.front().first_run, l.front().completion);
    l.pop_front();
  }
}

TEST(SchedulingTest, SchedulingTest10) {
  pqueue_arrival pq = read_workload("workloads/workload_04.txt");
  list<Process> l = stcf(pq);
  while(!l.empty()){
    printf("a: %d d: %d f: %d c: %d\n", l.front().arrival, l.front().duration, l.front().first_run, l.front().completion);
    l.pop_front();
  }
}

TEST(SchedulingTest, SchedulingTest11) {
  pqueue_arrival pq = read_workload("workloads/workload_05.txt");
  list<Process> l = stcf(pq);
  while(!l.empty()){
    printf("a: %d d: %d f: %d c: %d\n", l.front().arrival, l.front().duration, l.front().first_run, l.front().completion);
    l.pop_front();
  }
}

TEST(SchedulingTest, SchedulingTest12) {
  pqueue_arrival pq = read_workload("workloads/workload_05.txt");
  list<Process> l = rr(pq);
  while(!l.empty()){
    printf("a: %d d: %d f: %d c: %d\n", l.front().arrival, l.front().duration, l.front().first_run, l.front().completion);
    l.pop_front();
  }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
