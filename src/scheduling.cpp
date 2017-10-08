#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <sstream>
#include <map>

#include "scheduling.h"

using namespace std;

typedef struct fakeProcess fakeProcess;
struct fakeProcess{
	int fake_arrival;
	Process p;
};

class fakeArrivalComparator {
public:
  bool operator()(const fakeProcess lhs, const fakeProcess rhs)  const {
    return lhs.p.arrival > rhs.p.arrival;
  }
};

class fakeDurationComparator {
public:
  bool operator()(const fakeProcess lhs, const fakeProcess rhs)  const {
    return lhs.p.duration > rhs.p.duration;
  }
};

typedef priority_queue<fakeProcess, vector<fakeProcess>, fakeArrivalComparator> fakepqueue_arrival;
typedef priority_queue<fakeProcess, vector<fakeProcess>, fakeDurationComparator> fakepqueue_duration;

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
  int run = workload.top().arrival;
  int finish = workload.top().duration;
  while(!workload.empty()){
  	Process p = workload.top();
  	p.first_run = run;
  	p.completion = finish;
  	run = finish;
  	finish = finish + p.duration;
    complete.push_back(p);
    workload.pop();
  }
  return complete;
}

list<Process> sjf(pqueue_arrival workload)
{ 
	list<Process> complete;
	int begin = 0;
	int total = 0;
	int nextArrival = 0;
	pqueue_duration pd;

	while(!workload.empty()){
		Process p = workload.top();
		if(p.arrival == nextArrival){
			pd.push(p);
		}
		else{
			nextArrival = p.arrival;
			while(!pd.empty()){
				Process temp = pd.top();
				temp.first_run = begin;
				total += temp.duration;
				temp.completion = total;
				begin = total;
				complete.push_back(temp);
				pd.pop();
			}
			pd.push(p);
		}
		workload.pop();
		if(workload.empty()){
			while(!pd.empty()){
				Process temp = pd.top();
				temp.first_run = begin;
				total += temp.duration;
				temp.completion = total;
				begin = total;
				complete.push_back(temp);
				pd.pop();
			}
		}
	}

	return complete;

}

list<Process> stcf(pqueue_arrival workload)
{
  	  list<Process> complete;
	  vector<fakeProcess> fp;
	  fakepqueue_duration fpd;
	  int begin = workload.top().arrival;

	  while(!workload.empty()){
	  	Process t = workload.top();
	  	fakeProcess f;
	  	if(t.arrival <= begin){
	  		f.p = t;
	  		f.fake_arrival = begin;
	  		fpd.push(f);
	  		workload.pop();
	  	}
	  	else{
	  		while(!fpd.empty()){
	  			fakeProcess r = fpd.top();
	  			r.p.first_run = begin;
	  			begin += r.p.duration;
	  			r.p.completion = begin;
	  			fpd.pop();
	  			complete.push_back(r.p);
	  			if(fpd.empty()){
	  				return complete;
	  			}
	  			else{
	  				Process c = workload.top();
	  				if(begin < c.arrival){
	  					continue;
	  				}
	  				else{
	  					while(!fpd.empty()){
	  						fp.push_back(fpd.top());
	  						fpd.pop();
	  					}
	  					for(int i = 0; i< fp.size(); i++){
	  						fp[i].fake_arrival = begin;
	  						fpd.push(fp[i]);
	  					}
	  					fp.clear();
	  					break;
	  				}
	  			}
	  		}
	  	}
	  }
	  if(fpd.empty()){
	  	return complete;
	  }
	  else{
	  	fakeProcess m;
	  	while(!fpd.empty()){
	  		m = fpd.top();
	  		m.p.first_run = begin;
	  		begin += m.p.duration;
	  		m.p.completion = begin;
	  		complete.push_back(m.p);
	  		fpd.pop();
	  	}
	  	return complete;
	  }
}

list<Process> rr(pqueue_arrival workload)
{
  list<Process> complete;
  int timeSlice = 1;

  return complete;
}

float avg_turnaround(list<Process> processes)
{
  int turnaround;
  int size = processes.size();
  while(!processes.empty()){
    turnaround = turnaround + (processes.front().completion - processes.front().arrival);
    processes.pop_front();
  }
  float result = turnaround / size;
  return result;
}

float avg_response(list<Process> processes)
{
  int response;
  int size = processes.size();
  while(!processes.empty()){
  	response = response + (processes.front().first_run - processes.front().arrival);
  	processes.pop_front();
  }
  float result = response / size;
  return result;
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
