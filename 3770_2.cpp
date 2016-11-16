//for windows mingw

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct candidate {
	string name;
	long long votes;	
};

bool f2(candidate l, candidate r){
    if(l.votes > r.votes) return true;
    if(l.votes == r.votes && l.name < r.name) return true;
    return false;
}

struct f {
    bool operator()(const candidate& l, const candidate& r) const{
        if(l.votes > r.votes) return true;
        if(l.votes == r.votes && l.name < r.name) return true;
        return false;
    }
};

struct state{
	string state_name;
	long long viborshiki_cnt;
	map<string, long long> all_votes;
		
	candidate getWinner(){
		
		map<string, long long>::iterator it = all_votes.begin();
		candidate res;
		res.name = (*it).first;
		res.votes = (*it).second;
		
		while(++it != all_votes.end()){
			if(res.votes < (*it).second || (res.votes == (*it).second && res.name > (*it).first)){
				res.name = (*it).first;
				res.votes = (*it).second;
			}
		}

		res.votes = viborshiki_cnt;

		return res;
	}
};




int main(){

	freopen("input.txt","r",stdin);

	map<string, state> states;

	long long n;
	cin >> n;
	state s;

	for(long long i = 0; i < n; ++i){
		cin >> s.state_name >> s.viborshiki_cnt;
		states[s.state_name] = s;
	}

	string candidate_name;
	string state_name;
	map<string,long long> statistics;
	
	while(cin >> state_name >> candidate_name){
		states[state_name].all_votes[candidate_name]++;
		statistics[candidate_name] = 0;
	}

	map<string, state>::iterator it;
	map<string, long long>::iterator it2;
	
	set<candidate,f> res;

	for(it = states.begin(); it!=states.end(); ++it){
		candidate c = (*it).second.getWinner();
		statistics[c.name] += c.votes;
	}

	for(it2 = statistics.begin(); it2!=statistics.end(); ++it2){
		candidate c;
		c.name = (*it2).first;
		c.votes = (*it2).second;
		res.insert(c);
	}

	set<candidate,f>::iterator it3;

	for(it3 = res.begin(); it3 != res.end(); ++it3){
		cout << (*it3).name << " " << (*it3).votes << endl;
	}


	return 0;
}