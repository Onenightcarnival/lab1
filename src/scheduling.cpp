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

  ifstream buff;
  int temp;

  buff.open(filename);
  if(buff){
  	while(buff >> temp){
  		Process p;
  		p.arrival = temp;
  		if(buff >> temp){
        p.duration = temp;
      }
  		workload.push(p);
  	}
  }
  buff.close();

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
  while(!workload.empty()){
    complete.push_back(workload.top());
    workload.pop();
  }
  return complete;
}

list<Process> sjf(pqueue_arrival workload)
{ 
  // pqueue_arrival cp = workload;
  // list<Process> complete;
  // vector<Process> prev;
  // vector<Process> curr;
  // pqueue_duration qd;
  // vector<int> arriveTable;
  // arriveTable.push_back(prev[0].arrival);

  // int i = 0;
  // int nextArrival;
  // int totalDuration = 0;
  // int counter = 0;
  // int finish;

  // if(workload.size() == 1){
  //   Process p = workload.top();
  //   workload.pop();
  //   p.first_run = p.arrival;
  //   finish = finish + p.duration;
  //   p.completion = finish;
  //   complete.push_back(p);
  //   return complete;
  // }
  
  // while(!workload.empty()){
  //   //if next job has same arrival time, put it in the vector
  //   if(workload.top().arrival == arriveTable[i]){
  //     prev.push_back(workload.top());
  //     workload.pop();
  //     //if this is the last job in workload, which is base case
  //     if(workload.empty()){
  //       //save all the jobs in the vector whose arrival time are the same into qd
  //       for(unsigned int j = 0; j < prev.size(); j++){
  //         qd.push(prev[j]);
  //       }
  //       //compute first_run and completion then return the list
  //       while(!qd.empty()){
  //         qd.top().first_run = arriveTable[i];
  //         finish = finish + qd.top().duration;
  //         qd.top().completion = finish;
  //         complete.push_back(qd.top());
  //         qd.pop();
  //       }
  //       return complete;
  //     }
  //   }
  //   else{
  //     //save next different arrival time into timeTable
  //     nextArrival = workload.top().arrival;
  //     i++;
  //     arriveTable[i] = nextArrival;
  //     //all the jobs in the vector has the same arrival time
  //     for(unsigned int j = 0; j < prev.size(); j++){
  //       qd.push(prev[j]);
  //     }
  //     while(!qd.empty() && totalDuration < nextArrival){
  //       qd.top().first_run = arriveTable[i - 1];
  //       totalDuration = totalDuration + qd.top().duration;
  //       qd.top().completion = totalDuration;
  //       counter++;
  //       complete.push_back(qd.top());
  //       qd.pop();
  //     }
  //     if(!qd.empty()){
  //       for(unsigned int k = counter; k < prev.size(); k++){
  //         curr.push_back(prev[k]);
  //       }
  //       counter = 0;
  //       prev = curr;
  //       curr.clear();
  //     }
  //     else{
  //       prev.clear();
  //     }
  //   }
  // }
    //   //push all the eligble jobs into duration pq
    //   for(int j = 0; j < prev.size(); j++){
    //     if(totalDuration < nextArrival){
    //       qd.push(prev[j]);
    //       totalDuration = totalDuration + prev[j].duration;
    //     }
    //     else{
    //       counter = j;
    //       break;
    //     }
    //   }
    //   totalDuration = 0;
    //   //push the eligble jobs into list
    //   for(int k = 0; k < counter; k++){
    //     complete.push_back(qd.top());
    //     qd.pop();
    //   }
    //   //save the rest jobs and refresh their arrival time to nextArrival;
    //   for(int x = counter; counter < prev.size(); x++){
    //     curr.push_back(prev[x]);
    //   }
    //   prev = curr;
    //   curr.clear();
    //   // while(qd.size() != 0){
    //   //   qd.pop();
    //   // }
    //   for(int n = 0; n < prev.size(); n++){
    //     prev[n].arrival = nextArrival;
    //   }
    // }
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
  int turnaround;
  int size = processes.size();
  while(!processes.empty()){
    turnaround = turnaround + (processes.front().completion - processes.front().arrival);
  }
  float result = turnaround / size;
  return result;
}

float avg_response(list<Process> processes)
{
  int reponse;
  int size = processes.size();
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
