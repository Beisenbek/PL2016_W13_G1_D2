#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct candidate{
	string name;
	long long votes;
};

struct state{
	string name;
	long long state_votes;
	map<string,long long> candidates;

	void printCandidates(){
		map<string, long long>::iterator it;
		for(it = candidates.begin(); it != candidates.end(); ++it){
			cout << (*it).first << " " << (*it).second << endl;
		}
	}

	candidate getWinner(){
		map<string, long long>::iterator it;
		
		candidate winner;
		winner.votes = -1;
		winner.name = "";

		for(it = candidates.begin(); it != candidates.end(); ++it){
			if((*it).second > winner.votes){
				winner.votes = (*it).second;
				winner.name = (*it).first;
			}
		}

		winner.votes = state_votes;

		return winner;
	}
};


bool f(candidate l, candidate r){
	if(l.votes < r.votes) return false;
	if(l.votes == r.votes && l.name > r.name) return false;
	return true;
}

int main(){

	freopen("input.txt","r",stdin);

	int n;
	string state_name,candidate_name;
	
	vector<candidate> res;
	map<string,state> states;
	map<string, long long> statistics;

	cin >> n;

	for(int i = 0; i < n; ++i){
		state s;
		cin >> s.name >> s.state_votes;
		states[s.name] = s;
	}

	while(cin >> state_name >> candidate_name){
		states[state_name].candidates[candidate_name]++;
		statistics[candidate_name] = 0;
	}

	for(map<string,state>::iterator it = states.begin(); it != states.end(); ++it){
		string name = (*it).first;
		candidate winner = states[name].getWinner();
		statistics[winner.name] += winner.votes;
	}

	for(map<string, long long>::iterator it = statistics.begin(); it != statistics.end(); ++it){
		candidate c;
		c.name = (*it).first;
		c.votes =(*it).second; 
		res.push_back(c);
	}

	sort(res.begin(), res.end() ,f);
	
	for(unsigned long i = 0; i < res.size(); ++i){
		cout << res[i].name << " " << res[i].votes << endl;
	}

	return 0;
}