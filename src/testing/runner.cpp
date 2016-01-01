#include "runner.h"
    
namespace testing {

    Runner::Runner() { }
    
    Runner::~Runner() {
        // std::vector destroys contents when clears.
        // no need to delete explicitly.
        suites.clear();
    }
    
    void Runner::add(Suite *suite) {
        suites.push_back(suite);
    }
    
    void Runner::add(Report *report) {
        reports.add(report);
    }
    
    void Runner::run() {
    
        for(Suite *suite : suites) {
            suite->run(&this->reports);
        }
    }
    
}
