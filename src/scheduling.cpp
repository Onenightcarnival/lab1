#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <sstream>

#include "scheduling.h"

using namespace std;

vector<string> strToStrs(string str){
  vector<string> r;
  stringstream strStream(str);
  char letter;
  string word;
  int i = 0;
  while(strStream.get(letter)){
    if(!isdigit(letter)){
      if(word.size() > 0){
        r[i] = word;
        word.clear();
        i++;
      }
      continue;
    }
    word += letter;
  }
  return r;
}

vector<int> strToInt(vector<string> strs){
  vector<int> r;
  for(int i = 0; i < strs.size(); i++){
    r[i] = stoi(strs[i]);
  }
  return r;
}

pqueue_arrival read_workload(string filename)
{
  pqueue_arrival workload;

  ifstream afile;
  afile.open(filename);

  vector<string> strs;
  string str;
  while(getline(afile, str)){
    if(str.empty()){
      continue;
    }
    strs.push_back(str);
  }
  afile.close();
  afile.clear();

  for(int i = 0; i < strs.size(); i++){
    vector<int> data = strToInt(strToStrs(strs[i]));
    Process temp;
    temp.arrival = data[0];
    temp.duration = data[1];
    workload.push(temp);
  }

  return workload;
}

void show_workload(pqueue_arrival workload)
{
  pqueue_arrival xs = workload;
  cout << "Workload:" << endl;
  while (!xs.empty())
  {
    Process p = xs.top();
    cout << '\t' << p.arrival << ' ' << p.duration << endl;
    xs.pop();
  }
}

void show_processes(list<Process> processes)
{
  list<Process> xs = processes;
  cout << "Processes:" << endl;
  while (!xs.empty())
  {
    Process p = xs.front();
    cout << "\tarrival=" << p.arrival << ", duration=" << p.duration
         << ", first_run=" << p.first_run << ", completion=" << p.completion << endl;
    xs.pop_front();
  }
}

list<Process> fifo(pqueue_arrival workload)
{
  list<Process> complete;
  Process[] *p = new Process[workload.size];

  //store each process into an array in arrival time ascending order
  for(int i = workload.size; i > 0; i--){
    p[i] = workload.top();
    workload.pop();
  }

  //turn the array to list
  for(int i = 0; i < p.size; i++){
    complete.push_back(p[i]);
  }

  return complete;
}

list<Process> sjf(pqueue_arrival workload)
{
  list<Process> complete;
  int arrivalTime;
  int durationTime;
  Process[] *p = new Process[workload.size];
  vector<int> arriveTable;
  int curr;
  int prev = workload.top().arrival;
  arriveTable.push_back(curr);
  
  //store each process into an array in arrival time ascending order
  //count how many different arrival times
  for(int i = workload.size; i > 0; i--){
    p[i] = workload.top();
    curr = p[i].arrival;
    if(curr != prev){
      arriveTable.push_back(curr);
      prev = curr;
    }
    workload.pop();
  }

  //arrive at same time
  if(arriveTable.size == 1){
    for(int i = 0; i < p.size; i++){
      complete.push_back(p[i]);
    }
    return complete;
  }

  for(int i = 0; i < p.size; i++){
    if(p[i])
  }

  return complete;
}

list<Process> stcf(pqueue_arrival workload)
{
  list<Process> complete;
  return complete;
}

list<Process> rr(pqueue_arrival workload)
{
  list<Process> complete;
  return complete;
}

float avg_turnaround(list<Process> processes)
{
  return 0;
}

float avg_response(list<Process> processes)
{
  return 0;
}

void show_metrics(list<Process> processes)
{
  float avg_t = avg_turnaround(processes);
  float avg_r = avg_response(processes);
  show_processes(processes);
  cout << '\n';
  cout << "Average Turnaround Time: " << avg_turnaround(processes) << endl;
  cout << "Average Response Time:   " << avg_response(processes) << endl;
}
