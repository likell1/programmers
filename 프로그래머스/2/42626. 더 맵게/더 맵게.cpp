#include <string>
#include <vector>
#include <queue>

using namespace std;


int solution(vector<int> scoville, int K) {
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end());
    int answer = 0;
    
    while(pq.top() < K){
        if (pq.size() < 1) {return -1;}
        int x = pq.top();
        pq.pop();
        
        if (pq.empty() == false) {
            int y = pq.top();
            pq.pop();
            pq.push(x+ (y*2));
            answer++;
        }
        else return -1;
    }
    
    return answer;
}