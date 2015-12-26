//
//  JobPool.h
//  julia
//
//  Created by Russell Wilhelm Bentley on 12/23/15
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include <list>
#include <mutex>

using namespace std;

template <typename J> 
class JobPool {
protected:
	list <J*> m_queue;
	mutex m_mutex; 

public:
	JobPool ();
	~JobPool ();

	void addJob (J *job);
	J *getJob ();
};

template <typename J> JobPool <J>::JobPool () {
 
}

template <typename J> JobPool <J>::~JobPool () {

}

template <typename J> void JobPool <J>::addJob (J *job) {
    m_queue.push_back (job);
}

template <typename J> J *JobPool <J>::getJob () {
    J *result;
    m_mutex.lock ();
    if (!m_queue.empty ()) {
        result = m_queue.front ();
        m_queue.pop_front ();
        m_mutex.unlock ();
    } else {
        result = nullptr;
    }
    return result;
}
