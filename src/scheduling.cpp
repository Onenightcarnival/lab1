#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <sstream>

#include "scheduling.h"

using namespace std;

// vector<vector<string>> strToStrs(vector<string> str){
// 	vector<vector<string>> r;
// 	vector<string> s;
// 	string line;
// 	for(unsigned int i = 0; i < str.size(); i++){
// 		line = str[i];
// 		stringstream strStream(line);
//   		char letter;
//   		string word;
//   		int j = 0;
//   		while(strStream.get(letter)){
//     		if(isspace(letter)){
//      			if(word.size() > 0){
//         			s[j] = word;
//         			word.clear();
//         			j++;
//       			}
//       			continue;
//     		}
//     		word += letter;
//   		}
//   		r.push_back(s);
//   		s.clear();
// 	}
//   	return r;
// }

// vector<vector<int>> strToInt(vector<vector<string>> strs){
//   vector<vector<int>> r;
//   vector<int> v;
//   vector<string> s;
//   for(unsigned int i = 0; i < strs.size(); i++){
//   	s = strs[i];
//   	for(unsigned int j = 0; j < s.size(); j++){
//   		v[j] = stoi(s[j]);
//   		v[j] = stoi(s[j]);
//   	}
//   	r.push_back(v);
//   }
//   return r;
// }

pqueue_arrival read_workload(string filename)
{
  pqueue_arrival workload;

  // ifstream afile;
  // afile.open(filename);

  // vector<string> strs;
  // string str;
  // while(getline(afile, str)){
  //   if(str.empty()){
  //     continue;
  //   }
  //   strs.push_back(str);
  // }
  // afile.close();
  // afile.clear();

  // vector<vector<int>> data = strToInt(strToStrs(strs));
  // vector<int> temp;
  // Process p;

  // for(unsigned int i = 0; i < data.size(); i++){
  // 	temp = data[i];
  // 	p.arrival = temp[0];
  // 	p.duration = temp[1];
  // 	p.completion = -1;
  // 	p.first_run = -1;
  // 	workload.push(p);
  // }

  ifstream readMe;
  int time;

  readMe.open(filename);
  if(readMe){
  	while(readMe >> time){
  		Process p;
  		p.arrival = time;
  		p.completion = -1;
  		p.first_run = -1;
  		p.duration = time;
  		workload.push(p);
  	}
  }
  readMe.close();

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
  vector<Process> p;

  for(unsigned int i = 0; i < workload.size(); i++){
    p[i] = workload.top();
    workload.pop();
  }

  for(unsigned int i = 0; i < p.size(); i++){
    complete.push_back(p[i]);
  }

  return complete;
}

list<Process> sjf(pqueue_arrival workload)
{
  list<Process> complete;
  int arrivalTime;
  int durationTime;
  vector<Process> p;
  vector<int> arriveTable;
  int curr;
  int prev = workload.top().arrival;
  arriveTable.push_back(curr);
  
  for(unsigned int i = workload.size(); i > 0; i--){
    p[i] = workload.top();
    curr = p[i].arrival;
    if(curr != prev){
      arriveTable.push_back(curr);
      prev = curr;
    }
    workload.pop();
  }

  if(arriveTable.size() == 1){
    for(unsigned int i = 0; i < p.size(); i++){
      complete.push_back(p[i]);
    }
    return complete;
  }

  // for(int i = 0; i < p.size; i++){
  //   if(p[i])
  // }

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
