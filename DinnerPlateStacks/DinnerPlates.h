#include <vector>
#include <set>
#include <stack>

using namespace std;
/*
class DinnerPlates {
private: 
    vector<stack<int> > v;
    int cap;
    set<int> for_push; // stores the indices of stacks that are not-full
    int last = -1;
public:
    DinnerPlates(int capacity) {
        v.clear();
        cap = capacity;
        for_push.insert(0); // always have the next index (index that is equal to v.size() )
    }
    
    void push(int val) {
	// find the next index for push
        int idx = *for_push.begin();
		
	// if the index is the same as size of v, we need to add another stack at the end of v.
        if(v.size() <= idx) {
            v.push_back({});
        }
        v[idx].push(val);
        // std::cout << "push: " << idx << "-" << val << "\n";
        
        // update last if the idx is greater than it.
        if(last < idx) {            
            ++last;
            for_push.insert(idx+1); // update the set
        }
        
	// if the stack is full, then we need to erase the index from the for_each set.
        if(v[idx].size() == cap) {
            for_push.erase(idx);
        }
    }
    
    int pop() {
        if(last == -1) return -1;
        
	// change last to point to the last non-empty stack.
        int res = v[last].top();
        if(v[last].size() == cap) {
            for_push.insert(last);
        }
        // std::cout << "pop: " << last << "-" << res << "\n";
        v[last].pop();
        while(last >= 0 && v[last].empty()) {
            --last;
        }
        
        return res;
    }
    
    int popAtStack(int index) {
        if(index >= v.size() || v[index].empty()) {
            return -1;
        }
        
        // update the for_push set if the stack was full. 
        if(v[index].size() == cap) {
            for_push.insert(index);
        }
		
        int res = v[index].top();
        v[index].pop();
        // if the stack happens to be the last one, we need to sub last by 1.
        if(index == last && v[index].empty()) {
            last--;
        }
        // std::cout << "popat: " << index << "-" << res << "\n";
        return res;
    }
};*/

class DinnerPlates {
private:
    int capacity;
    vector<stack<int>> stacks;
    set<int> notFullStacks; // for push()
    set<int> allStacks; // for pop()
    
    void setFlag(int index){
        if(stacks[index].empty()){
            notFullStacks.insert(index);
            allStacks.erase(index);
            return;
        }
        
        if(stacks[index].size() >= capacity){
            notFullStacks.erase(index);
        }
        else{
            notFullStacks.insert(index);
        }
        
        allStacks.insert(index);
    }
public:
    DinnerPlates(int capacity):capacity(capacity) {
    }
    
    void push(int val) {
        if(!notFullStacks.empty()){
            int index = *notFullStacks.begin();
            stacks[index].push(val);
            setFlag(index);
            // std::cout << "push: " << index << "-" << val << "\n";
            return;
        }
        
        stacks.push_back(stack<int>());
        stacks.back().push(val);
        setFlag(stacks.size() - 1);
        // std::cout << "push: " << stacks.size() - 1 << "-" << val << "\n";
    }
    
    int pop() {
        if(allStacks.empty()){
           return -1; 
        }
        
        int index = *allStacks.rbegin();
        int n = stacks[index].top();
        stacks[index].pop();
        setFlag(index);
        // std::cout << "pop: " << index << "-" << n << "\n";
        return n;
    }
    
    int popAtStack(int index) {
        if(index < 0 || index >= stacks.size() || stacks[index].empty()){
            return -1;
        }
        
        int n = stacks[index].top();
        stacks[index].pop();
        setFlag(index);
        // std::cout << "popat: " << index << "-" << n << "\n";
        return n;
    }
};